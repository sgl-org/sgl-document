/**
 * @file    sgl_scroll_demo.c
 * @brief   SGL Scroll 滚动条控件 Demo — 覆盖所有 sgl_scroll_xxx 接口
 *          滚动条需绑定到容器控件，使容器内超出部分可滑动查看
 *          演示：矩形容器内放置多种控件，通过垂直滚动条滑动浏览
 */
#include "sgl_demo.h"
#if SGD_ENABLE_SCROLL

static sgl_obj_t *g_gundong = NULL;

/* 加按钮回调：滚动条步进 +10 */
static void btn_step_up(sgl_event_t *e)
{
    (void)e;
    if (g_gundong) {
        uint8_t val = sgl_scroll_get_value(g_gundong);
        if (val < 200) val += 1;
        sgl_scroll_set_value(g_gundong, val);
    }
}

/* 减按钮回调：滚动条步进 -10 */
static void btn_step_dn(sgl_event_t *e)
{
    (void)e;
    if (g_gundong) {
        uint8_t val = sgl_scroll_get_value(g_gundong);
        if (val >= 10) val -= 1;
        sgl_scroll_set_value(g_gundong, val);
    }
}

void sgd_scroll_demo(sgl_obj_t *parent)
{
    /* ================================================================
     * 1) 滚动容器 — 矩形 + 子控件，内容超出容器高度
     *    子控件坐标相对于矩形，超出部分通过滚动条查看
     * ================================================================ */

    /* 创建矩形容器（可视窗口 280×220）*/
    sgl_obj_t *rongqi = sgl_rect_create(parent);
    sgl_obj_set_pos(rongqi, 20, 20);
    sgl_obj_set_size(rongqi, 280, 220);
    sgl_rect_set_color(rongqi, SGL_COLOR_DARK_GRAY);
    sgl_rect_set_radius(rongqi, 4);

    /* 在容器内添加各种控件（总高度超出容器，需要滚动）*/
    int yy = 8;

    /* 标签 */
    sgl_obj_t *lab = sgl_label_create(rongqi);
    sgl_obj_set_pos(lab, 8, yy);
    sgl_obj_set_size(lab, 260, 24);
    sgl_label_set_text(lab, "Scroll Demo Content");
    sgl_label_set_font(lab, &consolas14);
    sgl_label_set_text_color(lab, SGL_COLOR_CYAN);
    sgl_label_set_text_align(lab, SGL_ALIGN_LEFT_MID);
    yy += 30;

    /* 按钮 */
    sgl_obj_t *btn = sgl_button_create(rongqi);
    sgl_obj_set_pos(btn, 8, yy);
    sgl_obj_set_size(btn, 100, 28);
    sgl_button_set_text(btn, "Button");
    sgl_button_set_font(btn, &consolas14);
    sgl_button_set_color(btn, SGL_COLOR_NAVY);
    sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
    sgl_button_set_radius(btn, 4);
    yy += 34;

    /* 圆形 */
    sgl_obj_t *yuan = sgl_circle_create(rongqi);
    sgl_obj_set_pos(yuan, 8, yy);
    sgl_obj_set_size(yuan, 50, 50);
    sgl_circle_set_color(yuan, SGL_COLOR_CYAN);
    sgl_circle_set_radius(yuan, 22);
    sgl_circle_set_alpha(yuan, 200);
    sgl_circle_set_border_color(yuan, SGL_COLOR_NAVY);
    sgl_circle_set_border_width(yuan, 3);
    yy += 56;

    /* LED 指示灯 */
    sgl_obj_t *led = sgl_led_create(rongqi);
    sgl_obj_set_pos(led, 8, yy);
    sgl_obj_set_size(led, 36, 36);
    sgl_led_set_radius(led, 18);
    sgl_led_set_on_color(led, SGL_COLOR_GOLD);
    sgl_led_set_off_color(led, SGL_COLOR_DARK_GRAY);
    sgl_led_set_alpha(led, 200);
    sgl_led_set_status(led, true);
    yy += 42;

    /* 开关 */
    sgl_obj_t *sw = sgl_switch_create(rongqi);
    sgl_obj_set_pos(sw, 8, yy);
    sgl_obj_set_size(sw, 60, 24);
    sgl_switch_set_color(sw, SGL_COLOR_CYAN);
    sgl_switch_set_bg_color(sw, SGL_COLOR_DARK_GRAY);
    sgl_switch_set_knob_color(sw, SGL_COLOR_WHITE);
    sgl_switch_set_radius(sw, 12);
    yy += 30;

    /* 底部提示标签 */
    lab = sgl_label_create(rongqi);
    sgl_obj_set_pos(lab, 8, yy+10);
    sgl_obj_set_size(lab, 260, 24);
    sgl_label_set_text(lab, "More content below");
    sgl_label_set_font(lab, &consolas24);
    sgl_label_set_text_color(lab, SGL_COLOR_GRAY);
    sgl_label_set_text_align(lab, SGL_ALIGN_LEFT_MID);

    /* ================================================================
     * 2) 垂直滚动条 — 绑定到矩形容器，拖动即可滚动查看内部控件
     *    sgl_scroll_bind_obj 将滚动条与容器关联
     * ================================================================ */
    g_gundong = sgl_scroll_create(parent);
    sgl_obj_set_pos(g_gundong, 300, 20);
    sgl_obj_set_size(g_gundong, 16, 220);

    /* 设置滚动条颜色 */
    sgl_scroll_set_color(g_gundong, SGL_COLOR_CYAN);

    /* 设置透明度 */
    sgl_scroll_set_alpha(g_gundong, 220);

    /* 设置圆角 */
    sgl_scroll_set_radius(g_gundong, 4);

    /* 设置边框颜色 */
    sgl_scroll_set_border_color(g_gundong, SGL_COLOR_NAVY);

    /* 设置边框宽度 */
    sgl_scroll_set_border_width(g_gundong, 1);

    /* 设置滚动条粗细 */
    sgl_scroll_set_width(g_gundong, 10);

    /* 设置方向（1 = 垂直）*/
    sgl_scroll_set_direct(g_gundong, 1);

    /* 绑定到容器 — 滚动条控制容器的垂直滚动 */
    sgl_scroll_bind_obj(g_gundong, rongqi);

    /* 设置初始滚动位置 */
    sgl_scroll_set_value(g_gundong, 0);

    /* 获取当前值 */
    sgl_scroll_get_value(g_gundong);

    /* ================================================================
     * 3) 步进按钮 — 点击 + / - 手动控制滚动条步进
     * ================================================================ */
    sgl_obj_t *step_btn = sgl_button_create(parent);
    sgl_obj_set_pos(step_btn, 100, 250);
    sgl_obj_set_size(step_btn, 50, 32);
    sgl_button_set_text(step_btn, "  -  ");
    sgl_button_set_font(step_btn, &consolas14);
    sgl_button_set_color(step_btn, SGL_COLOR_NAVY);
    sgl_button_set_text_color(step_btn, SGL_COLOR_WHITE);
    sgl_button_set_radius(step_btn, 4);
    sgl_obj_set_event_cb(step_btn, btn_step_dn, NULL);

    step_btn = sgl_button_create(parent);
    sgl_obj_set_pos(step_btn, 170, 250);
    sgl_obj_set_size(step_btn, 50, 32);
    sgl_button_set_text(step_btn, "  +  ");
    sgl_button_set_font(step_btn, &consolas14);
    sgl_button_set_color(step_btn, SGL_COLOR_NAVY);
    sgl_button_set_text_color(step_btn, SGL_COLOR_WHITE);
    sgl_button_set_radius(step_btn, 4);
    sgl_obj_set_event_cb(step_btn, btn_step_up, NULL);
}
#endif
