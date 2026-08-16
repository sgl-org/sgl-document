/**
 * @file    sgl_numberkbd_demo.c
 * @brief   SGL NumberKbd 数字键盘控件 Demo — 覆盖所有接口
 */
#include "sgl_demo.h"
#if SGD_ENABLE_NUMBERKBD
void sgd_numberkbd_demo(sgl_obj_t *parent)
{
    sgl_obj_t *shuzi = sgl_numberkbd_create(parent);
    sgl_obj_set_pos(shuzi, 20, 40);
    sgl_obj_set_size(shuzi, 280, 200);

    /* 设置键盘颜色 */
    sgl_numberkbd_set_color(shuzi, SGL_COLOR_DARK_GRAY);

    /* 设置透明度 */
    sgl_numberkbd_set_alpha(shuzi, 230);

    /* 设置圆角 */
    sgl_numberkbd_set_radius(shuzi, 6);

    /* 设置边框宽度 */
    sgl_numberkbd_set_border_width(shuzi, 1);

    /* 设置边框颜色 */
    sgl_numberkbd_set_border_color(shuzi, SGL_COLOR_CYAN);

    /* 设置字体 */
    sgl_numberkbd_set_text_font(shuzi, &consolas14);

    /* 设置文字颜色 */
    sgl_numberkbd_set_text_color(shuzi, SGL_COLOR_WHITE);

    /* 设置按钮边距 */
    sgl_numberkbd_set_btn_margin(shuzi, 4);

    /* 设置按钮颜色 */
    sgl_numberkbd_set_btn_color(shuzi, SGL_COLOR_NAVY);

    /* 设置按钮边框宽度 */
    sgl_numberkbd_set_btn_border_width(shuzi, 1);

    /* 设置按钮边框颜色 */
    sgl_numberkbd_set_btn_border_color(shuzi, SGL_COLOR_CYAN);

    /* 设置按钮圆角 */
    sgl_numberkbd_set_btn_radius(shuzi, 4);

    /* 获取操作码 */
    sgl_numberkbd_get_opcode(shuzi);
}
#endif
