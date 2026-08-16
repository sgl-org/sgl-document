/**
 * @file    sgl_gauge_demo.c
 * @brief   SGL Gauge 仪表盘控件 Demo — 覆盖所有 sgl_gauge_xxx 接口

 */
#include "sgl_demo.h"
#if SGD_ENABLE_GAUGE

/* 第二个仪表盘（供动画回调使用）*/
static sgl_obj_t *g_yibiao2 = NULL;

/* 动画路径回调：更新仪表盘指针值 */
static void gauge_anim_path(sgl_anim_t *anim, int32_t value)
{
    (void)anim;
    if (g_yibiao2) {
        sgl_gauge_set_value(g_yibiao2, (int16_t)value);
    }
}

void sgd_gauge_demo(sgl_obj_t *parent)
{
    /* ================================================================
     * 1) 完整功能仪表盘 — 演示所有 sgl_gauge_xxx 接口
     * ================================================================ */
    sgl_obj_t *yibiao1 = sgl_gauge_create(parent);
    sgl_obj_set_pos(yibiao1, (SGL_SCREEN_WIDTH - 160) / 2, 20);
    sgl_obj_set_size(yibiao1, 160, 160);

    /* 仪表盘盘面底色 */
    sgl_gauge_set_bg_color(yibiao1, SGL_COLOR_DARK_GRAY);

    /* 外圈弧形颜色 */
    sgl_gauge_set_arc_color(yibiao1, SGL_COLOR_CYAN);

    /* 指针颜色 */
    sgl_gauge_set_pointer_color(yibiao1, SGL_COLOR_RED);

    /* 刻度线颜色 */
    sgl_gauge_set_scale_color(yibiao1, SGL_COLOR_WHITE);

    /* 刻度数字颜色 */
    sgl_gauge_set_text_color(yibiao1, SGL_COLOR_WHITE);

    /* 中心轴盖颜色 */
    sgl_gauge_set_hub_color(yibiao1, SGL_COLOR_GRAY);

    /* 外圈弧宽 */
    sgl_gauge_set_arc_width(yibiao1, 2);

    /* 指针宽度 */
    sgl_gauge_set_pointer_width(yibiao1, 3);

    /* 刻度线宽度 */
    sgl_gauge_set_scale_width(yibiao1, 1);

    /* 刻度线长度 */
    sgl_gauge_set_scale_length(yibiao1, 12);

    /* 主刻度变密：每格代表 5 个数值单位 */
    sgl_gauge_set_scale_step_value(yibiao1, 5);

    /* 240 度扫角下，每 5 数值对应 12 度，刻度数量翻倍 */
    sgl_gauge_set_scale_angle(yibiao1, 12);

    /* 超过该数值后，刻度颜色切换为红色 */
    sgl_gauge_set_scale_warning_value(yibiao1, 80);

    /* 表盘扫角范围：从 150 度到 390 度 */
    sgl_gauge_set_angle_range(yibiao1, 150, 390);

    /* 当前值 */
    sgl_gauge_set_value(yibiao1, 65);

    /* 读取当前值，演示 get 接口 */
    int16_t val = sgl_gauge_get_value(yibiao1);
    (void)val;

    /* 刻度数字字体 */
    sgl_gauge_set_font(yibiao1, &consolas14);

    /* 中心轴盖半径 */
    sgl_gauge_set_hub_radiue(yibiao1, 8);

    /* 刻度起始值，配合 step_value 形成 0/5/10/.../100 */
    sgl_gauge_set_scale_start_value(yibiao1, 0);

    /* 文字不要每格都显示：隔 2 个主刻度显示一次，即显示 0/10/20...100 */
    sgl_gauge_set_text_interval(yibiao1, 5);

    /* 整体透明度 */
    sgl_gauge_set_alpha(yibiao1, 220);

    /* ================================================================
     * 2) 动画仪表盘 — 值 0→100 循环，接入动画系统
     * ================================================================ */
    g_yibiao2 = sgl_gauge_create(parent);
    sgl_obj_set_pos(g_yibiao2, (SGL_SCREEN_WIDTH - 140) / 2, 200);
    sgl_obj_set_size(g_yibiao2, 140, 160);
    sgl_gauge_set_bg_color(g_yibiao2, SGL_COLOR_DARK_GRAY);
    sgl_gauge_set_arc_color(g_yibiao2, SGL_COLOR_GOLD);
    sgl_gauge_set_pointer_color(g_yibiao2, SGL_COLOR_ORANGE);
    sgl_gauge_set_scale_color(g_yibiao2, SGL_COLOR_WHITE);
    sgl_gauge_set_text_color(g_yibiao2, SGL_COLOR_WHITE);
    sgl_gauge_set_hub_color(g_yibiao2, SGL_COLOR_GRAY);
    sgl_gauge_set_arc_width(g_yibiao2, 8);
    sgl_gauge_set_pointer_width(g_yibiao2, 1);
    sgl_gauge_set_scale_width(g_yibiao2, 2);
    sgl_gauge_set_scale_length(g_yibiao2, 12);
    sgl_gauge_set_scale_angle(g_yibiao2, 12);
    sgl_gauge_set_scale_warning_value(g_yibiao2, 80);
    sgl_gauge_set_angle_range(g_yibiao2, 150, 390);
    sgl_gauge_set_value(g_yibiao2, 0);
    sgl_gauge_set_font(g_yibiao2, &consolas14);
    sgl_gauge_set_hub_radiue(g_yibiao2, 8);
    sgl_gauge_set_scale_start_value(g_yibiao2, 0);
    sgl_gauge_set_scale_step_value(g_yibiao2, 5);
    sgl_gauge_set_text_interval(g_yibiao2, 2);
    sgl_gauge_set_alpha(g_yibiao2, 220);

    /* 创建动画：值 0→100 循环 */
    {
        sgl_anim_t *a = sgl_anim_create();
        sgl_anim_set_data(a, NULL);
        sgl_anim_set_act_duration(a, 3000);
        sgl_anim_set_start_value(a, 0);
        sgl_anim_set_end_value(a, 100);
        sgl_anim_set_path(a, gauge_anim_path, SGL_ANIM_PATH_LINEAR);
        sgl_anim_start(a, SGL_ANIM_REPEAT_LOOP);
    }
}
#endif
