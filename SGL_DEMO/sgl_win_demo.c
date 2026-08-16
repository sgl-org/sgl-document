/**
 * @file    sgl_win_demo.c
 * @brief   SGL Win 窗口控件 Demo — 覆盖所有 sgl_win_xxx 接口
 *          第一个窗口展示完整功能，第二个窗口通过按钮创建，
 *          点击右上角关闭按钮后销毁，再由按钮重新打开
 */
#include "sgl_demo.h"
#if SGD_ENABLE_WIN

extern const sgl_pixmap_t pic1_pixmap;

static sgl_obj_t *g_win2 = NULL;
static sgl_obj_t *g_win_parent = NULL;

static void btn_inside_win2(sgl_event_t *e)
{
    if (e->type == SGL_EVENT_CLICKED) {
        sgl_obj_t *label = (sgl_obj_t *)sgl_event_get_data(e);
        if (label) {
            sgl_label_set_text(label, "Button clicked");
        }
    }
}

static void create_demo_win2(void)
{
    if (g_win_parent == NULL || g_win2 != NULL) {
        return;
    }

    g_win2 = sgl_win_create(g_win_parent);
    sgl_obj_set_pos(g_win2, 80, 130);
    sgl_obj_set_size(g_win2, 200, 140);

    /* 设置窗口颜色 */
    sgl_win_set_color(g_win2, SGL_COLOR_DARK_GRAY);

    /* 设置圆角 */
    sgl_win_set_radius(g_win2, 6);

    /* 设置透明度 */
    sgl_win_set_alpha(g_win2, 220);

    /* 设置边框宽度 */
    sgl_win_set_border_width(g_win2, 1);

    /* 设置边框颜色 */
    sgl_win_set_border_color(g_win2, SGL_COLOR_GOLD);

    /* 设置标题文字 */
    sgl_win_set_title_text(g_win2, "Control Win");

    /* 设置标题文字颜色 */
    sgl_win_set_title_text_color(g_win2, SGL_COLOR_WHITE);

    /* 设置标题字体 */
    sgl_win_set_title_font(g_win2, &consolas14);

    /* 设置标题高度 */
    sgl_win_set_title_height(g_win2, 28);

    /* 设置标题文字对齐 */
    sgl_win_set_title_text_align(g_win2, SGL_ALIGN_LEFT_MID);

    /* 设置标题背景颜色 */
    sgl_win_set_title_bg_color(g_win2, SGL_COLOR_SADDLE_BROWN);

    /* 设置关闭按钮颜色 */
    sgl_win_set_close_btn_color(g_win2, SGL_COLOR_RED);

    /* 窗口正文标签：演示内容区不是标题的一部分，而是窗口子控件 */
    sgl_obj_t *lab = sgl_label_create(g_win2);
    sgl_obj_set_pos(lab, 12, 42);
    sgl_obj_set_size(lab, 160, 22);
    sgl_label_set_text(lab, "Ready");
    sgl_label_set_font(lab, &consolas14);
    sgl_label_set_text_color(lab, SGL_COLOR_WHITE);
    sgl_label_set_text_align(lab, SGL_ALIGN_LEFT_MID);

    /* 窗口内按钮：点击后更新上方标签，形成更真实的内容区交互 */
    sgl_obj_t *btn = sgl_button_create(g_win2);
    sgl_obj_set_pos(btn, 12, 74);
    sgl_obj_set_size(btn, 110, 28);
    sgl_button_set_text(btn, "Click Me");
    sgl_button_set_font(btn, &consolas14);
    sgl_button_set_color(btn, SGL_COLOR_SADDLE_BROWN);
    sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
    sgl_button_set_radius(btn, 4);
    sgl_obj_set_event_cb(btn, btn_inside_win2, lab);
}

/* 打开窗口按钮回调：如果窗口已被右上角关闭销毁，则重新创建 */
static void btn_open_win(sgl_event_t *e)
{
    (void)e;

    if (g_win2 && !sgl_obj_is_destroyed(g_win2)) {
        sgl_obj_set_visible(g_win2);
        return;
    }

    g_win2 = NULL;
    create_demo_win2();
}

void sgd_win_demo(sgl_obj_t *parent)
{
    g_win_parent = parent;

    /* ================================================================
     * 1) 完整功能窗口
     * ================================================================ */
    sgl_obj_t *chuangkou = sgl_win_create(parent);
    sgl_obj_set_pos(chuangkou, 30, 30);
    sgl_obj_set_size(chuangkou, 260, 200);

    /* 设置窗口颜色 */
    sgl_win_set_color(chuangkou, SGL_COLOR_DARK_GRAY);

    /* 设置圆角 */
    sgl_win_set_radius(chuangkou, 6);

    /* 设置透明度 */
    sgl_win_set_alpha(chuangkou, 220);

    /* 设置边框宽度 */
    sgl_win_set_border_width(chuangkou, 1);

    /* 设置边框颜色 */
    sgl_win_set_border_color(chuangkou, SGL_COLOR_CYAN);

    /* 设置背景图片 */
    sgl_win_set_pixmap(chuangkou, &pic1_pixmap);

    /* 设置标题文字 */
    sgl_win_set_title_text(chuangkou, "Window Demo");

    /* 设置标题文字颜色 */
    sgl_win_set_title_text_color(chuangkou, SGL_COLOR_WHITE);

    /* 设置标题字体 */
    sgl_win_set_title_font(chuangkou, &consolas14);

    /* 设置标题高度 */
    sgl_win_set_title_height(chuangkou, 30);

    /* 设置标题文字对齐 */
    sgl_win_set_title_text_align(chuangkou, SGL_ALIGN_LEFT_MID);

    /* 设置标题背景颜色 */
    sgl_win_set_title_bg_color(chuangkou, SGL_COLOR_NAVY);

    /* 设置关闭按钮颜色 */
    sgl_win_set_close_btn_color(chuangkou, SGL_COLOR_RED);

    /* 获取标题高度 */
    sgl_win_title_height(chuangkou);

    /* 窗口正文说明文字：演示内容区控件的常规写法 */
    sgl_obj_t *lab = sgl_label_create(chuangkou);
    sgl_obj_set_pos(lab, 12, 44);
    sgl_obj_set_size(lab, 220, 52);
    sgl_label_set_text(lab, "This window can host labels, buttons\nand other child widgets.");
    sgl_label_set_font(lab, &consolas14);
    sgl_label_set_text_color(lab, SGL_COLOR_WHITE);
    sgl_label_set_text_align(lab, SGL_ALIGN_LEFT_MID);

    /* ================================================================
     * 2) 第二个窗口 + 打开按钮
     *    第二个窗口默认创建出来，点击右上角关闭按钮后会销毁。
     *    下方按钮通过标准创建流程把它重新打开
     * ================================================================ */
    create_demo_win2();

    /* 打开窗口按钮 */
    sgl_obj_t *btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, 90, 285);
    sgl_obj_set_size(btn, 140, 30);
    sgl_button_set_text(btn, "Open Win2");
    sgl_button_set_font(btn, &consolas14);
    sgl_button_set_color(btn, SGL_COLOR_NAVY);
    sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
    sgl_button_set_radius(btn, 4);
    sgl_obj_set_event_cb(btn, btn_open_win, NULL);
}

#endif
