/**
 * @file    sgl_ring_demo.c
 * @brief   SGL Ring 环形控件 Demo — 覆盖所有 sgl_ring_xxx 接口

 */
#include "sgl_demo.h"
#if SGD_ENABLE_RING
void sgd_ring_demo(sgl_obj_t *parent)
{
    /* ================================================================
     * 奥运五环 — 上半部分
     * 颜色：蓝、黄、黑、绿、红（绘制顺序实现交错）
     * ================================================================ */

    /* 外半径和内半径同时放大，让五环更饱满，也更容易形成明显交叠 */
#define R_OUT  34
#define R_IN   29
#define R_SZ   (R_OUT * 2)


    const int ring_step_x = R_SZ - 18;
    const int ring_step_y = R_OUT - 4;
    const int top_mid_x = SGL_SCREEN_WIDTH / 2;
    const int top_left_x = top_mid_x - ring_step_x;
    const int top_right_x = top_mid_x + ring_step_x;
    const int bot_left_x = top_mid_x - ring_step_x / 2;
    const int bot_right_x = top_mid_x + ring_step_x / 2;

    /* 第一排：蓝（左） 黑（中） 红（右）*/
    int top_y = 80;
    /* 第二排：黄（左） 绿（右）*/
    int bot_y = top_y + ring_step_y;

    /* 1) 黄色环（左下，先画放底层）*/
    sgl_obj_t *huan = sgl_ring_create(parent);

    /* 设置控件位置 */
    sgl_obj_set_pos(huan, bot_left_x - R_OUT, bot_y - R_OUT);
    /* 设置控件大小 */
    sgl_obj_set_size(huan, R_SZ, R_SZ);

    /* 设置环形颜色（黄色）*/
    sgl_ring_set_color(huan, SGL_COLOR_YELLOW);

    /* 设置透明度 */
    sgl_ring_set_alpha(huan, 230);

    /* 设置环形内外半径 */
    sgl_ring_set_radius(huan, R_IN, R_OUT);

    /* 2) 绿色环（右下）*/
    huan = sgl_ring_create(parent);
    sgl_obj_set_pos(huan, bot_right_x - R_OUT, bot_y - R_OUT);
    sgl_obj_set_size(huan, R_SZ, R_SZ);
    sgl_ring_set_color(huan, SGL_COLOR_GREEN);
    sgl_ring_set_alpha(huan, 230);
    sgl_ring_set_radius(huan, R_IN, R_OUT);

    /* 3) 蓝色环（左上）*/
    huan = sgl_ring_create(parent);
    sgl_obj_set_pos(huan, top_left_x - R_OUT, top_y - R_OUT);
    sgl_obj_set_size(huan, R_SZ, R_SZ);
    sgl_ring_set_color(huan, SGL_COLOR_BLUE);
    sgl_ring_set_alpha(huan, 230);
    sgl_ring_set_radius(huan, R_IN, R_OUT);

    /* 4) 红色环（右上）*/
    huan = sgl_ring_create(parent);
    sgl_obj_set_pos(huan, top_right_x - R_OUT, top_y - R_OUT);
    sgl_obj_set_size(huan, R_SZ, R_SZ);
    sgl_ring_set_color(huan, SGL_COLOR_RED);
    sgl_ring_set_alpha(huan, 230);
    sgl_ring_set_radius(huan, R_IN, R_OUT);

    /* 5) 黑色环（中上，最后画放最上层）*/
    huan = sgl_ring_create(parent);
    sgl_obj_set_pos(huan, top_mid_x - R_OUT, top_y - R_OUT);
    sgl_obj_set_size(huan, R_SZ, R_SZ);
    sgl_ring_set_color(huan, SGL_COLOR_BLACK);
    sgl_ring_set_alpha(huan, 230);
    sgl_ring_set_radius(huan, R_IN, R_OUT);
}
#endif
