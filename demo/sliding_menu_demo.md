```c
#include <SDL.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sgl.h>
#include <sgl_font.h>
#include <sgl_anim.h>

typedef struct sgl_port_sdl2 sgl_port_sdl2_t;

sgl_port_sdl2_t* sgl_port_sdl2_init(void);
size_t sgl_port_sdl2_get_frame_count(sgl_port_sdl2_t* sdl2_dev);
void sgl_port_sdl2_increase_frame_count(sgl_port_sdl2_t* sdl2_dev);
void sgl_port_sdl2_deinit(sgl_port_sdl2_t* sdl2_dev);
void flush_window_callback(void *param);
// 前向声明
typedef struct sliding_menu sliding_menu_t;
void update_sliding_menu(sliding_menu_t* menu, float progress);

extern const unsigned char gImage_1[8192];
const sgl_pixmap_t pixmap1 = {
    .width = 64,
    .height = 64,
    .bitmap = gImage_1,
};
// 滑动菜单结构体
typedef struct sliding_menu {
    sgl_obj_t* container;      // 菜单容器
    sgl_obj_t** items;         // 菜单项数组
    sgl_obj_t* text_label;     // 文本标签
    char** item_texts;         // 菜单项文本数组
    int item_count;            // 菜单项总数
    int current_index;         // 当前选中项索引
    sgl_color_t* colors;       // 菜单项颜色数组
    sgl_pixmap_t** pixmaps;    // 菜单项图片数组
    int container_width;       // 容器宽度
    int container_height;      // 容器高度
    //int text_offset_y;         // 文本标签距离容器底部的距离

    // 菜单项目尺寸
    int item_width_small;
    int item_width_large;
    int item_height_small;
    int item_height_large;

    // 动画相关

    int target_index;          // 目标索引
    sgl_anim_t* anim;          // SGL动画对象
    int anim_direction;        // 动画方向 (-1=左, 1=右)
    bool is_animating;         // 是否正在动画中
    bool circular_motion;      // 是否启用环形运动
    void (*item_click_callback)(int index);   // 点击事件回调

} sliding_menu_t;

  

// 菜单项事件处理函数

static void menu_item_event_handler(sgl_event_t* event) {

    // 检查事件参数有效性

    if (!event||!event->obj||!event->obj->parent) {

        //SGL_LOG_ERROR("NULL！！！！！！！！！\n");

        return;

    }

    // 处理RELEASED事件，CLICKED

    if (event->type == SGL_EVENT_RELEASED) {

        // 获取菜单对象和菜单项索引

        sliding_menu_t* menu = (sliding_menu_t*)event->obj->parent;

        int item_index = (int)event->param;

        if (!menu||item_index < 0 || item_index >= menu->item_count) {

            SGL_LOG_ERROR("Menu is NULL\n");

            return;

        }

        // // 验证索引有效性

        // if (item_index < 0 || item_index >= menu->item_count) {

        //     //SGL_LOG_ERROR("Invalid item index: %d\n", item_index);

        //     return;

        // }

        // 只有当前选中项才触发点击事件

        if (item_index == menu->current_index && menu->item_click_callback) {

            SGL_LOG_INFO("Menu item %d clicked!\n", item_index);

            menu->item_click_callback(item_index);

        }

    }

}

  

// 菜单动画路径回调函数

static void menu_anim_path(sgl_anim_t* anim, int32_t value) {

    sliding_menu_t* menu = (sliding_menu_t*)anim->data;

    float progress = (float)value / 1000.0f;

    //SGL_LOG_INFO("Animation progress: value=%d, progress=%f\n", value, progress);

    update_sliding_menu(menu, progress);



}

  

// 菜单动画完成回调函数

static void menu_anim_finished(sgl_anim_t* anim) {

    sliding_menu_t* menu = (sliding_menu_t*)anim->data;

    menu->current_index = menu->target_index;

    menu->is_animating = false; // 标记动画已完成

    //SGL_LOG_INFO("Animation finished: current_index updated to %d\n", menu->current_index);

}

  
void update_sliding_menu(sliding_menu_t *menu, float progress){

    if (!menu)
        return;
    int center_x = menu->container_width / 2; // 容器中心点X坐标
    // 隐藏所有菜单项

    // for (int i = 0; i < menu->item_count; i++) {

    //     sgl_obj_set_pos(menu->items[i], 0, 0);

    //     sgl_obj_set_size(menu->items[i], 0, 0);

    //     // 清除按钮文本

    // }

    // 只显示当前项及其相邻项

    for (int i = menu->current_index - 2; i <= menu->current_index + 2; i++)

    {

        int idx = i;

        // 处理循环索引（仅在启用环形运动时）

        if (menu->circular_motion)

        {

            if (idx < 0)

                idx += menu->item_count;

            if (idx >= menu->item_count)

                idx -= menu->item_count;

        }

        else

        {

            // 如果未启用环形运动，跳过超出范围的索引

            if (idx < 0 || idx >= menu->item_count)

                continue;

        }

  

        // 计算当前项与当前选中项的距离

        int distance = idx - menu->current_index;

        // 计算目标项与目标选中项的距离

        int target_distance = idx - menu->target_index;

  

        // 处理循环情况 - 确保使用最短路径（仅在启用环形运动时）

        if (menu->circular_motion)

        {

            if (distance > menu->item_count / 2)

            {

                distance -= menu->item_count;

            }

            else if (distance < -menu->item_count / 2)

            {

                distance += menu->item_count;

            }

  

            if (target_distance > menu->item_count / 2)

            {

                target_distance -= menu->item_count;

            }

            else if (target_distance < -menu->item_count / 2)

            {

                target_distance += menu->item_count;

            }

        }

  

        // // 特殊处理：当跨越边界时，调整目标距离以避免飞行动画

        // if (menu->anim_direction < 0 && distance == 2 && target_distance == -3) {

        //     // 从右侧瞬间出现的情况

        //     target_distance = 2;

        // } else if (menu->anim_direction > 0 && distance == -2 && target_distance == 3) {

        //     // 从左侧瞬间出现的情况

        //     target_distance = -2;

        // }

  

        float interpolated_distance = distance + (target_distance - distance) * progress;

  

        // 计算当前项的大小（根据实时距离中心的远近动态变化）

  

        float distance_abs = sgl_abs(interpolated_distance);

  

        int width, height;

  

        if (distance_abs <= 0.5)

        {

  

            // 中心附近项最大

  

            float t = 1.0f - (distance_abs / 0.5f); // 0.0 - 1.0

  

            width = menu->item_width_small + (int)((menu->item_width_large - menu->item_width_small) * t);

  

            height = menu->item_height_small + (int)((menu->item_height_large - menu->item_height_small) * t);

  

            // 更新文本标签的内容

  

            if (menu->item_texts[idx])

            {

  

                sgl_label_set_text(menu->text_label, menu->item_texts[idx]);

            }

            else

            {

  

                sgl_label_set_text(menu->text_label, "");

            }

        }

        else if (distance_abs <= 1.5)

        {

  

            // 中等项

  

            float t = 1.0f - ((distance_abs - 0.5f) / 1.0f); // 0.0 - 1.0

  

            width = menu->item_width_small + (int)((menu->item_width_large - menu->item_width_small) * 0.5f * t);

  

            height = menu->item_height_small + (int)((menu->item_height_large - menu->item_height_small) * 0.5f * t);

        }

        else

        {

  

            // 远离中心的项

  

            width = menu->item_width_small;

  

            height = menu->item_height_small;

        }

  

        // 计算位置（增加间距）

  

        int x = center_x + (int)(interpolated_distance * (menu->item_width_small + 30)) - width / 2;

  

        int y = (menu->container_height - height) / 2;

  

        sgl_obj_set_pos(menu->items[idx], x, y);

  

        sgl_obj_set_size(menu->items[idx], width, height);

  

        // 设置按钮圆角

  

        sgl_button_set_radius(menu->items[idx], 10);

  

        // 如果该项有设置图片，则设置图片

  

        if (menu->pixmaps[idx])

        {

  

            sgl_button_set_pixmap(menu->items[idx], menu->pixmaps[idx]);

        }

  

        //sgl_obj_set_dirty(menu->container);

    }

}

  

// 创建滑动菜单

sliding_menu_t* create_sliding_menu(sgl_obj_t* parent, int x, int y, int width, int height, int item_count) {

    sliding_menu_t* menu = (sliding_menu_t*)malloc(sizeof(sliding_menu_t));

    if (!menu) return NULL;

  

    menu->container = sgl_rect_create(parent);

    sgl_obj_set_pos(menu->container, x, y);

    sgl_obj_set_size(menu->container, width, height);

    sgl_rect_set_color(menu->container, SGL_COLOR_BLACK);

    sgl_rect_set_alpha(menu->container, 100);

  

    // 创建文本标签

    menu->text_label = sgl_label_create(menu->container);

    sgl_label_set_font(menu->text_label, &consolas24);

    sgl_label_set_text_color(menu->text_label, SGL_COLOR_WHITE);

    sgl_label_set_text_align(menu->text_label, SGL_ALIGN_CENTER);

  

    menu->item_count = item_count;

    menu->current_index = 0;

    menu->target_index = 0;

    menu->container_width = width;

    menu->container_height = height;

    menu->text_offset_y = 45;  // 默认距离容器底部10像素

    menu->item_click_callback = NULL;

    sgl_obj_set_pos(menu->text_label, 0, menu->container_height - menu->text_offset_y);

    sgl_obj_set_size(menu->text_label, menu->container_width, 30);

    // 默认启用环形运动

    menu->circular_motion = true;

  

    // 默认项目尺寸

    menu->item_width_small = menu->container_width / 5;

    menu->item_width_large = menu->container_width / 3;

    menu->item_height_small = menu->container_height * 2 / 3;

    menu->item_height_large = menu->container_height * 4 / 5;

  

    // 分配菜单项和颜色数组

    menu->items = (sgl_obj_t**)malloc(sizeof(sgl_obj_t*) * item_count);

    menu->colors = (sgl_color_t*)malloc(sizeof(sgl_color_t) * item_count);

    menu->pixmaps = (sgl_pixmap_t**)malloc(sizeof(sgl_pixmap_t*) * item_count);

    menu->item_texts = (char**)malloc(sizeof(char*) * item_count);

    if (!menu->items || !menu->colors || !menu->item_texts || !menu->pixmaps) {

        free(menu);

        return NULL;

    }

  

    // 默认颜色

    sgl_color_t default_colors[] = {

        SGL_COLOR_RED, SGL_COLOR_GREEN, SGL_COLOR_BLUE,

        SGL_COLOR_YELLOW, SGL_COLOR_MAGENTA, SGL_COLOR_CYAN

    };

    for (int i = 0; i < item_count; i++) {

        menu->items[i] = sgl_button_create(menu->container);

        // 设置颜色

        menu->colors[i] = default_colors[i % 6];

        // 设置位置和大小

        sgl_obj_set_pos(menu->items[i], 0, 0);

        sgl_obj_set_size(menu->items[i], 0, 0);

        sgl_button_set_color(menu->items[i], menu->colors[i]);

        // 设置按钮圆角

        sgl_button_set_radius(menu->items[i], 10);

        // 注册事件处理函数

        sgl_obj_set_event_cb(menu->items[i], menu_item_event_handler, i);

        sgl_obj_set_clickable(menu->items[i]);

        // 初始化文本和图片

        menu->item_texts[i] = NULL;

        menu->pixmaps[i] = NULL;

    }

  

    // 创建动画对象

    menu->anim = sgl_anim_create();

    if (menu->anim) {

        sgl_anim_set_data(menu->anim, menu);

        sgl_anim_set_path(menu->anim, menu_anim_path, SGL_ANIM_PATH_EASE_IN_OUT);

        sgl_anim_set_act_duration(menu->anim, 300);

        sgl_anim_set_finish_cb(menu->anim, menu_anim_finished);

        sgl_anim_set_repeat_cnt(menu->anim, 1); // 设置只播放一次

  

    }

    menu->is_animating = false; // 初始化动画状态为未进行

  

    return menu;

}
// 设置菜单项尺寸

void sliding_menu_set_item_size(sliding_menu_t* menu, int width_small, int height_small, int width_large, int height_large) {

    if (!menu) return;

    menu->item_width_small = width_small;

    menu->item_width_large = width_large;

    menu->item_height_small = height_small;

    menu->item_height_large = height_large;

}

  

// 设置是否启用环形运动

void sliding_menu_set_circular_motion(sliding_menu_t* menu, bool enable) {

    if (!menu) return;

    menu->circular_motion = enable;

}

  

// 获取环形运动开关状态

bool sliding_menu_get_circular_motion(const sliding_menu_t* menu) {

    return menu ? menu->circular_motion : false;

}

  

// 设置文本标签距离容器底部的距离

//void sliding_menu_set_text_offset(sliding_menu_t* menu, int offset_y) {

    //if (!menu) return;

    //menu->text_offset_y = offset_y;

//}

  
  

// 设置菜单项文本

void sliding_menu_set_item_text(sliding_menu_t* menu, const char* texts[]) {

    if (!menu || !texts) return;

    for (int i = 0; i < menu->item_count; i++) {

        // 如果已有文本，先释放

        if (menu->item_texts[i]) {

            free(menu->item_texts[i]);

            menu->item_texts[i] = NULL;

        }

        if (texts[i]) {

            // 复制文本

            menu->item_texts[i] = (char*)malloc(strlen(texts[i]) + 1);

            if (menu->item_texts[i]) {

                strcpy(menu->item_texts[i], texts[i]);

            }

        }

    }

}

  
  
  

// 添加设置按钮圆角的接口

void sliding_menu_set_item_radius(sliding_menu_t* menu, int index, uint8_t radius) {

    if (!menu || index < 0 || index >= menu->item_count) return;

    sgl_button_set_radius(menu->items[index], radius);

}

  

// 设置菜单项点击回调

void sliding_menu_set_click_callback(sliding_menu_t* menu, void (*callback)(int index)) {

    if (!menu) return;

    menu->item_click_callback = callback;

}

  

// 向左移动菜单

void sliding_menu_move_left(sliding_menu_t* menu) {

    if (!menu || menu->item_count <= 1) return;

    // 如果正在动画中，忽略新操作

    if (menu->is_animating) {

        //SGL_LOG_INFO("Animation in progress, ignoring left move\n");

        return;

    }

    menu->target_index = menu->current_index - 1;

    // 检查是否启用环形运动

    if (menu->circular_motion) {

        if (menu->target_index < 0) {

            menu->target_index = menu->item_count - 1;  // 循环到末尾

        }

    } else {

        // 如果未启用环形运动且已在第一个元素，则不移动

        if (menu->target_index < 0) {

            return;

        }

    }

    //SGL_LOG_INFO("Moving left: current=%d, target=%d\n", menu->current_index, menu->target_index);

    menu->anim_direction = -1;

    menu->is_animating = true; // 标记动画开始

    // 启动动画

    if (menu->anim) {

        sgl_anim_set_start_value(menu->anim, 0);

        sgl_anim_set_end_value(menu->anim, 1000);

        sgl_anim_set_repeat_cnt(menu->anim, 1); // 播放一次

        sgl_anim_start(menu->anim);

        update_sliding_menu(menu, 0.0f);

    }

}

  

// 向右移动菜单

void sliding_menu_move_right(sliding_menu_t* menu) {

    if (!menu || menu->item_count <= 1) return;

    // 如果正在动画中，忽略新操作

    if (menu->is_animating) {

        //SGL_LOG_INFO("Animation in progress, ignoring right move\n");

        return;

    }

    menu->target_index = menu->current_index + 1;

    // 检查是否启用环形运动

    if (menu->circular_motion) {

        if (menu->target_index >= menu->item_count) {

            menu->target_index = 0;  // 循环到开头

        }

    } else {

        // 如果未启用环形运动且已在最后一个元素，则不移动

        if (menu->target_index >= menu->item_count) {

            return;

        }

    }

    //SGL_LOG_INFO("Moving right: current=%d, target=%d\n", menu->current_index, menu->target_index);

    menu->anim_direction = 1;

    menu->is_animating = true; // 标记动画开始

    // 启动动画

    if (menu->anim) {

        sgl_anim_set_start_value(menu->anim, 0);

        sgl_anim_set_end_value(menu->anim, 1000);

        sgl_anim_set_repeat_cnt(menu->anim, 1); // 确保只播放一次

        sgl_anim_start(menu->anim);

        // 立即调用一次更新以开始动画

        update_sliding_menu(menu, 0.0f);

    }

}

  

// 设置菜单项颜色

void sliding_menu_set_item_color(sliding_menu_t* menu, int index, sgl_color_t color) {

    if (!menu || index < 0 || index >= menu->item_count) return;

    menu->colors[index] = color;

    sgl_button_set_color(menu->items[index], color);

}

  

// 设置菜单项图片

void sliding_menu_set_item_pixmap(sliding_menu_t* menu, int index, const sgl_pixmap_t* pixmap) {

    if (!menu || index < 0 || index >= menu->item_count) return;

    menu->pixmaps[index] = (sgl_pixmap_t*)pixmap;

}

  

// 获取当前选中项索引

int sliding_menu_get_current_index(sliding_menu_t* menu) {

    return menu ? menu->current_index : -1;

}
  

/**
 * @brief 点击滑动菜单项，触发按钮动画效果

 * @param menu 滑动菜单对象

 * @param item_index 菜单项索引

 * @param press_state 按键状态: 1表示按下, 0表示释放

 */

void sliding_menu_item_click(sliding_menu_t* menu, int item_index, int press_state) {

    // 检查参数有效性

    if (!menu || item_index < 0 || item_index >= menu->item_count) {

        SGL_LOG_ERROR("Invalid menu or item index\n");

        return;

    }

    // 获取实际选中项索引（考虑动画状态）

    int actual_index = menu->is_animating ? menu->target_index : menu->current_index;

    // 只有当前选中项才触发点击事件

    if (item_index == actual_index) {

        // 根据press_state参数决定发送按下还是释放事件

        if (press_state) {

            // 发送按下事件触发按钮动画

            sgl_event_send_obj(menu->items[item_index], SGL_EVENT_PRESSED);

        } else {

            // 发送释放事件完成按钮点击过程

            sgl_event_send_obj(menu->items[item_index], SGL_EVENT_RELEASED);

            // 调用用回调函数

            if (menu->item_click_callback) {

                SGL_LOG_INFO("Menu item %d clicked via key/mouse press!\n", item_index);

                menu->item_click_callback(item_index);

            }

        }

    }

}

  

// 示例点击回调函数

void on_menu_item_clicked(int index) {

    SGL_LOG_INFO("Menu item %d clicked!\n", index);

}

  

int main(int argc, char *argv[])

{

    SGL_UNUSED(argc);

    SGL_UNUSED(argv);

  

    int quit = 0;

    SDL_Event MouseEvent;

    sgl_port_sdl2_t* sdl2_dev = sgl_port_sdl2_init();

    if(sdl2_dev == NULL)

    {

        return -1;

    }

  

    sgl_obj_t* rect43 = sgl_button_create(NULL);

    sgl_obj_set_pos(rect43, 0, 0);

    sgl_obj_set_size(rect43, 64, 64);

    sgl_button_set_pixmap(rect43, &pixmap1);

  

    // 创建滑动菜单

    sliding_menu_t* menu = create_sliding_menu(NULL, 100, 200, 240, 135, 5);

    if (menu) {

        // 设置菜单项尺寸

        sliding_menu_set_item_size(menu, 40, 40, 55, 55);

        // 设置文本标签距离容器底部的距离

        //sliding_menu_set_text_offset(menu, 30);

        // 设置菜单项文本

        const char* menu_items[] = {"中文", "Settings", "About", "Help", "Exit"};

        sliding_menu_set_item_text(menu, menu_items);

        //sliding_menu_set_circular_motion(menu, true);// 启用环形运动

        sliding_menu_set_circular_motion(menu, false);

        // 设置点击回调

        sliding_menu_set_click_callback(menu, on_menu_item_clicked);

        //sliding_menu_set_item_pixmap(menu, 0,&test_pixmap);

        sliding_menu_set_item_pixmap(menu, 1, &pixmap1);

        update_sliding_menu(menu, 1.0f); // 显示初始状态

    }

  

    while (!quit) {

        // 使用WaitEventTimeout而不是PollEvent，减少CPU占用并改善事件响应

        if (SDL_WaitEventTimeout(&MouseEvent, 10)) {

            switch (MouseEvent.type) {

            case SDL_QUIT:

                quit = 1;

                break;

            case SDL_KEYDOWN:

                SGL_LOG_INFO("Key pressed: %d\n", MouseEvent.key.keysym.sym);

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

                    // 触发当前选中菜单项的点击事件（按下状态）

                    sliding_menu_item_click(menu, sliding_menu_get_current_index(menu), 1);

                    break;

                default:

                    SGL_LOG_INFO("Other key: %d\n", MouseEvent.key.keysym.sym);

                    break;

                }

                break;

            case SDL_KEYUP:

                SGL_LOG_INFO("Key released: %d\n", MouseEvent.key.keysym.sym);

                switch (MouseEvent.key.keysym.sym) {

                case SDLK_RETURN:

                case SDLK_KP_ENTER:

                    SGL_LOG_INFO("Enter key released\n");

                    // 触发当前选中菜单项的点击事件（释放状态）

                    sliding_menu_item_click(menu, sliding_menu_get_current_index(menu), 0);

                    break;

                }

                break;

            case SDL_MOUSEBUTTONDOWN:

                // 处理鼠标点击事件

                /*

                if (MouseEvent.button.button == SDL_BUTTON_LEFT) {

                    SGL_LOG_INFO("Mouse left button clicked at (%d, %d)\n", MouseEvent.button.x, MouseEvent.button.y);

                    // 可以在这里添加点击位置判断逻辑

                    // 现在简单地模拟点击当前选中的菜单项

                    sliding_menu_item_click(menu, sliding_menu_get_current_index(menu), 1);

                }

                */

                break;

            case SDL_MOUSEBUTTONUP:

                /*

                if (MouseEvent.button.button == SDL_BUTTON_LEFT) {

                    SGL_LOG_INFO("Mouse left button released at (%d, %d)\n", MouseEvent.button.x, MouseEvent.button.y);

                    // 触发当前选中菜单项的点击事件（释放状态）

                    sliding_menu_item_click(menu, sliding_menu_get_current_index(menu), 0);

                }

                */

                break;

            }

        }

  

        // 总是调用sgl_task_handle以确保动画系统得到更新

        sgl_task_handle();

        sgl_port_sdl2_increase_frame_count(sdl2_dev);

    }

  

    // 清理资源

    destroy_sliding_menu(menu);

    sgl_port_sdl2_deinit(sdl2_dev);

  

    return 0;

}
```
