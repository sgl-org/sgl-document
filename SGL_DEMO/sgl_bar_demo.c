/**
 * @file    sgl_bar_demo.c
 * @brief   SGL Bar 条形图控件 Demo — 覆盖所有 sgl_bar_xxx 接口
 *          条形图用于直观显示数值，支持水平/垂直方向
 */
#include "sgl_demo.h"
#if SGD_ENABLE_BAR

extern const sgl_pixmap_t pic1_pixmap;

/* 动画条形图相关全局变量 */
static sgl_obj_t *g_bar_anim = NULL;
static sgl_obj_t *g_bar_label = NULL;

/* 动画路径回调 */
static void bar_anim_path(sgl_anim_t *anim, int32_t value)
{
    if (g_bar_anim) {
        sgl_bar_set_value(g_bar_anim, (uint8_t)value);
    }
    if (g_bar_label) {
        sgl_label_set_text_fmt_dynamic(g_bar_label, "%d%%", (int)value);
    }
}

void sgd_bar_demo(sgl_obj_t *parent)
{
    int16_t y = SGD_MG;
    sgl_obj_t *bar;

    /* ================================================================
     * 1) 完整功能条形图 — 演示所有接口
     *    API: sgl_bar_create / set_value / set_fill_color
     *         set_track_color / set_direct / set_radius
     *         set_border_width / set_border_color / set_alpha
     *         set_pixmap / get_value
     * ================================================================ */
    bar = sgl_bar_create(parent);
    sgl_obj_set_pos(bar, SGD_MG, y);
    sgl_obj_set_size(bar, SGD_W, 24);

    /* 设置当前值（0-127） */
    sgl_bar_set_value(bar, 80);
		
    /* 设置填充颜色 */
    sgl_bar_set_fill_color(bar, SGL_COLOR_RED);
    /* 设置轨道颜色 */
    sgl_bar_set_track_color(bar, SGL_COLOR_TOMATO);
    /* 设置方向（水平） */
    sgl_bar_set_direct(bar, SGL_DIRECT_HORIZONTAL);
    /* 设置圆角半径 */
    sgl_bar_set_radius(bar, 4);
    /* 设置边框宽度 */
    sgl_bar_set_border_width(bar, 1);
    /* 设置边框颜色 */
    //sgl_bar_set_border_color(bar, SGL_COLOR_WHITE);
    /* 设置透明度 */
    sgl_bar_set_alpha(bar, 20);
    /* 设置背景图片 */
    sgl_bar_set_pixmap(bar, &pic1_pixmap);//这个接口待评估删除 
    /* 读取当前值 */
    sgl_bar_get_value(bar);
    y += 24 + SGD_GAP;

    /* 第二个条形图 — 不同颜色（无图片） */
    bar = sgl_bar_create(parent);
    sgl_obj_set_pos(bar, SGD_MG, y);
    sgl_obj_set_size(bar, SGD_W, 24);
    sgl_bar_set_value(bar, 45);
    sgl_bar_set_fill_color(bar, SGL_COLOR_RED);
    sgl_bar_set_track_color(bar, SGL_COLOR_DARK_GRAY);
    sgl_bar_set_radius(bar, 4);
    y += 24 + SGD_GAP;

    /* ================================================================
     * 2) 动画循环条形图 — 0→100→0→100 循环（跳变回 0）
     *    使用 SGL 动画系统驱动，到 100% 后直接跳回 0% 重新开始
     * ================================================================ */
    g_bar_anim = sgl_bar_create(parent);
    sgl_obj_set_pos(g_bar_anim, SGD_MG, y);
    sgl_obj_set_size(g_bar_anim, SGD_W, 30);

    sgl_bar_set_value(g_bar_anim, 0);
    sgl_bar_set_fill_color(g_bar_anim, SGL_COLOR_GOLD);
    sgl_bar_set_track_color(g_bar_anim, SGL_COLOR_DARK_GRAY);
    sgl_bar_set_radius(g_bar_anim, 4);

    /* 值标签（居中叠加，无背景色） */
    g_bar_label = sgl_label_create(parent);
    sgl_obj_set_pos(g_bar_label, SGD_MG, y);
    sgl_obj_set_size(g_bar_label, SGD_W, 30);
    sgl_label_set_font(g_bar_label, &consolas14);
    sgl_label_set_text(g_bar_label, "0%");
    sgl_label_set_text_color(g_bar_label, SGL_COLOR_WHITE);
    sgl_label_set_text_align(g_bar_label, SGL_ALIGN_CENTER);

    /* 创建动画：0 → 100，循环，到 100 后自动跳回 0 重新开始 */
    {
        sgl_anim_t *a = sgl_anim_create();
        sgl_anim_set_data(a, NULL);
        sgl_anim_set_act_duration(a, 2000);
        sgl_anim_set_start_value(a, 0);
        sgl_anim_set_end_value(a, 100);
        sgl_anim_set_path(a, bar_anim_path, SGL_ANIM_PATH_LINEAR);
        sgl_anim_start(a, SGL_ANIM_REPEAT_LOOP);
    }
    y += 30 + SGD_GAP;
}
#endif