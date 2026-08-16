/**
 * @file    sgl_box_demo.c Box和矩形一样可以当任意控件的爸爸
 * @brief   SGL Box 容器控件 Demo — 覆盖所有 sgl_box_xxx 接口
 *          Box 支持同时水平和垂直双向滚动（SGL_BOX_SCROLL_BOTH）
 *          内容超出可视区时自动出现滚动条，手指拖动即可滑动
 
 */
#include "sgl_demo.h"
#if SGD_ENABLE_BOX

extern const sgl_pixmap_t pic1_pixmap;

void sgd_box_demo(sgl_obj_t *parent)
{
    sgl_obj_t *rongqi = sgl_box_create(parent);
    sgl_obj_set_pos(rongqi, 10, 10);
    sgl_obj_set_size(rongqi, 280, 200);

    /* 设置背景颜色 */
    sgl_box_set_bg_color(rongqi, SGL_COLOR_DARK_GRAY);

    /* 设置圆角 */
    sgl_box_set_radius(rongqi, 4);

    /* 设置边框颜色 */
    sgl_box_set_border_color(rongqi, SGL_COLOR_CYAN);

    /* 设置边框宽度 */
    sgl_box_set_border_width(rongqi, 1);

    /* 设置弹性滚动（上下左右弹性边界像素）*/
    sgl_box_set_elastic_scroll(rongqi, 80, 80, 80, 80);

    /* 设置滚动条颜色 */
    sgl_box_set_scrollbar_color(rongqi, SGL_COLOR_CYAN);

    /* 显示垂直和水平滚动条 */
    sgl_box_set_show_scrollbar(rongqi, 1, 1);

    /* 设置透明度 */
    sgl_box_set_alpha(rongqi, 220);

    /* 设置背景图片 */
    sgl_box_set_pixmap(rongqi, &pic1_pixmap);

    /* ================================================================
     * Box 内部控件：左右各一列，超出容器范围时可双向滚动
     * ================================================================ */

    /* 左侧按钮列（垂直溢出）*/
    for (int i = 0; i < 8; i++) {
        char *text = sgl_malloc(16);
        if (text) snprintf(text, 16, "L-Btn %d", i + 1);
        sgl_obj_t *btn = sgl_button_create(rongqi);
        sgl_obj_set_pos(btn, 10, 10 + i * 36);
        sgl_obj_set_size(btn, 100, 30);
        sgl_button_set_text(btn, text ? text : "Btn");
        sgl_button_set_font(btn, &consolas14);
        sgl_button_set_color(btn, SGL_COLOR_NAVY);
        sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
        sgl_button_set_radius(btn, 4);
    }

    /* 右侧按钮列（水平溢出 + 垂直溢出）*/
    for (int i = 0; i < 8; i++) {
        char *text = sgl_malloc(16);
        if (text) snprintf(text, 16, "R-Btn %d", i + 1);
        sgl_obj_t *btn = sgl_button_create(rongqi);
        sgl_obj_set_pos(btn, 150, 10 + i * 36);
        sgl_obj_set_size(btn, 100, 30);
        sgl_button_set_text(btn, text ? text : "Btn");
        sgl_button_set_font(btn, &consolas14);
        sgl_button_set_color(btn, SGL_COLOR_DARK_GREEN);
        sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
        sgl_button_set_radius(btn, 4);
    }

    /* 底部额外标签（进一步增加垂直溢出）*/
    sgl_obj_t *lab = sgl_label_create(rongqi);
    sgl_obj_set_pos(lab, 10, 310);
    sgl_obj_set_size(lab, 240, 20);
    sgl_label_set_text(lab, "Scroll down to see more...");
    sgl_label_set_font(lab, &consolas14);
    sgl_label_set_text_color(lab, SGL_COLOR_GRAY);
    sgl_label_set_text_align(lab, SGL_ALIGN_LEFT_MID);
}
#endif
