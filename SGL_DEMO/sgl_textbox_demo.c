/**
 * @file    sgl_textbox_demo.c
 * @brief   SGL Textbox 文本框控件 Demo — 覆盖所有 sgl_textbox_xxx 接口
 *          Textbox 与 Textline 的区别：
 *          - Textbox：支持长文本滚动（内部带滚动条），适合显示大量文本
 *          - Textline：纯文本显示，不支持滚动，适合显示少量文本
 */
#include "sgl_demo.h"
#if SGD_ENABLE_TEXTBOX
extern const sgl_pixmap_t pic1_pixmap;

void sgd_textbox_demo(sgl_obj_t *parent) {
    int16_t y = SGD_MG;
    sgl_obj_t *tb;

    /* 创建文本框对象 */
    tb = sgl_textbox_create(parent);
    sgl_obj_set_pos(tb, SGD_MG, y);
    sgl_obj_set_size(tb, SGD_W, SGD_H);

    /* 设置文本内容（\n 换行，超出高度可滚动） */
    sgl_textbox_set_text(tb, "[1] Textbox Demo\nMulti-line text\n"
                            "with scroll support.\n"
                            "You can scroll to see\n"
                            "more content here.\n"
                            "Line 6\nLine 7\nLine 8");
    /* 设置文字颜色 */
    sgl_textbox_set_text_color(tb, SGL_COLOR_WHITE);
    /* 设置字体 */
    sgl_textbox_set_text_font(tb, &consolas14);
    /* 设置背景颜色 */
    sgl_textbox_set_bg_color(tb, SGL_COLOR_DARK_GRAY);
    /* 设置圆角半径 */
    sgl_textbox_set_radius(tb, 4);
    /* 设置边框颜色 */
    sgl_textbox_set_border_color(tb, SGL_COLOR_CYAN);
    /* 设置边框宽度 */
    sgl_textbox_set_border_width(tb, 1);
    /* 设置行间距 */
    sgl_textbox_set_line_margin(tb, 2);
    y += SGD_H  + SGD_GAP;

    /* 第二个文本框 */
    tb = sgl_textbox_create(parent);
    sgl_obj_set_pos(tb, SGD_MG, y);
    sgl_obj_set_size(tb, SGD_W, SGD_H * 3);
    sgl_textbox_set_text(tb, "[2] With pixmap + border\n"
                            "Short text demo.");
    sgl_textbox_set_text_color(tb, SGL_COLOR_WHITE);
    sgl_textbox_set_text_font(tb, &consolas14);
    sgl_textbox_set_bg_color(tb, SGL_COLOR_NAVY);
    /* 设置背景图片 */
    sgl_textbox_set_pixmap(tb, &pic1_pixmap);
    sgl_textbox_set_radius(tb, 4);
    sgl_textbox_set_border_color(tb, SGL_COLOR_WHITE);
    sgl_textbox_set_border_width(tb, 1);
    sgl_textbox_set_line_margin(tb, 3);
    y += SGD_H * 3 + SGD_GAP;
}
#endif