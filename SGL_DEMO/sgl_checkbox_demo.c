/**
 * @file    sgl_checkbox_demo.c
 * @brief   SGL Checkbox 复选框控件 Demo — 覆盖所有 sgl_checkbox_xxx 接口
 *          演示多选项列表，通过 Label 的 FMT 接口实时显示各选项选中状态
 */
#include "sgl_demo.h"
#if SGD_ENABLE_CHECKBOX

/* 选项数量 */
#define CB_NUM  4

/* 复选框与状态标签的全局指针 */
static sgl_obj_t *g_cb[CB_NUM];
static sgl_obj_t *g_cb_label[CB_NUM];

/* 复选框点击回调 — 更新对应的状态标签 */
static void on_cb_click(sgl_event_t *e)
{
    if (e->type == SGL_EVENT_CLICKED) {
        /* 遍历找到被点击的复选框 */
        for (int i = 0; i < CB_NUM; i++) {
            if (g_cb[i] && sgl_event_get_target(e) == g_cb[i]) {
                bool st = sgl_checkbox_get_status(g_cb[i]);
                sgl_label_set_text_fmt_dynamic(g_cb_label[i],
                    "Option %d: %s", i + 1, st ? "ON" : "OFF");
                break;
            }
        }
    }
}

void sgd_checkbox_demo(sgl_obj_t *parent)
{
    int16_t y = SGD_MG;
    sgl_obj_t *cb;

    /* ================================================================
     * 1) 单个复选框 — 覆盖全部接口
     *    API: sgl_checkbox_create / set_text / set_font
     *         set_status / set_text_color / set_box_color
     *         set_check_color / set_radius / set_alpha / get_status
     * ================================================================ */
    cb = sgl_checkbox_create(parent);
    sgl_obj_set_pos(cb, SGD_MG, y);  sgl_obj_set_size(cb, SGD_W, SGD_H);

    /* 设置文字 */
    sgl_checkbox_set_text(cb, "[1] Demo Checkbox");
    /* 设置字体 */
    sgl_checkbox_set_font(cb, &consolas14);
    /* 设置选中 */
    sgl_checkbox_set_status(cb, true);
    /* 文字颜色 */
    sgl_checkbox_set_text_color(cb, SGL_COLOR_BLACK);
    /* 框体颜色 */
    sgl_checkbox_set_box_color(cb, SGL_COLOR_DARK_GRAY);
    /* 勾选标记颜色 */
    sgl_checkbox_set_check_color(cb, SGL_COLOR_GREEN);
    /* 圆角 */
    sgl_checkbox_set_radius(cb, 3);
    /* 透明度 */
    sgl_checkbox_set_alpha(cb, 255);
    /* 读取状态 */
    sgl_checkbox_get_status(cb);
    y += SGD_H + SGD_GAP;

    /* ================================================================
     * 2) 多选项列表 — 4 个复选框 + 状态显示标签
     *    每个复选框带一个标签，用实时显示 ON/OFF
     * ================================================================ */
    {
        int16_t cb_w = SGD_W * 2 / 5;      /* 复选框宽度 */
        int16_t lb_w = SGD_W - cb_w - 4;   /* 标签宽度 */
        int16_t item_h = SGD_H/2;            /* 每项高度 */

        for (int i = 0; i < CB_NUM; i++) {
            /* 创建复选框 */
            g_cb[i] = sgl_checkbox_create(parent);
            sgl_obj_set_pos(g_cb[i], SGD_MG, y);
            sgl_obj_set_size(g_cb[i], cb_w, item_h);
            sgl_checkbox_set_font(g_cb[i], &consolas14);
            sgl_checkbox_set_text(g_cb[i], "Option");
            /* 默认第一个选中，其余不选中 */
            sgl_checkbox_set_status(g_cb[i], (i == 0) ? true : false);
            /* 深色文字，白色背景下可见 */
            sgl_checkbox_set_text_color(g_cb[i], SGL_COLOR_BLACK);
            sgl_checkbox_set_box_color(g_cb[i], SGL_COLOR_DARK_GRAY);
            sgl_checkbox_set_check_color(g_cb[i], SGL_COLOR_GREEN);
            sgl_checkbox_set_radius(g_cb[i], 3);
            /* 注册点击回调 */
            sgl_obj_set_event_cb(g_cb[i], on_cb_click, NULL);

            /* 创建状态显示标签（右侧，FMT 显示 ON/OFF） */
            g_cb_label[i] = sgl_label_create(parent);
            sgl_obj_set_pos(g_cb_label[i], SGD_MG + cb_w + 4, y);
            sgl_obj_set_size(g_cb_label[i], lb_w, item_h);
            sgl_label_set_font(g_cb_label[i], &consolas14);
            /* 使用 FMT 接口显示状态 */
            sgl_label_set_text_fmt_dynamic(g_cb_label[i],
                "Opt %d: %s", i + 1, (i == 0) ? "ON" : "OFF");
            sgl_label_set_text_color(g_cb_label[i], SGL_COLOR_BLUE);
            /* 不设背景色，透明显示在白色屏幕上 */

            y += item_h + 2;
        }
    }
}
#endif