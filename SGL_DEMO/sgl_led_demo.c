/**
 * @file    sgl_led_demo.c
 * @brief   SGL LED 指示灯控件 Demo — 覆盖所有 sgl_led_xxx 接口
 *          按钮控制 LED1，开关控制 LED2
 */
#include "sgl_demo.h"
#if SGD_ENABLE_LED

/* 按钮回调：切换 LED1 亮灭 */
static void btn_toggle_led(sgl_event_t *e)
{
    if (e->type == SGL_EVENT_CLICKED) {
        sgl_obj_t *led = (sgl_obj_t *)e->event_data;
        if (sgl_led_get_status(led)) {
            sgl_led_off(led);
        } else {
            sgl_led_on(led);
        }
    }
}

/* 开关回调：同步 LED2 状态 */
static void switch_toggle_led(sgl_event_t *e)
{
    if (e->type == SGL_EVENT_CLICKED) {
        sgl_obj_t *led = (sgl_obj_t *)e->event_data;
        sgl_obj_t *sw = (sgl_obj_t *)e->obj;
        if (sgl_switch_get_status(sw)) {
            sgl_led_on(led);
        } else {
            sgl_led_off(led);
        }
    }
}

void sgd_led_demo(sgl_obj_t *parent)
{
    /* ================================================================
     * LED1 — 青色，默认点亮，由按钮控制
     * ================================================================ */
    sgl_obj_t *led1 = sgl_led_create(parent);
    sgl_obj_set_pos(led1, 60, 40);
    sgl_obj_set_size(led1, 60, 60);

    /* 设置 LED 圆角半径 */
    sgl_led_set_radius(led1, 30);

    /* 设置点亮时的颜色（青色）*/
    sgl_led_set_on_color(led1, SGL_COLOR_CYAN);

    /* 设置熄灭时的颜色 */
    sgl_led_set_off_color(led1, SGL_COLOR_DARK_GRAY);

    /* 设置背景颜色 */
    sgl_led_set_bg_color(led1, SGL_COLOR_DARK_GRAY);

    /* 设置透明度 */
    sgl_led_set_alpha(led1, 220);

    /* 设置状态为点亮 */
    sgl_led_set_status(led1, true);
    sgl_led_on(led1);

    /* 获取当前状态 */
    bool sta = sgl_led_get_status(led1);
    (void)sta;

    /* 控制按钮 */
    sgl_obj_t *btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, 20, 120);
    sgl_obj_set_size(btn, 120, 32);
    sgl_button_set_text(btn, "Toggle LED1");
    sgl_button_set_font(btn, &consolas14);
    sgl_button_set_color(btn, SGL_COLOR_NAVY);
    sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
    sgl_button_set_radius(btn, 4);
    sgl_obj_set_event_cb(btn, btn_toggle_led, led1);

    /* ================================================================
     * LED2 — 金色，默认熄灭，由开关控制
     * ================================================================ */
    sgl_obj_t *led2 = sgl_led_create(parent);
    sgl_obj_set_pos(led2, 200, 40);
    sgl_obj_set_size(led2, 60, 60);
    sgl_led_set_radius(led2, 30);
    sgl_led_set_on_color(led2, SGL_COLOR_GOLD);
    sgl_led_set_off_color(led2, SGL_COLOR_DARK_GRAY);
    sgl_led_set_bg_color(led2, SGL_COLOR_DARK_GRAY);
    sgl_led_set_alpha(led2, 180);
    sgl_led_off(led2);

    /* 控制开关 */
    sgl_obj_t *sw = sgl_switch_create(parent);
    sgl_obj_set_pos(sw, 190, 120);
    sgl_obj_set_size(sw, 80, 32);
    sgl_switch_set_color(sw, SGL_COLOR_GOLD);
    sgl_switch_set_bg_color(sw, SGL_COLOR_DARK_GRAY);
    sgl_switch_set_knob_color(sw, SGL_COLOR_WHITE);
    sgl_switch_set_radius(sw, 16);
    sgl_switch_set_alpha(sw, 220);
    sgl_switch_set_status(sw, false);
    sgl_obj_set_event_cb(sw, switch_toggle_led, led2);
}
#endif
