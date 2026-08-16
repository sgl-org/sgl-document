/**
 * @file    sgl_textline_demo.c
 * @brief   SGL Textline 多行文本控件 Demo — 覆盖所有 sgl_textline_xxx 接口
 *          支持多行文本显示，可设置字体/颜色/背景/边距等
 */
#include "sgl_demo.h"
#if SGD_ENABLE_TEXTLINE
void sgd_textline_demo(sgl_obj_t *parent) {
    int16_t y = SGD_MG;
    sgl_obj_t *tl;

    /* 创建多行文本对象 */
    tl = sgl_textline_create(parent);
    sgl_obj_set_pos(tl, SGD_MG, y);  sgl_obj_set_size(tl, SGD_W, SGD_H * 2);

    /* 设置文本内容，支持 \n 换行 */
    sgl_textline_set_text(tl, "[1] Textline\nMulti-line\ndemo here");

    /* 设置字体 */
    sgl_textline_set_text_font(tl, &consolas14);

    /* 设置文字颜色 */
    sgl_textline_set_text_color(tl, SGL_COLOR_WHITE);

    /* 设置背景颜色 */
    sgl_textline_set_bg_color(tl, SGL_COLOR_DARK_GRAY);

    /* 设置圆角半径 */
    sgl_textline_set_radius(tl, 4);

    /* 设置透明度 */
    sgl_textline_set_alpha(tl, 200);

    /* 设置文字与边缘的间距 */
    sgl_textline_set_edge_margin(tl, 4);

    /* 设置行间距 */
    sgl_textline_set_line_margin(tl, 2);
    y += SGD_H * 2 + SGD_GAP;

    /* 第二个文本行 — 透明背景  */
    tl = sgl_textline_create(parent);
    sgl_obj_set_pos(tl, SGD_MG, y);  sgl_obj_set_size(tl, SGD_W, SGD_H * 2);
    sgl_textline_set_text(tl, "[2] Cyan txt\nNavy bg");
    sgl_textline_set_text_font(tl, &consolas14);
    sgl_textline_set_text_color(tl, SGL_COLOR_RED_ORANGE);
    sgl_textline_set_bg_color(tl, SGL_COLOR_NAVY);
    sgl_textline_set_radius(tl, 4);
    /* 设置背景透明 */
    sgl_textline_set_bg_transparent(tl);
    y += SGD_H * 2 + SGD_GAP;
}
#endif