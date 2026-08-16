/**
 * @file    sgl_icon_demo.c
 * @brief   SGL Icon 图标控件 Demo — 覆盖所有 sgl_icon_xxx 接口
 */
#include "sgl_demo.h"
#if SGD_ENABLE_ICON
void sgd_icon_demo(sgl_obj_t *parent)
{
    sgl_obj_t *tubiao1 = sgl_icon_create(parent);
    sgl_obj_set_pos(tubiao1, 60, 60);
    sgl_obj_set_size(tubiao1, 60, 60);

    /* 设置图标颜色（青色）*/
    sgl_icon_set_color(tubiao1, SGL_COLOR_CYAN);
		//设置icon
		//sgl_icon_set_icon(sgl_obj_t *obj, const sgl_icon_pixmap_t *icon)
		
    /* 设置透明度 */
    sgl_icon_set_alpha(tubiao1, 220);

    /* 设置对齐 */
    sgl_icon_set_align(tubiao1, SGL_ALIGN_CENTER);

    /* 第二个图标（金色）*/
    sgl_obj_t *tubiao2 = sgl_icon_create(parent);
    sgl_obj_set_pos(tubiao2, 180, 60);
    sgl_obj_set_size(tubiao2, 60, 60);
    sgl_icon_set_color(tubiao2, SGL_COLOR_GOLD);
    sgl_icon_set_alpha(tubiao2, 200);
    sgl_icon_set_align(tubiao2, SGL_ALIGN_CENTER);
}
#endif
