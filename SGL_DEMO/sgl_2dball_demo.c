/**
 * @file    sgl_2dball_demo.c
 * @brief   SGL 2DBall 二维球体控件 Demo — 覆盖所有 sgl_2dball_xxx 接口
 */
#include "sgl_demo.h"
#if SGD_ENABLE_2DBALL
void sgd_2dball_demo(sgl_obj_t *parent)
{
    /* 创建第一个二维球体 */
    sgl_obj_t *qiu1 = sgl_2dball_create(parent);
    sgl_obj_set_pos(qiu1, 50, 60);
    sgl_obj_set_size(qiu1, 80, 80);

    /* 设置球体颜色（青色）*/
    sgl_2dball_set_color(qiu1, SGL_COLOR_CYAN);

    /* 设置背景颜色 */
    sgl_2dball_set_bg_color(qiu1, SGL_COLOR_DARK_GRAY);

    /* 设置透明度 */
    sgl_2dball_set_alpha(qiu1, 200);

    /* 设置球体半径 */
    sgl_2dball_set_radius(qiu1, 35);

    /* 创建第二个球体（金色）*/
    sgl_obj_t *qiu2 = sgl_2dball_create(parent);
    sgl_obj_set_pos(qiu2, 190, 60);
    sgl_obj_set_size(qiu2, 80, 80);
    sgl_2dball_set_color(qiu2, SGL_COLOR_GOLD);
    sgl_2dball_set_bg_color(qiu2, SGL_COLOR_DARK_GRAY);
    sgl_2dball_set_alpha(qiu2, 180);
    sgl_2dball_set_radius(qiu2, 30);
}
#endif
