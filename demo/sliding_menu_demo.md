# 基于 Button 的滑动菜单 Demo

> 本示例演示如何基于 SGL 的 `Button`、`Rect`、`Label` 与动画系统，实现一个**滑动菜单（Carousel Menu）**：
> - 菜单项在容器中横向滑动，中间项放大、两侧项缩小（视觉层次效果）
> - 支持环形运动（circular motion）与边界模式
> - 支持方向键（←/→）切换、回车键确认
> - 使用 `sgl_anim_t` 动画系统驱动滑动过程

> ⚠️ **版本说明**：本示例基于最新版 SGL API 编写，主要适配点：
> 1. `sgl_task_handle()` → `sgl_task_handler()`
> 2. `sgl_anim_set_repeat_cnt()` 已移除，重复次数改为 `sgl_anim_start(anim, repeat_cnt)` 的第二个参数
> 3. 事件回调数据通过 `sgl_obj_set_event_cb(obj, cb, data)` 传入，回调中用 `sgl_event_get_data(event)` 取出（旧版 `event->param` 已移除）
> 4. `sgl_pixmap_t.bitmap` 改为联合体，赋值使用 `.bitmap.array`
> 5. `sgl_init()` 返回 `int`，需检查返回值

```c
/**
 * @file    sliding_menu_demo.c
 * @brief   基于 Button 的滑动菜单示例（最新版 SGL API）
 * @note    本示例使用 sgl_port_sdl2 移植层（外部提供），请在工程中加入对应
 *          SDL2 移植文件后编译运行。
 */
#include <SDL.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <sgl.h>
#include <sgl_font.h>
#include <sgl_anim.h>

typedef struct sgl_port_sdl2 sgl_port_sdl2_t;

sgl_port_sdl2_t* sgl_port_sdl2_init(void);
size_t sgl_port_sdl2_get_frame_count(sgl_port_sdl2_t* sdl2_dev);
void sgl_port_sdl2_increase_frame_count(sgl_port_sdl2_t* sdl2_dev);
void sgl_port_sdl2_deinit(sgl_port_sdl2_t* sdl2_dev);
void flush_window_callback(void *param);

/* 图片资源（外部文件提供） */
extern const unsigned char gImage_1[8192];
const sgl_pixmap_t pixmap1 = {
    .width  = 64,
    .height = 64,
    .bitmap.array = gImage_1,   /* 新版本 bitmap 为联合体 */
};

/* 滑动菜单结构体 */
typedef struct sliding_menu {
    sgl_obj_t* container;        /* 菜单容器（Rect） */
    sgl_obj_t** items;           /* 菜单项按钮数组 */
    sgl_obj_t* text_label;       /* 底部文本标签 */
    char** item_texts;           /* 菜单项文本数组 */
    int item_count;              /* 菜单项总数 */
    int current_index;           /* 当前选中项索引 */
    int target_index;            /* 动画目标索引 */
    sgl_color_t* colors;         /* 菜单项颜色数组 */
    sgl_pixmap_t** pixmaps;      /* 菜单项图片数组 */
    int container_width;         /* 容器宽度 */
    int container_height;        /* 容器高度 */

    /* 菜单项目尺寸（小/大两种状态） */
    int item_width_small;
    int item_width_large;
    int item_height_small;
    int item_height_large;

    /* 动画相关 */
    sgl_anim_t* anim;            /* SGL 动画对象 */
    bool is_animating;           /* 是否正在动画中 */
    bool circular_motion;        /* 是否启用环形运动 */
    void (*item_click_callback)(int index);  /* 点击事件回调 */
} sliding_menu_t;

/* 当前活动菜单（本示例仅一个菜单，用于事件回调中获取菜单对象） */
static sliding_menu_t *s_active_menu = NULL;

/* 前向声明（menu_anim_path 中会调用） */
void update_sliding_menu(sliding_menu_t *menu, float progress);

/**
 * @brief 菜单项事件处理函数
 * @note  事件数据通过 sgl_obj_set_event_cb() 的第三个参数传入（即菜单项索引），
 *        菜单对象通过 s_active_menu 获取。
 */
static void menu_item_event_handler(sgl_event_t* event)
{
    if (!event) {
        return;
    }

    /* 处理 RELEASED / CLICKED 事件 */
    if (event->type == SGL_EVENT_RELEASED) {
        sliding_menu_t* menu = s_active_menu;
        int item_index = (int)(intptr_t)sgl_event_get_data(event);

        if (!menu || item_index < 0 || item_index >= menu->item_count) {
            SGL_LOG_ERROR("Menu is NULL\n");
            return;
        }

        /* 只有当前选中项才触发点击事件 */
        if (item_index == menu->current_index && menu->item_click_callback) {
            SGL_LOG_INFO("Menu item %d clicked!\n", item_index);
            menu->item_click_callback(item_index);
        }
    }
}

/**
 * @brief 菜单动画路径回调（value: 0 ~ 1000，映射为滑动进度 0.0 ~ 1.0）
 */
static void menu_anim_path(sgl_anim_t* anim, int32_t value)
{
    sliding_menu_t* menu = (sliding_menu_t*)anim->data;
    float progress = (float)value / 1000.0f;
    update_sliding_menu(menu, progress);
}

/**
 * @brief 菜单动画完成回调
 */
static void menu_anim_finished(sgl_anim_t* anim)
{
    sliding_menu_t* menu = (sliding_menu_t*)anim->data;
    menu->current_index = menu->target_index;
    menu->is_animating = false; /* 标记动画已完成 */
}

/**
 * @brief 根据滑动进度更新所有菜单项的位置/尺寸（核心布局函数）
 */
void update_sliding_menu(sliding_menu_t *menu, float progress)
{
    if (!menu)
        return;

    int center_x = menu->container_width / 2; /* 容器中心点X坐标 */

    /* 只更新当前项及其相邻项 */
    for (int i = menu->current_index - 2; i <= menu->current_index + 2; i++) {
        int idx = i;

        /* 处理循环索引（仅在启用环形运动时） */
        if (menu->circular_motion) {
            if (idx < 0)
                idx += menu->item_count;
            if (idx >= menu->item_count)
                idx -= menu->item_count;
        } else {
            /* 未启用环形运动时跳过越界索引 */
            if (idx < 0 || idx >= menu->item_count)
                continue;
        }

        /* 计算当前项与当前选中项/目标选中项的距离 */
        int distance = idx - menu->current_index;
        int target_distance = idx - menu->target_index;

        /* 环形模式下使用最短路径 */
        if (menu->circular_motion) {
            if (distance > menu->item_count / 2)
                distance -= menu->item_count;
            else if (distance < -menu->item_count / 2)
                distance += menu->item_count;

            if (target_distance > menu->item_count / 2)
                target_distance -= menu->item_count;
            else if (target_distance < -menu->item_count / 2)
                target_distance += menu->item_count;
        }

        float interpolated_distance = distance + (target_distance - distance) * progress;

        /* 根据距离中心的远近动态计算尺寸 */
        float distance_abs = fabsf(interpolated_distance);
        int width, height;

        if (distance_abs <= 0.5f) {
            /* 中心附近项最大 */
            float t = 1.0f - (distance_abs / 0.5f); /* 0.0 - 1.0 */
            width  = menu->item_width_small  + (int)((menu->item_width_large  - menu->item_width_small)  * t);
            height = menu->item_height_small + (int)((menu->item_height_large - menu->item_height_small) * t);

            /* 更新底部文本标签内容 */
            if (menu->item_texts[idx]) {
                sgl_label_set_text(menu->text_label, menu->item_texts[idx]);
            } else {
                sgl_label_set_text(menu->text_label, "");
            }
        } else if (distance_abs <= 1.5f) {
            /* 中等项 */
            float t = 1.0f - ((distance_abs - 0.5f) / 1.0f); /* 0.0 - 1.0 */
            width  = menu->item_width_small  + (int)((menu->item_width_large  - menu->item_width_small)  * 0.5f * t);
            height = menu->item_height_small + (int)((menu->item_height_large - menu->item_height_small) * 0.5f * t);
        } else {
            /* 远离中心的项 */
            width  = menu->item_width_small;
            height = menu->item_height_small;
        }

        /* 计算位置（增加间距） */
        int x = center_x + (int)(interpolated_distance * (menu->item_width_small + 30)) - width / 2;
        int y = (menu->container_height - height) / 2;

        sgl_obj_set_pos(menu->items[idx], x, y);
        sgl_obj_set_size(menu->items[idx], width, height);

        /* 设置按钮圆角 */
        sgl_button_set_radius(menu->items[idx], 10);

        /* 如果该项设置了图片则设置图片 */
        if (menu->pixmaps[idx]) {
            sgl_button_set_pixmap(menu->items[idx], menu->pixmaps[idx]);
        }
    }
}

/**
 * @brief 创建滑动菜单
 */
sliding_menu_t* create_sliding_menu(sgl_obj_t* parent, int x, int y, int width, int height, int item_count)
{
    sliding_menu_t* menu = (sliding_menu_t*)malloc(sizeof(sliding_menu_t));
    if (!menu) return NULL;

    menu->container = sgl_rect_create(parent);
    sgl_obj_set_pos(menu->container, x, y);
    sgl_obj_set_size(menu->container, width, height);
    sgl_rect_set_color(menu->container, SGL_COLOR_BLACK);
    sgl_rect_set_alpha(menu->container, 100);

    /* 创建底部文本标签 */
    menu->text_label = sgl_label_create(menu->container);
    sgl_label_set_font(menu->text_label, &consolas24);
    sgl_label_set_text_color(menu->text_label, SGL_COLOR_WHITE);
    sgl_label_set_text_align(menu->text_label, SGL_ALIGN_CENTER);
    sgl_obj_set_pos(menu->text_label, 0, height - 45);
    sgl_obj_set_size(menu->text_label, width, 30);

    menu->item_count = item_count;
    menu->current_index = 0;
    menu->target_index = 0;
    menu->container_width = width;
    menu->container_height = height;
    menu->item_click_callback = NULL;

    /* 默认启用环形运动 */
    menu->circular_motion = true;

    /* 默认项目尺寸 */
    menu->item_width_small = menu->container_width / 5;
    menu->item_width_large = menu->container_width / 3;
    menu->item_height_small = menu->container_height * 2 / 3;
    menu->item_height_large = menu->container_height * 4 / 5;

    /* 分配菜单项和颜色数组 */
    menu->items = (sgl_obj_t**)malloc(sizeof(sgl_obj_t*) * item_count);
    menu->colors = (sgl_color_t*)malloc(sizeof(sgl_color_t) * item_count);
    menu->pixmaps = (sgl_pixmap_t**)malloc(sizeof(sgl_pixmap_t*) * item_count);
    menu->item_texts = (char**)malloc(sizeof(char*) * item_count);
    if (!menu->items || !menu->colors || !menu->item_texts || !menu->pixmaps) {
        free(menu);
        return NULL;
    }

    /* 默认颜色 */
    sgl_color_t default_colors[] = {
        SGL_COLOR_RED, SGL_COLOR_GREEN, SGL_COLOR_BLUE,
        SGL_COLOR_YELLOW, SGL_COLOR_MAGENTA, SGL_COLOR_CYAN
    };

    for (int i = 0; i < item_count; i++) {
        menu->items[i] = sgl_button_create(menu->container);

        /* 设置颜色 */
        menu->colors[i] = default_colors[i % 6];

        /* 初始位置/尺寸为 0，由 update_sliding_menu() 统一布局 */
        sgl_obj_set_pos(menu->items[i], 0, 0);
        sgl_obj_set_size(menu->items[i], 0, 0);
        sgl_button_set_color(menu->items[i], menu->colors[i]);
        sgl_button_set_radius(menu->items[i], 10);

        /* 注册事件处理函数：第三个参数为事件数据（菜单项索引） */
        sgl_obj_set_event_cb(menu->items[i], menu_item_event_handler, (void *)(intptr_t)i);
        sgl_obj_set_clickable(menu->items[i]);

        /* 初始化文本和图片 */
        menu->item_texts[i] = NULL;
        menu->pixmaps[i] = NULL;
    }

    /* 记录当前活动菜单（供事件回调使用） */
    s_active_menu = menu;

    /* 创建动画对象 */
    menu->anim = sgl_anim_create();
    if (menu->anim) {
        sgl_anim_set_data(menu->anim, menu);
        sgl_anim_set_path(menu->anim, menu_anim_path, SGL_ANIM_PATH_EASE_IN_OUT);
        sgl_anim_set_act_duration(menu->anim, 300);
        sgl_anim_set_finish_cb(menu->anim, menu_anim_finished);
    }
    menu->is_animating = false; /* 初始化动画状态为未进行 */

    return menu;
}

/**
 * @brief 销毁滑动菜单，释放资源
 */
void destroy_sliding_menu(sliding_menu_t* menu)
{
    if (!menu) return;

    if (menu->anim) {
        sgl_anim_delete(menu->anim);
    }
    for (int i = 0; i < menu->item_count; i++) {
        if (menu->items[i]) {
            sgl_obj_delete(menu->items[i]);
        }
        if (menu->item_texts[i]) {
            free(menu->item_texts[i]);
        }
    }
    if (menu->text_label) {
        sgl_obj_delete(menu->text_label);
    }
    if (menu->container) {
        sgl_obj_delete(menu->container);
    }
    free(menu->items);
    free(menu->colors);
    free(menu->pixmaps);
    free(menu->item_texts);
    free(menu);

    s_active_menu = NULL;
}

/* ==================== 菜单项配置接口 ==================== */

/* 设置菜单项尺寸 */
void sliding_menu_set_item_size(sliding_menu_t* menu, int width_small, int height_small, int width_large, int height_large)
{
    if (!menu) return;
    menu->item_width_small = width_small;
    menu->item_width_large = width_large;
    menu->item_height_small = height_small;
    menu->item_height_large = height_large;
}

/* 设置是否启用环形运动 */
void sliding_menu_set_circular_motion(sliding_menu_t* menu, bool enable)
{
    if (!menu) return;
    menu->circular_motion = enable;
}

/* 获取环形运动开关状态 */
bool sliding_menu_get_circular_motion(const sliding_menu_t* menu)
{
    return menu ? menu->circular_motion : false;
}

/* 设置菜单项文本 */
void sliding_menu_set_item_text(sliding_menu_t* menu, const char* texts[])
{
    if (!menu || !texts) return;
    for (int i = 0; i < menu->item_count; i++) {
        if (menu->item_texts[i]) {
            free(menu->item_texts[i]);
            menu->item_texts[i] = NULL;
        }
        if (texts[i]) {
            menu->item_texts[i] = (char*)malloc(strlen(texts[i]) + 1);
            if (menu->item_texts[i]) {
                strcpy(menu->item_texts[i], texts[i]);
            }
        }
    }
}

/* 设置单个菜单项圆角 */
void sliding_menu_set_item_radius(sliding_menu_t* menu, int index, uint8_t radius)
{
    if (!menu || index < 0 || index >= menu->item_count) return;
    sgl_button_set_radius(menu->items[index], radius);
}

/* 设置菜单项点击回调 */
void sliding_menu_set_click_callback(sliding_menu_t* menu, void (*callback)(int index))
{
    if (!menu) return;
    menu->item_click_callback = callback;
}

/* 设置菜单项颜色 */
void sliding_menu_set_item_color(sliding_menu_t* menu, int index, sgl_color_t color)
{
    if (!menu || index < 0 || index >= menu->item_count) return;
    menu->colors[index] = color;
    sgl_button_set_color(menu->items[index], color);
}

/* 设置菜单项图片 */
void sliding_menu_set_item_pixmap(sliding_menu_t* menu, int index, const sgl_pixmap_t* pixmap)
{
    if (!menu || index < 0 || index >= menu->item_count) return;
    menu->pixmaps[index] = (sgl_pixmap_t*)pixmap;
}

/* 获取当前选中项索引 */
int sliding_menu_get_current_index(sliding_menu_t* menu)
{
    return menu ? menu->current_index : -1;
}

/* ==================== 菜单移动控制 ==================== */

/**
 * @brief 向左移动菜单（切换到上一个菜单项）
 */
void sliding_menu_move_left(sliding_menu_t* menu)
{
    if (!menu || menu->item_count <= 1) return;
    if (menu->is_animating) return; /* 动画中忽略新操作 */

    menu->target_index = menu->current_index - 1;

    if (menu->circular_motion) {
        if (menu->target_index < 0) {
            menu->target_index = menu->item_count - 1; /* 循环到末尾 */
        }
    } else {
        if (menu->target_index < 0) {
            return; /* 已在第一个元素，不移动 */
        }
    }

    menu->is_animating = true;

    if (menu->anim) {
        sgl_anim_set_start_value(menu->anim, 0);
        sgl_anim_set_end_value(menu->anim, 1000);
        sgl_anim_start(menu->anim, SGL_ANIM_REPEAT_ONCE); /* 播放一次 */
        update_sliding_menu(menu, 0.0f);
    }
}

/**
 * @brief 向右移动菜单（切换到下一个菜单项）
 */
void sliding_menu_move_right(sliding_menu_t* menu)
{
    if (!menu || menu->item_count <= 1) return;
    if (menu->is_animating) return; /* 动画中忽略新操作 */

    menu->target_index = menu->current_index + 1;

    if (menu->circular_motion) {
        if (menu->target_index >= menu->item_count) {
            menu->target_index = 0; /* 循环到开头 */
        }
    } else {
        if (menu->target_index >= menu->item_count) {
            return; /* 已在最后一个元素，不移动 */
        }
    }

    menu->is_animating = true;

    if (menu->anim) {
        sgl_anim_set_start_value(menu->anim, 0);
        sgl_anim_set_end_value(menu->anim, 1000);
        sgl_anim_start(menu->anim, SGL_ANIM_REPEAT_ONCE); /* 播放一次 */
        update_sliding_menu(menu, 0.0f);
    }
}

/**
 * @brief 点击滑动菜单项，触发按钮动画效果
 * @param menu        滑动菜单对象
 * @param item_index  菜单项索引
 * @param press_state 按键状态: 1=按下, 0=释放
 */
void sliding_menu_item_click(sliding_menu_t* menu, int item_index, int press_state)
{
    if (!menu || item_index < 0 || item_index >= menu->item_count) {
        SGL_LOG_ERROR("Invalid menu or item index\n");
        return;
    }

    /* 获取实际选中项索引（考虑动画状态） */
    int actual_index = menu->is_animating ? menu->target_index : menu->current_index;

    /* 只有当前选中项才触发点击事件 */
    if (item_index == actual_index) {
        if (press_state) {
            /* 发送按下事件触发按钮动画 */
            sgl_event_send_obj(menu->items[item_index], SGL_EVENT_PRESSED);
        } else {
            /* 发送释放事件完成按钮点击过程 */
            sgl_event_send_obj(menu->items[item_index], SGL_EVENT_RELEASED);
            if (menu->item_click_callback) {
                SGL_LOG_INFO("Menu item %d clicked via key/mouse press!\n", item_index);
                menu->item_click_callback(item_index);
            }
        }
    }
}

/* 示例点击回调函数 */
void on_menu_item_clicked(int index)
{
    SGL_LOG_INFO("Menu item %d clicked!\n", index);
}

int main(int argc, char *argv[])
{
    SGL_UNUSED(argc);
    SGL_UNUSED(argv);

    int quit = 0;
    SDL_Event MouseEvent;
    sgl_port_sdl2_t* sdl2_dev = sgl_port_sdl2_init();
    if (sdl2_dev == NULL) {
        return -1;
    }

    /* 初始化SGL（新版本返回 int，需检查返回值） */
    if (sgl_init() != 0) {
        sgl_port_sdl2_deinit(sdl2_dev);
        return -1;
    }

    /* 创建一个带图片的按钮（示例菜单项图标） */
    sgl_obj_t* btn_pic = sgl_button_create(NULL);
    sgl_obj_set_pos(btn_pic, 0, 0);
    sgl_obj_set_size(btn_pic, 64, 64);
    sgl_button_set_pixmap(btn_pic, &pixmap1);

    /* 创建滑动菜单 */
    sliding_menu_t* menu = create_sliding_menu(NULL, 100, 200, 240, 135, 5);
    if (menu) {
        /* 设置菜单项尺寸 */
        sliding_menu_set_item_size(menu, 40, 40, 55, 55);

        /* 设置菜单项文本 */
        const char* menu_items[] = {"中文", "Settings", "About", "Help", "Exit"};
        sliding_menu_set_item_text(menu, menu_items);

        /* 关闭环形运动（演示边界模式） */
        sliding_menu_set_circular_motion(menu, false);

        /* 设置点击回调 */
        sliding_menu_set_click_callback(menu, on_menu_item_clicked);

        /* 给第 2 项设置图片 */
        sliding_menu_set_item_pixmap(menu, 1, &pixmap1);

        /* 显示初始状态 */
        update_sliding_menu(menu, 1.0f);
    }

    while (!quit) {
        /* 使用 WaitEventTimeout 而非 PollEvent，减少 CPU 占用并改善事件响应 */
        if (SDL_WaitEventTimeout(&MouseEvent, 10)) {
            switch (MouseEvent.type) {
            case SDL_QUIT:
                quit = 1;
                break;

            case SDL_KEYDOWN:
                switch (MouseEvent.key.keysym.sym) {
                case SDLK_LEFT:
                    SGL_LOG_INFO("Left key detected\n");
                    sliding_menu_move_left(menu);
                    break;
                case SDLK_RIGHT:
                    SGL_LOG_INFO("Right key detected\n");
                    sliding_menu_move_right(menu);
                    break;
                case SDLK_RETURN:
                case SDLK_KP_ENTER:
                    SGL_LOG_INFO("Enter key detected\n");
                    /* 触发当前选中菜单项的点击事件（按下状态） */
                    sliding_menu_item_click(menu, sliding_menu_get_current_index(menu), 1);
                    break;
                default:
                    SGL_LOG_INFO("Other key: %d\n", MouseEvent.key.keysym.sym);
                    break;
                }
                break;

            case SDL_KEYUP:
                switch (MouseEvent.key.keysym.sym) {
                case SDLK_RETURN:
                case SDLK_KP_ENTER:
                    SGL_LOG_INFO("Enter key released\n");
                    /* 触发当前选中菜单项的点击事件（释放状态） */
                    sliding_menu_item_click(menu, sliding_menu_get_current_index(menu), 0);
                    break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                /* 如需鼠标点击支持，可在此判断点击位置并调用
                 * sliding_menu_item_click(menu, sliding_menu_get_current_index(menu), 1); */
                break;

            case SDL_MOUSEBUTTONUP:
                /* 同上：sliding_menu_item_click(menu, sliding_menu_get_current_index(menu), 0); */
                break;
            }
        }

        /* 主循环任务：事件 + 动画 + 绘制（旧版本为 sgl_task_handle()） */
        sgl_task_handler();
        sgl_port_sdl2_increase_frame_count(sdl2_dev);
    }

    /* 清理资源 */
    destroy_sliding_menu(menu);
    sgl_port_sdl2_deinit(sdl2_dev);

    return 0;
}
```
