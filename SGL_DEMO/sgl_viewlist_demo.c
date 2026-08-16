/**
 * @file    sgl_viewlist_demo.c
 * @brief   SGL ViewList 视图列表控件 Demo — 覆盖所有接口
 */
#include "sgl_demo.h"
#if SGD_ENABLE_VIEWLIST
void sgd_viewlist_demo(sgl_obj_t *parent)
{
    sgl_obj_t *view = sgl_viewlist_create(parent);
    sgl_obj_set_pos(view, 20, 20);
    sgl_obj_set_size(view, 280, 200);

    /* 设置圆角 */
    sgl_viewlist_set_radius(view, 4);

    /* 设置背景颜色 */
    sgl_viewlist_set_bg_color(view, SGL_COLOR_DARK_GRAY);

    /* 设置透明度 */
    sgl_viewlist_set_alpha(view, 220);

    /* 设置边框宽度 */
    sgl_viewlist_set_border_width(view, 1);

    /* 设置边框颜色 */
    sgl_viewlist_set_border_color(view, SGL_COLOR_CYAN);

    /* 设置列表项高度 */
    sgl_viewlist_set_item_height(view, 40);

    /* 设置列表项边距 */
    sgl_viewlist_set_item_margin(view, 4, 4);

    /* 追加子项（使用按钮）*/
    for (int i = 0; i < 6; i++) {
        char *text = sgl_malloc(16);
        if (text) {
            snprintf(text, 16, "Item %d", i + 1);
        }
        sgl_obj_t *btn = sgl_button_create(view);
        sgl_button_set_text(btn, text ? text : "Item");
        sgl_button_set_font(btn, &consolas14);
        sgl_button_set_color(btn, SGL_COLOR_NAVY);
        sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
        sgl_button_set_radius(btn, 4);
        sgl_viewlist_append_obj(view, btn);
    }
}
#endif
