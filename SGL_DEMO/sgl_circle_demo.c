/**
 * @file    sgl_circle_demo.c
 * @brief   SGL Circle 圆形控件 Demo — 覆盖所有 sgl_circle_xxx 接口
 *          深色主题，两个圆形垂直排列
 */
#include "sgl_demo.h"
#if SGD_ENABLE_CIRCLE

/* 图片资源（来自工程 images.c）*/
extern const sgl_pixmap_t pic1_pixmap;

void sgd_circle_demo(sgl_obj_t *parent)
{
    /* 创建第一个圆形控件对象 */
    sgl_obj_t *yuan1 = sgl_circle_create(parent);

    /* 设置控件位置（上方居中）*/
    sgl_obj_set_pos(yuan1, (SGL_SCREEN_WIDTH - 120) / 2, 60);
    /* 设置控件大小 */
    sgl_obj_set_size(yuan1, 120, 120);

    /* 设置圆形的填充颜色（青色）*/
    sgl_circle_set_color(yuan1, SGL_COLOR_CYAN);

    /* 设置圆形半径 */
    sgl_circle_set_radius(yuan1, 50);

    /* 设置圆形的透明度 */
    sgl_circle_set_alpha(yuan1, 200);

    /* 设置圆形的背景图片 */
    sgl_circle_set_pixmap(yuan1, &pic1_pixmap);

    /* 设置圆形边框的颜色 */
    sgl_circle_set_border_color(yuan1, SGL_COLOR_NAVY);

    /* 设置圆形边框的宽度 */
    sgl_circle_set_border_width(yuan1, 6);

    /* 创建第二个圆形控件对象（下方，不使用图片）*/
    sgl_obj_t *yuan2 = sgl_circle_create(parent);
    sgl_obj_set_pos(yuan2, (SGL_SCREEN_WIDTH - 120) / 2, 210);
    sgl_obj_set_size(yuan2, 120, 120);
    sgl_circle_set_color(yuan2, SGL_COLOR_GOLD);
    sgl_circle_set_radius(yuan2, 50);
    sgl_circle_set_alpha(yuan2, 220);
    sgl_circle_set_border_color(yuan2, SGL_COLOR_BROWN);
    sgl_circle_set_border_width(yuan2, 4);

    /* 设置圆心 X 偏移 */
    sgl_circle_set_x_offset(yuan2, 13);

    /* 设置圆心 Y 偏移 */
    sgl_circle_set_y_offset(yuan2, -5);
}
#endif
