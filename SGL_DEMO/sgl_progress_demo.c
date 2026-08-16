/**
 * @file    sgl_progress_demo.c
 * @brief   SGL Progress 进度条控件 Demo — 覆盖所有 sgl_progress_xxx 接口
 *          进度条用于显示任务的完成进度，支持填充色/轨道色/圆角/边框/间隙等
 */
#include "sgl_demo.h"
#if SGD_ENABLE_PROGRESS

/* 动画进度条相关全局变量 */
static sgl_obj_t *g_anim_progress = NULL;    /* 动画进度条对象 */
static sgl_obj_t *g_anim_label = NULL;        /* 进度值显示标签 */
static sgl_anim_t *g_anim = NULL;             /* 动画对象 */

/* 动画路径回调 — 每帧更新进度条值和标签文字 */
static void anim_path_cb(sgl_anim_t *anim, int32_t value)
{
    if (g_anim_progress) {
        sgl_progress_set_value(g_anim_progress, (uint8_t)value);
    }
    if (g_anim_label) {
        sgl_label_set_text_fmt_dynamic(g_anim_label, "%d%%", (int)value);
    }
}

void sgd_progress_demo(sgl_obj_t *parent)
{
    int16_t y = SGD_MG;
    sgl_obj_t *pr;

    /* ================================================================
     * 1) 完整功能进度条 — 演示所有接口
     *    API: sgl_progress_create / set_value / set_fill_color
     *         set_track_color / set_fill_alpha / set_track_alpha
     *         set_radius / set_border_width / set_border_color
     *         set_fill_gap / set_fill_radius / set_fill_width / get_value
     * ================================================================ */
    pr = sgl_progress_create(parent);
    sgl_obj_set_pos(pr, SGD_MG, y);
    sgl_obj_set_size(pr, SGD_W, SGD_H);

    /* 设置进度值 65% */
    sgl_progress_set_value(pr, 65);
    /* 设置填充颜色 */
    sgl_progress_set_fill_color(pr, SGL_COLOR_LIME);
    /* 设置轨道颜色 */
    sgl_progress_set_track_color(pr, SGL_COLOR_DARK_GRAY);
    /* 设置填充透明度 */
    sgl_progress_set_fill_alpha(pr, 200);
    /* 设置轨道透明度 */
    sgl_progress_set_track_alpha(pr, 100);
    /* 设置圆角半径 */
    sgl_progress_set_radius(pr, 6);
    /* 设置边框宽度 */
    sgl_progress_set_border_width(pr, 1);
    /* 设置边框颜色 */
    sgl_progress_set_border_color(pr, SGL_COLOR_CYAN);
    /* 设置填充间隙大小 */
    sgl_progress_set_fill_gap(pr, 2);
    /* 设置填充部分的圆角半径 */
    sgl_progress_set_fill_radius(pr, 4);
    /* 设置填充宽度 */
    sgl_progress_set_fill_width(pr, 8);
    /* 读取当前进度值 */
    sgl_progress_get_value(pr);
    y += SGD_H + SGD_GAP;

    /* ================================================================
     * 2) 动画循环进度条 — 0→100→0→100 循环往复
     *    使用 SGL 动画系统驱动进度值，并在中间显示百分比文字
     * ================================================================ */
    g_anim_progress = sgl_progress_create(parent);
    sgl_obj_set_pos(g_anim_progress, SGD_MG, y);
    sgl_obj_set_size(g_anim_progress, SGD_W, SGD_H + 10);

    /* 设置进度值 0% */
    sgl_progress_set_value(g_anim_progress, 0);
    /* 设置填充颜色 */
    sgl_progress_set_fill_color(g_anim_progress, SGL_COLOR_RED);
    /* 设置轨道颜色 */
    sgl_progress_set_track_color(g_anim_progress, SGL_COLOR_DARK_GRAY);
    /* 设置圆角半径 */
    sgl_progress_set_radius(g_anim_progress, 6);

    /* 在进度条中间创建标签，显示当前百分比（无背景色，透明叠加） */
    g_anim_label = sgl_label_create(parent);
    sgl_obj_set_pos(g_anim_label, SGD_MG, y);
    sgl_obj_set_size(g_anim_label, SGD_W, SGD_H + 10);
    sgl_label_set_font(g_anim_label, &consolas14);
    sgl_label_set_text(g_anim_label, "0%");
    sgl_label_set_text_color(g_anim_label, SGL_COLOR_WHITE);
    sgl_label_set_text_align(g_anim_label, SGL_ALIGN_CENTER);

    /* 创建动画：0 → 100，周期 2000ms */
    g_anim = sgl_anim_create();
    sgl_anim_set_data(g_anim, NULL);
    sgl_anim_set_act_duration(g_anim, 1000);
    sgl_anim_set_start_value(g_anim, 0);
    sgl_anim_set_end_value(g_anim, 100);
    sgl_anim_set_path(g_anim, anim_path_cb, SGL_ANIM_PATH_LINEAR);
    sgl_anim_start(g_anim, SGL_ANIM_REPEAT_LOOP);

    y += SGD_H + 10 + SGD_GAP;
}
#endif