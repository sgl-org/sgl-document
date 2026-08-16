/**
 * @file    sgl_line_demo.c
 * @brief   SGL Line 线段控件 Demo — 覆盖所有 sgl_line_xxx 接口
 *          深色主题，实线与虚线对比，下方射线动画
 */
#include "sgl_demo.h"
#include <math.h>
#if SGD_ENABLE_LINE

/* 射线参数 */
#define RAY_NUM      18
#define RAY_LEN     80
#define ANIM_MAX  1000
#define SLOT_W     125

/* 射线颜色数组 */
static const sgl_color_t g_ray_clr[RAY_NUM] = {
    SGL_COLOR_RED,      SGL_COLOR_GREEN,  SGL_COLOR_BLUE,   SGL_COLOR_CYAN,
    SGL_COLOR_YELLOW,   SGL_COLOR_MAGENTA,SGL_COLOR_ORANGE, SGL_COLOR_LIME,
    SGL_COLOR_PINK, SGL_COLOR_TEAL,   SGL_COLOR_BROWN,
   SGL_COLOR_GRAY
};

static sgl_obj_t *g_rays[RAY_NUM] = {NULL};

/* 射线动画回调：每条射线依次淡入再淡出 */
static void ray_anim_path(sgl_anim_t *anim, int32_t value)
{
    (void)anim;
    for (int i = 0; i < RAY_NUM; i++) {
        int slot_start = i * (ANIM_MAX / RAY_NUM);
        int t = value - slot_start;
        uint8_t alpha = 0;
        if (t >= 0 && t <= SLOT_W) {
            if (t <= SLOT_W / 2) {
                alpha = (uint8_t)(t * 255 / (SLOT_W / 2));          /* 淡入 */
            } else {
                alpha = (uint8_t)((SLOT_W - t) * 255 / (SLOT_W / 2)); /* 淡出 */
            }
        }
        sgl_line_set_alpha(g_rays[i], alpha);
    }
}

void sgd_line_demo(sgl_obj_t *parent)
{
    /* ================================================================
     * 1) 实线 — 完整功能，演示所有 sgl_line_xxx 基础接口
     * ================================================================ */
    sgl_obj_t *xian1 = sgl_line_create(parent);

    /* 设置线段起点和终点坐标 */
    sgl_line_set_pos(xian1, 20, 50, 300, 50);

    /* 设置线段颜色（青色）*/
    sgl_line_set_color(xian1, SGL_COLOR_CYAN);

    /* 设置透明度 */
    sgl_line_set_alpha(xian1, 220);

    /* 设置线段宽度 */
    sgl_line_set_width(xian1, 4);

    /* ================================================================
     * 2) 虚线 — 演示 set_dashed / set_dash_pattern
     * ================================================================ */
    sgl_obj_t *xian2 = sgl_line_create(parent);
    sgl_line_set_pos(xian2, 20, 110, 300, 110);
    sgl_line_set_color(xian2, SGL_COLOR_GOLD);
    sgl_line_set_alpha(xian2, 200);
    sgl_line_set_width(xian2, 3);

    /* 设置为虚线模式 */
    sgl_line_set_dashed(xian2, 1);

    /* 设置虚线样式：实线段 8px，间隔 4px */
    sgl_line_set_dash_pattern(xian2, 8, 4);

    /* ================================================================
     * 3) 射线动画 — 多条彩色线段依次射出，循环播放
     * ================================================================ */

    /* 射线中心点 */
    int cx = 160, cy = 320;

    /* 创建 8 条射线，从中心向外辐射 */
    for (int i = 0; i < RAY_NUM; i++) {
        float rad = i * 360.0f / RAY_NUM;
        int ex = cx + (int)(RAY_LEN * cosf(rad * 3.14159265f / 180.0f));
        int ey = cy + (int)(RAY_LEN * sinf(rad * 3.14159265f / 180.0f));

        g_rays[i] = sgl_line_create(parent);
        sgl_line_set_pos(g_rays[i], cx, cy, ex, ey);
        sgl_line_set_color(g_rays[i], g_ray_clr[i]);
        sgl_line_set_alpha(g_rays[i], 0);
        sgl_line_set_width(g_rays[i], 2);
    }

    /* 创建动画：value 0→1000 循环，每次切换一条射线 */
    {
        sgl_anim_t *a = sgl_anim_create();
        sgl_anim_set_data(a, NULL);
        sgl_anim_set_act_duration(a, 3000);
        sgl_anim_set_start_value(a, 0);
        sgl_anim_set_end_value(a, ANIM_MAX);
        sgl_anim_set_path(a, ray_anim_path, SGL_ANIM_PATH_LINEAR);
        sgl_anim_start(a, SGL_ANIM_REPEAT_LOOP);
    }
}
#endif
