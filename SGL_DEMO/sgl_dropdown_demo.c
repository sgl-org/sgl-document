/**
 * @file    sgl_dropdown_demo.c
 * @brief   SGL Dropdown 下拉菜单控件 Demo — 覆盖所有 sgl_dropdown_xxx 接口
 *          深色主题 + 24号字体，选中信息通过标签显示
 */
#include "sgl_demo.h"
#if SGD_ENABLE_DROPDOWN

/* 选中信息标签（全局，供回调中更新文本） */
static sgl_obj_t *g_dd_info = NULL;

/* ================================================================
 * 事件回调 — 获取当前选中项的索引和文本，更新到标签上
 * API: sgl_dropdown_get_selected_index
 *      sgl_dropdown_get_selected_text
 * ================================================================ */
static void sgd_dd_event(sgl_event_t *e)
{
    if (e->type == SGL_EVENT_CLICKED) {
        /* 获取触发事件的 dropdown 对象 */
        sgl_obj_t *obj = (sgl_obj_t *)e->obj;
        /* 读取选中项的索引 */
        int idx = sgl_dropdown_get_selected_index(obj);
        /* 读取选中项的文本 */
        char buf[32];
        if (sgl_dropdown_get_selected_text(obj, buf, sizeof(buf))) {
            /* 使用 FMT 接口动态更新标签文本（不依赖 rt_kprintf）*/
            if (g_dd_info) {
                sgl_label_set_text_fmt_dynamic(g_dd_info, "Selected: [%d] %s", idx, buf);
            }
        }
    }
}

void sgd_dropdown_demo(sgl_obj_t *parent)
{
    int16_t y = SGD_MG;
    sgl_obj_t *dd_disable, *dd;

    /* ================================================================
     *  信息标签 — 显示当前选中的索引和文本（放在最顶部）
     *  使用 FMT 接口动态更新
     * ================================================================ */

    g_dd_info = sgl_label_create(parent);
    sgl_obj_set_pos(g_dd_info, SGD_MG, y);
    sgl_obj_set_size(g_dd_info, SGD_W, 20);
    sgl_label_set_font(g_dd_info, &consolas14);
    sgl_label_set_text_color(g_dd_info, SGL_COLOR_CYAN);
    sgl_label_set_text_align(g_dd_info, SGL_ALIGN_LEFT_MID);
    sgl_label_set_text(g_dd_info, "Selected: none");
    y += 20 + 4;

    /* ================================================================
     * 2) 只读下拉菜单 — 演示 sgl_dropdown_set_alpha + sgl_obj_set_unclickable
     *    禁止点击 + 低透明度灰色效果
     * ================================================================ */

    dd_disable = sgl_dropdown_create(parent);
    sgl_obj_set_pos(dd_disable, SGD_MG, y);
    sgl_obj_set_size(dd_disable, SGD_W, 26);
    sgl_dropdown_set_text_font(dd_disable, &consolas14);
    sgl_dropdown_set_text_color(dd_disable, SGL_COLOR_GRAY);
    sgl_dropdown_set_bg_color(dd_disable, SGL_COLOR_DARK_GRAY);
    sgl_dropdown_set_border_color(dd_disable, SGL_COLOR_GRAY);
    sgl_dropdown_set_border_width(dd_disable, 1);
    sgl_dropdown_set_radius(dd_disable, 4);
    /* 设置透明度（低透明度，更加半透明）*/
    sgl_dropdown_set_alpha(dd_disable, 80);
    sgl_dropdown_set_selected_color(dd_disable, SGL_COLOR_DARK_GRAY);
    sgl_dropdown_set_visible_rows(dd_disable, 3);
    sgl_dropdown_set_option_static(dd_disable, "Disabled A\nDisabled B\nDisabled C");
    /* 禁止点击 — 该下拉菜单无法交互 */
    sgl_obj_set_unclickable(dd_disable);
    y += 26 + 4;

    /* ================================================================
     * 1) 完整功能下拉菜单 — 演示所有 sgl_dropdown_xxx 接口
     *    深色主题 + 24号字体，可交互（放在最底下避免遮挡）
     * ================================================================ */

    /* 创建下拉菜单对象 */
    dd = sgl_dropdown_create(parent);

    /* 设置控件位置 */
    sgl_obj_set_pos(dd, SGD_MG, y);
    /* 设置控件尺寸，高度适配 24 号字体 */
    sgl_obj_set_size(dd, SGD_W, 40);

    /* 设置选项文字的字体为 24 号 Consolas */
    sgl_dropdown_set_text_font(dd, &consolas24);

    /* 设置文字颜色 */
    sgl_dropdown_set_text_color(dd, SGL_COLOR_GRAY);

    /* 设置背景颜色 */
    sgl_dropdown_set_bg_color(dd, SGL_COLOR_DARK_GRAY);

    /* 设置边框颜色 */
    sgl_dropdown_set_border_color(dd, SGL_COLOR_GRAY);

    /* 设置边框宽度 */
    sgl_dropdown_set_border_width(dd, 1);

    /* 设置圆角半径 */
    sgl_dropdown_set_radius(dd, 4);

    /* 设置透明度 */
    //sgl_dropdown_set_alpha(dd, 180);

    /* 设置选中项的高亮颜色 */
    sgl_dropdown_set_selected_color(dd, SGL_COLOR_NAVY);

    /* 设置下拉菜单展开时最多可见行数 */
    sgl_dropdown_set_visible_rows(dd, 5);

    /* 设置选项列表（动态文本，内部拷贝字符串，后续可增删）*/
    sgl_dropdown_set_option_dynamic(dd,
        "Option A\nOption B\nOption C\nOption D\nOption E");

    /* 使用 add_option 继续追加选项 */
    sgl_dropdown_add_option(dd, "Option F");
    sgl_dropdown_add_option(dd, "Option G");
    sgl_dropdown_add_option(dd, "Option H");

    /* 按文本删除选项 */
    sgl_dropdown_delete_option_by_text(dd, "Option C");

    /* 按索引删除选项 */
    sgl_dropdown_delete_option_by_index(dd, 1);

    /* 注册事件回调（点击选中时触发，更新上方标签）*/
    sgl_obj_set_event_cb(dd, sgd_dd_event, NULL);
}
#endif
