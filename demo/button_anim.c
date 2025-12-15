#include <SDL.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

#include <sgl.h>
#include <sgl_font.h>

typedef struct sgl_port_sdl2 sgl_port_sdl2_t;

sgl_port_sdl2_t* sgl_port_sdl2_init(void);
size_t sgl_port_sdl2_get_frame_count(sgl_port_sdl2_t* sdl2_dev);
void sgl_port_sdl2_increase_frame_count(sgl_port_sdl2_t* sdl2_dev);
void sgl_port_sdl2_deinit(sgl_port_sdl2_t* sdl2_dev);
void flush_window_callback(void *param);

// 定义动画缓动函数类型宏，默认使用缓入缓出效果
/*
SGL_ANIM_PATH_EASE_IN_OUT - 缓入缓出（默认）
SGL_ANIM_PATH_EASE_IN - 缓入
SGL_ANIM_PATH_EASE_OUT - 缓出
SGL_ANIM_PATH_LINEAR - 线性
*/
#ifndef ANIM_PATH_FUNCTION
#define ANIM_PATH_FUNCTION SGL_ANIM_PATH_LINEAR
#endif


/**
 * 位置动画路径函数 - 控制按钮的X坐标位置
 */
static void position_anim_path(sgl_anim_t *anim, int32_t value)
{
    sgl_obj_t *obj = (sgl_obj_t *)anim->data;
    if (obj) {
        sgl_pos_t pos = sgl_obj_get_pos(obj);
        sgl_obj_set_pos(obj, (int16_t)value, pos.y);
    }
}

/**
 * 尺寸动画路径函数 - 控制按钮的宽度和高度
 */
static void size_anim_path(sgl_anim_t *anim, int32_t value)
{
    sgl_obj_t *obj = (sgl_obj_t *)anim->data;
    if (obj) {
        // 保持宽高相等，制作缩放效果
        sgl_obj_set_size(obj, (uint16_t)value, (uint16_t)value);
    }
}

/**
 * 透明度动画路径函数 - 控制按钮的透明度
 */
static void alpha_anim_path(sgl_anim_t *anim, int32_t value)
{
    sgl_obj_t *obj = (sgl_obj_t *)anim->data;
    if (obj) {
        sgl_button_set_alpha(obj, (uint8_t)value);
    }
}

/**
 * 颜色动画路径函数 - 控制按钮的颜色
 */
static void color_anim_path(sgl_anim_t *anim, int32_t value)
{
    sgl_obj_t *obj = (sgl_obj_t *)anim->data;
    if (obj) {
        // 创建彩虹色渐变效果
        // 将0-120的值映射到0-360度的色相
        uint16_t hue = (value * 3) % 360;
        uint8_t r, g, b;
        
        // 简单的彩虹色计算
        if (hue < 60) {
            r = 255;
            g = (uint8_t)(hue * 255 / 60);
            b = 0;
        } else if (hue < 120) {
            r = (uint8_t)((120 - hue) * 255 / 60);
            g = 255;
            b = 0;
        } else if (hue < 180) {
            r = 0;
            g = 255;
            b = (uint8_t)((hue - 120) * 255 / 60);
        } else if (hue < 240) {
            r = 0;
            g = (uint8_t)((240 - hue) * 255 / 60);
            b = 255;
        } else if (hue < 300) {
            r = (uint8_t)((hue - 240) * 255 / 60);
            g = 0;
            b = 255;
        } else {
            r = 255;
            g = 0;
            b = (uint8_t)((360 - hue) * 255 / 60);
        }
        
        // 使用SGL的RGB宏创建颜色
        sgl_color_t color = sgl_rgb(r, g, b);
        sgl_button_set_color(obj, color);
    }
}

/**
 * 边框动画路径函数 - 控制按钮的边框宽度
 */
static void border_anim_path(sgl_anim_t *anim, int32_t value)
{
    sgl_obj_t *obj = (sgl_obj_t *)anim->data;
    if (obj) {
        sgl_button_set_border_width(obj, (uint8_t)value);
    }
}

/**
 * 圆角动画路径函数 - 控制按钮的圆角半径
 */
static void radius_anim_path(sgl_anim_t *anim, int32_t value)
{
    sgl_obj_t *obj = (sgl_obj_t *)anim->data;
    if (obj) {
        sgl_button_set_radius(obj, (uint8_t)value);
    }
}
/**
 * 中心扩展动画路径函数 - 控制按钮在保持中心位置的同时变大
 */
static void center_expand_anim_path(sgl_anim_t *anim, int32_t value)
{
    sgl_obj_t *obj = (sgl_obj_t *)anim->data;
    if (obj) {
        // 获取按钮原始中心位置
        sgl_pos_t pos = sgl_obj_get_pos(obj);
        uint16_t width = sgl_obj_get_width(obj);
        uint16_t height = sgl_obj_get_height(obj);
        
        int16_t center_x = pos.x + width / 2;
        int16_t center_y = pos.y + height / 2;
        
        // 设置新的尺寸
        sgl_obj_set_size(obj, (uint16_t)value, (uint16_t)value);
        
        // 计算位置中心
        pos.x = center_x - (int16_t)value / 2;
        pos.y = center_y - (int16_t)value / 2;
        sgl_obj_set_pos(obj, pos.x, pos.y);
    }
}
/**
 * 动画完成回调函数 - 实现循环动画
 */
static void anim_finish_cb(sgl_anim_t *anim)
{
    // 交换起始值和结束值以创建循环动画
    int32_t tmp = anim->start_value;
    anim->start_value = anim->end_value;
    anim->end_value = tmp;
}

/**
 * 创建位置动画按钮
 */
static void create_position_anim_buttons(sgl_obj_t *parent)
{
    // 创建标题
    sgl_obj_t *label = sgl_label_create(parent);
    sgl_obj_set_pos(label, 0, 20);
    sgl_obj_set_size(label, 200, 20);
    sgl_label_set_text(label, "Position");
    sgl_label_set_text_color(label, SGL_COLOR_WHITE);
    sgl_label_set_font(label, &consolas24);
    
    // 创建演示按钮
    sgl_obj_t *btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, 30, 50);
    sgl_obj_set_size(btn, 80, 40);
    sgl_button_set_text(btn, "Move");
    sgl_button_set_color(btn, SGL_COLOR_BLUE);
    sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
    sgl_button_set_font(btn, &consolas24);
    
    // 创建位置动画
    sgl_anim_t *anim = sgl_anim_create();
    sgl_anim_set_data(anim, btn);
    sgl_anim_set_act_duration(anim, 2000);
    sgl_anim_set_start_value(anim, 30);
    sgl_anim_set_end_value(anim, 150);
    sgl_anim_set_path(anim, position_anim_path, ANIM_PATH_FUNCTION);
    sgl_anim_set_repeat_cnt(anim, SGL_ANIM_REPEAT_LOOP);
    sgl_anim_set_finish_cb(anim, anim_finish_cb);
    sgl_anim_start(anim);
}

/**
 * 创建尺寸动画按钮
 */
extern const unsigned char gImage_2[8192];
const sgl_pixmap_t setting_pixmap = {
    .width = 64,
    .height = 64,
    .bitmap = gImage_2,
};
static void create_size_anim_buttons(sgl_obj_t *parent)
{
    // 创建标题
    sgl_obj_t *label = sgl_label_create(parent);
    sgl_obj_set_pos(label, 0, 120);
    sgl_obj_set_size(label, 200, 20);
    sgl_label_set_text(label, "Size");
    sgl_label_set_text_color(label, SGL_COLOR_WHITE);
    sgl_label_set_font(label, &consolas24);
    
    // 创建演示按钮
    sgl_obj_t *btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, 30, 150);
    sgl_obj_set_size(btn, 50, 50);
    //sgl_button_set_text(btn, "Size");
    sgl_button_set_color(btn, SGL_COLOR_GREEN);
    //sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
    sgl_button_set_font(btn, &consolas24);
    sgl_button_set_pixmap(btn, &setting_pixmap);
    
    // 创建尺寸动画
    sgl_anim_t *anim = sgl_anim_create();
    sgl_anim_set_data(anim, btn);
    sgl_anim_set_act_duration(anim, 1500);
    sgl_anim_set_start_value(anim, 50);
    sgl_anim_set_end_value(anim, 80);
    sgl_anim_set_path(anim, size_anim_path, ANIM_PATH_FUNCTION);
    sgl_anim_set_repeat_cnt(anim, SGL_ANIM_REPEAT_LOOP);
    sgl_anim_set_finish_cb(anim, anim_finish_cb);
    sgl_anim_start(anim);
}

/**
 * 创建透明度动画按钮
 */
static void create_alpha_anim_buttons(sgl_obj_t *parent)
{
    // 创建标题
    sgl_obj_t *label = sgl_label_create(parent);
    sgl_obj_set_pos(label, 0, 230);
    sgl_obj_set_size(label, 200, 20);
    sgl_label_set_text(label, "Alpha");
    sgl_label_set_text_color(label, SGL_COLOR_WHITE);
    sgl_label_set_font(label, &consolas24);
    
    // 创建演示按钮
    sgl_obj_t *btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, 30, 260);
    sgl_obj_set_size(btn, 80, 40);
    sgl_button_set_text(btn, "Alpha");
    sgl_button_set_color(btn, SGL_COLOR_RED);
    sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
    sgl_button_set_font(btn, &consolas24);
    
    // 创建透明度动画
    sgl_anim_t *anim = sgl_anim_create();
    sgl_anim_set_data(anim, btn);
    sgl_anim_set_act_duration(anim, 2000);
    sgl_anim_set_start_value(anim, 10);
    sgl_anim_set_end_value(anim, 255);
    sgl_anim_set_path(anim, alpha_anim_path, ANIM_PATH_FUNCTION);
    sgl_anim_set_repeat_cnt(anim, SGL_ANIM_REPEAT_LOOP);
    sgl_anim_set_finish_cb(anim, anim_finish_cb);
    sgl_anim_start(anim);
}

/**
 * 创建颜色动画按钮
 */
static void create_color_anim_buttons(sgl_obj_t *parent)
{
    // 创建标题
    sgl_obj_t *label = sgl_label_create(parent);
    sgl_obj_set_pos(label, 180, 20);
    sgl_obj_set_size(label, 200, 20);
    sgl_label_set_text(label, "Color Animation");
    sgl_label_set_text_color(label, SGL_COLOR_WHITE);
    sgl_label_set_font(label, &consolas24);
    
    // 创建演示按钮
    sgl_obj_t *btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, 180, 50);
    sgl_obj_set_size(btn, 80, 40);
    sgl_button_set_text(btn, "Color");
    sgl_button_set_alpha(btn, 128);
    sgl_button_set_color(btn, SGL_COLOR_RED);
    sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
    sgl_button_set_font(btn, &consolas24);
    
    // 创建颜色动画
    sgl_anim_t *anim = sgl_anim_create();
    sgl_anim_set_data(anim, btn);
    sgl_anim_set_act_duration(anim, 2000);
    sgl_anim_set_start_value(anim, 0);
    sgl_anim_set_end_value(anim, 120);
    sgl_anim_set_path(anim, color_anim_path, ANIM_PATH_FUNCTION);
    sgl_anim_set_repeat_cnt(anim, SGL_ANIM_REPEAT_LOOP);
    sgl_anim_set_finish_cb(anim, anim_finish_cb);
    sgl_anim_start(anim);
}

/**
 * 创建边框动画按钮
 */
static void create_border_anim_buttons(sgl_obj_t *parent)
{
    // 创建标题
    sgl_obj_t *label = sgl_label_create(parent);
    sgl_obj_set_pos(label, 180, 120);
    sgl_obj_set_size(label, 200, 20);
    sgl_label_set_text(label, "Border Animation");
    sgl_label_set_text_color(label, SGL_COLOR_WHITE);
    sgl_label_set_font(label, &consolas24);
    
    // 创建演示按钮
    sgl_obj_t *btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, 180, 150);
    sgl_obj_set_size(btn, 80, 40);
    sgl_button_set_text(btn, "Border");
    sgl_button_set_color(btn, SGL_COLOR_YELLOW);
    sgl_button_set_text_color(btn, SGL_COLOR_BLACK);
    sgl_button_set_font(btn, &consolas24);
    sgl_button_set_border_color(btn, SGL_COLOR_RED_ORANGE);
    
    // 创建边框动画
    sgl_anim_t *anim = sgl_anim_create();
    sgl_anim_set_data(anim, btn);
    sgl_anim_set_act_duration(anim, 1500);
    sgl_anim_set_start_value(anim, 0);
    sgl_anim_set_end_value(anim, 5);
    sgl_anim_set_path(anim, border_anim_path, ANIM_PATH_FUNCTION);
    sgl_anim_set_repeat_cnt(anim, SGL_ANIM_REPEAT_LOOP);
    sgl_anim_set_finish_cb(anim, anim_finish_cb);
    sgl_anim_start(anim);
}

/**
 * 创建圆角动画按钮
 */
static void create_radius_anim_buttons(sgl_obj_t *parent)
{
    // 创建标题
    sgl_obj_t *label = sgl_label_create(parent);
    sgl_obj_set_pos(label, 180, 230);
    sgl_obj_set_size(label, 200, 20);
    sgl_label_set_text(label, "Radius Animation");
    sgl_label_set_text_color(label, SGL_COLOR_WHITE);
    sgl_label_set_font(label, &consolas24);
    
    // 创建演示按钮
    sgl_obj_t *btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, 180, 260);
    sgl_obj_set_size(btn, 80, 40);
    sgl_button_set_text(btn, "Radius");
    sgl_button_set_color(btn, SGL_COLOR_MAGENTA);
    sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
    sgl_button_set_font(btn, &consolas24);
    
    // 创建圆角动画
    sgl_anim_t *anim = sgl_anim_create();
    sgl_anim_set_data(anim, btn);
    sgl_anim_set_act_duration(anim, 1500);
    sgl_anim_set_start_value(anim, 0);
    sgl_anim_set_end_value(anim, 20);
    sgl_anim_set_path(anim, radius_anim_path, ANIM_PATH_FUNCTION);
    sgl_anim_set_repeat_cnt(anim, SGL_ANIM_REPEAT_LOOP);
    sgl_anim_set_finish_cb(anim, anim_finish_cb);
    sgl_anim_start(anim);
}

/**
 * 创建中心扩展动画按钮
 */
static void create_center_expand_anim_button(sgl_obj_t *parent)
{
    // 创建标题
    sgl_obj_t *label = sgl_label_create(parent);
    sgl_obj_set_pos(label, 520, 120);
    sgl_obj_set_size(label, 200, 20);
    sgl_label_set_text(label, "Center Expand");
    sgl_label_set_text_color(label, SGL_COLOR_WHITE);
    sgl_label_set_font(label, &consolas24);
    
    // 创建演示按钮（位于屏幕右侧中央）
    sgl_obj_t *btn = sgl_button_create(parent);
    // 初始尺寸40x40，位于屏幕右侧中央
    sgl_obj_set_pos(btn, 600, 180);
    sgl_obj_set_size(btn, 40, 40);
    sgl_button_set_text(btn, "中文");
    sgl_button_set_color(btn, SGL_COLOR_CYAN);
    sgl_button_set_text_color(btn, SGL_COLOR_BLACK);
    sgl_button_set_radius(btn, 10);    
    sgl_button_set_font(btn, &consolas24);
    
    // 创建中心扩展动画
    sgl_anim_t *anim = sgl_anim_create();
    sgl_anim_set_data(anim, btn);
    sgl_anim_set_act_duration(anim, 2000);
    sgl_anim_set_start_value(anim, 40);
    sgl_anim_set_end_value(anim,100);
    sgl_anim_set_path(anim, center_expand_anim_path, ANIM_PATH_FUNCTION);
    sgl_anim_set_repeat_cnt(anim, SGL_ANIM_REPEAT_LOOP);
    sgl_anim_set_finish_cb(anim, anim_finish_cb);
    sgl_anim_start(anim);
}
int main(int argc, char *argv[])
{
    SGL_UNUSED(argc);
    SGL_UNUSED(argv);

    int quit = 0;
    SDL_Event MouseEvent;
    sgl_port_sdl2_t* sdl2_dev = NULL;

    sdl2_dev = sgl_port_sdl2_init();
    if(sdl2_dev == NULL) 
    {
        return -1;
    }

    // 初始化SGL
    sgl_init();

    /* 创建主页面 */
    sgl_obj_t *page = sgl_obj_create(NULL);
    sgl_page_set_color(page, sgl_rgb(127,127, 127));

    // 创建各种动画演示按钮
    create_position_anim_buttons(page);
    create_size_anim_buttons(page);
    create_alpha_anim_buttons(page);
    create_color_anim_buttons(page);
    create_border_anim_buttons(page);
    create_radius_anim_buttons(page);
    create_center_expand_anim_button(page);

    /* 载入页面 */
    sgl_screen_load(page);

    while (!quit) {
        SDL_PollEvent(&MouseEvent);
        switch (MouseEvent.type) {
        case SDL_QUIT:
            quit = 1;
            break;
        }

        sgl_task_handle();
        sgl_port_sdl2_increase_frame_count(sdl2_dev);

      
        SDL_Delay(10);
    }

    sgl_port_sdl2_deinit(sdl2_dev);

    return 0;
}
