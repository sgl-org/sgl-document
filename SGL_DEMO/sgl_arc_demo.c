/**
 * @file    sgl_arc_demo.c
 * @brief   SGL Arc 弧形控件 Demo — 覆盖所有 sgl_arc_xxx 接口
 *          深色主题，第一个可触摸改变角度并显示百分比，
 *          第二个接入动画系统循环播放
 */
#include "sgl_demo.h"
#include <math.h>
#if SGD_ENABLE_ARC

/* 全局变量：弧一的百分比标签 + 弧二动画对象 */
static sgl_obj_t *g_hu1_lab = NULL;
static sgl_obj_t *g_hu2 = NULL;

/* 弧一触摸回调：更新标签显示 */
static void hu1_event(sgl_event_t *e)
{    
    if (e->type == SGL_EVENT_PRESSED || e->type == SGL_EVENT_RELEASED ||
        e->type == SGL_EVENT_MOVE_DOWN || e->type == SGL_EVENT_MOVE_UP ||
        e->type == SGL_EVENT_MOVE_LEFT || e->type == SGL_EVENT_MOVE_RIGHT) {
        /* arc 控件本体已经负责更新 end_angle，demo 这里只读夹角并换算百分比 */
        if (g_hu1_lab) {
            int percent = (int)(sgl_arc_get_included_angle(e->obj) * 100 / 360);
            sgl_label_set_text_fmt_dynamic(g_hu1_lab, "%d%%", percent);
        }
    }
}

/* 弧二动画路径回调 */
static void hu2_anim_path(sgl_anim_t *anim, int32_t value)
{
    (void)anim;
    if (g_hu2) {
        sgl_arc_set_end_angle(g_hu2, (int16_t)value);
    }
}

void sgd_arc_demo(sgl_obj_t *parent)
{
    /* 先创建弧一的百分比标签（放在弧一下层，避免遮挡触摸）*/
    g_hu1_lab = sgl_label_create(parent);
    sgl_obj_set_pos(g_hu1_lab, (SGL_SCREEN_WIDTH - 120) / 2, 50);
    sgl_obj_set_size(g_hu1_lab, 120, 120);
    sgl_label_set_font(g_hu1_lab, &consolas23);
    //sgl_label_set_text_color(g_hu1_lab, SGL_COLOR_WHITE);
    sgl_label_set_text_align(g_hu1_lab, SGL_ALIGN_CENTER);
    sgl_label_set_text(g_hu1_lab, "75%");

    /* 创建第一个弧形控件对象（在标签上层，触摸可穿透到弧形）*/
    sgl_obj_t *hu1 = sgl_arc_create(parent);

    /* 设置控件位置（上方居中）*/
    sgl_obj_set_pos(hu1, (SGL_SCREEN_WIDTH - 120) / 2, 50);
    /* 设置控件大小 */
    sgl_obj_set_size(hu1, 120, 120);

    /* 设置弧形起始角度 */
    sgl_arc_set_start_angle(hu1, 20);

    /* 设置弧形结束角度*/
    sgl_arc_set_end_angle(hu1, 290);

    /* 设置弧形颜色（青色）*/
    sgl_arc_set_color(hu1, SGL_COLOR_CYAN);

    /* 设置弧形背景颜色 */
    sgl_arc_set_bg_color(hu1, SGL_COLOR_NAVY);

    /* 设置透明度 */
    sgl_arc_set_alpha(hu1, 200);

    /* 设置弧形模式（环形模式）*/
    sgl_arc_set_mode(hu1, SGL_ARC_MODE_RING);

    /* 设置弧形内外半径 */
    sgl_arc_set_radius(hu1, 30, 50);

    /* 注册事件回调 */
    sgl_obj_set_event_cb(hu1, hu1_event, NULL);

   

    /* 创建第二个弧形控件对象 */
    g_hu2 = sgl_arc_create(parent);
    sgl_obj_set_pos(g_hu2, (SGL_SCREEN_WIDTH - 120) / 2, 220);
    sgl_obj_set_size(g_hu2, 120, 120);
    sgl_arc_set_start_angle(g_hu2, 0);
    sgl_arc_set_end_angle(g_hu2, 0);
    sgl_arc_set_color(g_hu2, SGL_COLOR_GOLD);
    sgl_arc_set_bg_color(g_hu2, SGL_COLOR_DARK_OLIVE_GREEN);
    sgl_arc_set_alpha(g_hu2, 220);

    /* 设置弧形模式（普通平滑模式）*/
    sgl_arc_set_mode(g_hu2, SGL_ARC_MODE_NORMAL_SMOOTH);

    /* 设置弧形内外半径 */
    sgl_arc_set_radius(g_hu2, 10, 45);

    /* 创建动画：弧二结束角度 0→360 循环 */
    {
        sgl_anim_t *a = sgl_anim_create();
        sgl_anim_set_data(a, NULL);
        sgl_anim_set_act_duration(a, 3000);
        sgl_anim_set_start_value(a, 0);
        sgl_anim_set_end_value(a, 360);
        sgl_anim_set_path(a, hu2_anim_path, SGL_ANIM_PATH_LINEAR);
        sgl_anim_start(a, SGL_ANIM_REPEAT_LOOP);
    }
}
#endif
