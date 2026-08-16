/**
 * @file    sgl_textlist_demo.c
 * @brief   SGL TextList 文本列表控件 Demo — 覆盖所有接口
 */
#include "sgl_demo.h"
#if SGD_ENABLE_TEXTLIST
void sgd_textlist_demo(sgl_obj_t *parent)
{
    sgl_obj_t *wenben = sgl_textlist_create(parent);
    sgl_obj_set_pos(wenben, 20, 20);
    sgl_obj_set_size(wenben, 280, 200);

    /* 设置圆角 */
    sgl_textlist_set_radius(wenben, 4);

    /* 设置文字颜色 */
    sgl_textlist_set_text_color(wenben, SGL_COLOR_WHITE);

    /* 设置选中项颜色 */
    sgl_textlist_set_selected_color(wenben, SGL_COLOR_NAVY);

    /* 设置边框颜色 */
    sgl_textlist_set_border_color(wenben, SGL_COLOR_CYAN);

    /* 设置背景颜色 */
    sgl_textlist_set_bg_color(wenben, SGL_COLOR_DARK_GRAY);

    /* 设置字体 */
    sgl_textlist_set_text_font(wenben, &consolas14);

    /* 设置透明度 */
    sgl_textlist_set_alpha(wenben, 220);

    /* 设置边框宽度 */
    sgl_textlist_set_border_width(wenben, 1);

    /* 添加列表项 */
    sgl_textlist_add_item(wenben, "Item 1");
    sgl_textlist_add_item(wenben, "Item 2");
    sgl_textlist_add_item(wenben, "Item 3");
    sgl_textlist_add_item(wenben, "Item 4");
    sgl_textlist_add_item(wenben, "Item 5");

    /* 获取选中文本和索引 */
    sgl_textlist_get_selected_text(wenben);
    sgl_textlist_get_selected_index(wenben);

    /* 删除项 */
    sgl_textlist_delete_item_by_index(wenben, 4);
    sgl_textlist_delete_item_by_text(wenben, "Item 3");
}
#endif
