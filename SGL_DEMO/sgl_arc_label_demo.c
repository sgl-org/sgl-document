/**
 * @file    sgl_arc_label_demo.c
 * @brief   SGL ArcLabel 弧形标签控件 Demo — 覆盖所有 sgl_arc_label_xxx 接口
 *          第一个标签旋转动画，第二个标签正常显示
 */
#include "sgl_demo.h"
#if SGD_ENABLE_ARC_LABEL

static sgl_obj_t *g_wenzi1 = NULL;

/* 旋转动画回调 */
static void spin_anim_path(sgl_anim_t *anim, int32_t value)
{
    (void)anim;
    if (g_wenzi1) {
        sgl_arc_label_set_angle(g_wenzi1, (int16_t)value);
    }
}

void sgd_arc_label_demo(sgl_obj_t *parent)
{
    /* ================================================================
     * 1) 旋转标签 — 接入动画系统，角度 0→360 循环
     * ================================================================ */
    g_wenzi1 = sgl_arc_label_create(parent);

    /* 设置控件位置 */
    sgl_obj_set_pos(g_wenzi1, 60, 50);
    /* 设置控件大小 */
    sgl_obj_set_size(g_wenzi1, 100, 30);

    /* 设置文字 */
    sgl_arc_label_set_text(g_wenzi1, "Spin");

    /* 设置字体 */
    sgl_arc_label_set_font(g_wenzi1, &consolas14);

    /* 设置文字颜色 */
    sgl_arc_label_set_text_color(g_wenzi1, SGL_COLOR_CYAN);

    /* 设置背景颜色 */
    sgl_arc_label_set_bg_color(g_wenzi1, SGL_COLOR_DARK_GRAY);

    /* 设置圆角 */
    sgl_arc_label_set_radius(g_wenzi1, 4);

    /* 设置文字对齐 */
    sgl_arc_label_set_text_align(g_wenzi1, SGL_ALIGN_CENTER);

    /* 设置透明度 */
    sgl_arc_label_set_alpha(g_wenzi1, 220);

    /* 设置文字偏移 */
    sgl_arc_label_set_text_offset(g_wenzi1, 0, 0);

    /* 设置旋转原点位置 */
    sgl_arc_label_set_orig_pos(g_wenzi1, 60, 50);

    /* 设置旋转原点大小 */
    sgl_arc_label_set_orig_size(g_wenzi1, 100, 30);

    /* 设置初始角度 */
    sgl_arc_label_set_angle(g_wenzi1, 0);

    /* 获取当前角度 */
    sgl_arc_label_get_angle(g_wenzi1);

    /* 创建旋转动画：角度 0→360 循环 */
    {
        sgl_anim_t *a = sgl_anim_create();
        sgl_anim_set_data(a, NULL);
        sgl_anim_set_act_duration(a, 3000);
        sgl_anim_set_start_value(a, 0);
        sgl_anim_set_end_value(a, 360);
        sgl_anim_set_path(a, spin_anim_path, SGL_ANIM_PATH_LINEAR);
        sgl_anim_start(a, SGL_ANIM_REPEAT_LOOP);
    }

    /* ================================================================
     * 2) 普通标签 — 不旋转，展示长文本和 FMT 动态接口
     * ================================================================ */
    sgl_obj_t *wenzi2 = sgl_arc_label_create(parent);
    sgl_obj_set_pos(wenzi2, 60, 160);
    sgl_obj_set_size(wenzi2, 200, 30);

    /* 设置字体 */
    sgl_arc_label_set_font(wenzi2, &consolas14);

    /* 设置文字颜色 */
    sgl_arc_label_set_text_color(wenzi2, SGL_COLOR_GOLD);

    /* 设置背景颜色 */
    sgl_arc_label_set_bg_color(wenzi2, SGL_COLOR_DARK_GRAY);

    /* 设置圆角 */
    sgl_arc_label_set_radius(wenzi2, 4);

    /* 设置文字对齐 */
    sgl_arc_label_set_text_align(wenzi2, SGL_ALIGN_CENTER);

    /* 设置透明度 */
    sgl_arc_label_set_alpha(wenzi2, 200);

    /* 使用 FMT 动态接口设置文本 */
    sgl_arc_label_set_text_fmt_dynamic(wenzi2, "ArcLabel Demo");
}
#endif
