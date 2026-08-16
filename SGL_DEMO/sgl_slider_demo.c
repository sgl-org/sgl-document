/**
 * @file    sgl_slider_demo.c
 * @brief   SGL Slider 控件 Demo — 覆盖所有 sgl_slider_xxx 接口
 *          滑动条（滑块）控件，支持水平/垂直方向，可自定义轨道/滑块/填充颜色
 */
#include "sgl_demo.h"

/* 用于显示滑动条当前值的标签 */
static sgl_obj_t *g_slider_val_label = NULL;
static sgl_obj_t *g_slider_obj = NULL;       /* 水平滑块对象，供按钮回调使用 */

/* 减按钮回调 */
static void on_dec_click(sgl_event_t *e)
{
    if (e->type == SGL_EVENT_CLICKED && g_slider_obj) {
        int16_t v = (int16_t)sgl_slider_get_value(g_slider_obj) - 5;
        if (v < 0) v = 0;
        sgl_slider_set_value(g_slider_obj, (uint8_t)v);
        sgl_label_set_text_fmt_dynamic(g_slider_val_label, "Slider: %d", (int)v);
    }
}

/* 加按钮回调 */
static void on_inc_click(sgl_event_t *e)
{
    if (e->type == SGL_EVENT_CLICKED && g_slider_obj) {
        int16_t v = (int16_t)sgl_slider_get_value(g_slider_obj) + 5;
        if (v > 100) v = 100;
        sgl_slider_set_value(g_slider_obj, (uint8_t)v);
        sgl_label_set_text_fmt_dynamic(g_slider_val_label, "Slider: %d", (int)v);
    }
}

/* 滑动条值变化回调 — 更新标签显示 */
static void on_slider_event(sgl_event_t *e)
{
    if (e->type == SGL_EVENT_PRESSED || e->type == SGL_EVENT_RELEASED ||
        e->type == SGL_EVENT_MOVE_DOWN || e->type == SGL_EVENT_MOVE_UP ||
        e->type == SGL_EVENT_MOVE_LEFT || e->type == SGL_EVENT_MOVE_RIGHT)
    {
        sgl_obj_t *sl = sgl_event_get_target(e);
        uint8_t val = sgl_slider_get_value(sl);
        if (g_slider_val_label) {
            sgl_label_set_text_fmt_dynamic(g_slider_val_label, "Slider: %d", (int)val);
        }
    }
}

void sgd_slider_demo(sgl_obj_t *parent)
{
    int16_t y = SGD_MG;
    sgl_obj_t *sl;

    /* ================================================================
     * 1) 水平滑动条 — 完整演示所有接口
     *    API: sgl_slider_create / set_value / set_fill_color
     *         set_track_color / set_knob_color / set_direct
     *         set_radius / set_thickness / set_border_width / get_value
     * ================================================================ */
    sl = sgl_slider_create(parent);
    g_slider_obj = sl;  /* 保存全局引用，供按钮回调使用 */
    sgl_obj_set_pos(sl, SGD_MG, y);
    sgl_obj_set_size(sl, SGD_W, SGD_H - 25);
    /* 注意：滑动球（knob）的大小由 sgl_obj_set_size 的高度决定，
     *       内部算法：knob_r = 高度 / 2 - 1，高度越大球越大。 */

    /* 设置填充颜色（拖动球左侧已滑过的部分） */
    //sgl_slider_set_fill_color(sl, SGL_COLOR_CYAN);

    /* 设置轨道颜色（拖动球右侧未滑过的部分） */
    //sgl_slider_set_track_color(sl, SGL_COLOR_DARK_GRAY);

    /* 设置拖动球（knob）的颜色，与轨道区分 */
    //sgl_slider_set_knob_color(sl, SGL_COLOR_YELLOW);

    /* 设置方向为水平 */
    sgl_slider_set_direct(sl, SGL_DIRECT_HORIZONTAL);

    /* 设置滑动条圆角半径 */
    sgl_slider_set_radius(sl, 4);

    /* 设置滑动条轨道的粗细（厚度越大轨道越粗） */
    sgl_slider_set_thickness(sl, 10);

    /* 设置边框宽度 */
    sgl_slider_set_border_width(sl, 1);

    /* 设置当前值（0-100） */
    sgl_slider_set_value(sl, 50);

    /* 注册事件回调，拖动滑块时实时更新标签显示 */
    sgl_obj_set_event_cb(sl, on_slider_event, NULL);

    /* 读取当前值（演示 get_value 接口） */
    sgl_slider_get_value(sl);

    y += SGD_H + SGD_GAP;

    /* 显示当前值的标签 + 加减按钮（无白底，适应白色屏幕背景） */
    {
        int16_t btn_w = 36;
        int16_t lbl_w = SGD_W - btn_w * 2 - 4;

        /* 减按钮 */
        sgl_obj_t *dec = sgl_button_create(parent);
        sgl_obj_set_pos(dec, SGD_MG, y);
        sgl_obj_set_size(dec, btn_w, SGD_H);
        sgl_button_set_font(dec, &consolas14);
        sgl_button_set_text(dec, "-");
        sgl_button_set_radius(dec, 4);
        sgl_obj_set_event_cb(dec, on_dec_click, NULL);

        /* 值标签 */
        g_slider_val_label = sgl_label_create(parent);
        sgl_obj_set_pos(g_slider_val_label, SGD_MG + btn_w + 2, y);
        sgl_obj_set_size(g_slider_val_label, lbl_w, SGD_H);
        sgl_label_set_font(g_slider_val_label, &consolas14);
        sgl_label_set_text_fmt_dynamic(g_slider_val_label, "Slider: %d", 50);
        sgl_label_set_text_color(g_slider_val_label, SGL_COLOR_BLUE);
        /* 不设背景色，透明显示在白色屏幕上 */

        /* 加按钮 */
        sgl_obj_t *inc = sgl_button_create(parent);
        sgl_obj_set_pos(inc, SGD_MG + btn_w + 2 + lbl_w + 2, y);
        sgl_obj_set_size(inc, btn_w, SGD_H);
        sgl_button_set_font(inc, &consolas14);
        sgl_button_set_text(inc, "+");
        sgl_button_set_radius(inc, 4);
        sgl_obj_set_event_cb(inc, on_inc_click, NULL);
    }
    y += SGD_H + SGD_GAP;

    /* ================================================================
     * 2) 垂直滑动条
     *    API: sgl_slider_set_direct (SGL_DIRECT_VERTICAL)
     *         sgl_slider_set_thickness (不同大小)
     * ================================================================ */
    sl = sgl_slider_create(parent);
    sgl_obj_set_pos(sl, SGD_MG, y);
    sgl_obj_set_size(sl, 20, SGD_W * 2 / 3);

    /* 设置为垂直方向 */
    sgl_slider_set_direct(sl, SGL_DIRECT_VERTICAL);

    sgl_slider_set_thickness(sl, 6);
    sgl_slider_set_value(sl, 70);
    sgl_slider_set_fill_color(sl, SGL_COLOR_LIME);
    sgl_slider_set_track_color(sl, SGL_COLOR_DARK_GRAY);
    sgl_slider_set_knob_color(sl, SGL_COLOR_YELLOW);
    sgl_slider_set_radius(sl, 4);

    y += SGD_W * 2 / 3 + SGD_GAP;
}