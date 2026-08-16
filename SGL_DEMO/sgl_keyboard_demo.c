/**
 * @file    sgl_keyboard_demo.c
 * @brief   SGL Keyboard 键盘控件 Demo — 覆盖所有 sgl_keyboard_xxx 接口
 *          按键输入实时显示，叉号关闭键盘后可通过按钮重新调出
 */
#include "sgl_demo.h"
#if SGD_ENABLE_KEYBOARD

extern const sgl_pixmap_t pic1_pixmap;

static char g_edit_buf[32];
static sgl_obj_t *g_disp = NULL;
static sgl_obj_t *g_jianpan = NULL;
static sgl_obj_t *g_parent = NULL;

/* 键盘事件回调：每次按键后刷新显示输入内容 */
static void keyboard_event(sgl_event_t *e)
{
    if (e->type == SGL_EVENT_PRESSED) {
        if (g_disp) {
            sgl_obj_set_dirty(g_disp);
        }
    }
}

/* 创建并配置键盘 */
static void create_keyboard(void)
{
    if (g_parent == NULL) return;

    g_jianpan = sgl_keyboard_create(g_parent);

    /* 设置位置和大小 */
    sgl_obj_set_pos(g_jianpan, 10, 60);
    sgl_obj_set_size(g_jianpan, 300, 200);

    /* 设置键盘主体颜色 */
    sgl_keyboard_set_color(g_jianpan, SGL_COLOR_DARK_GRAY);

    /* 设置整体透明度 */
    sgl_keyboard_set_alpha(g_jianpan, 230);

    /* 设置主体透明度 */
    sgl_keyboard_set_main_alpha(g_jianpan, 220);

    /* 设置圆角 */
    sgl_keyboard_set_radius(g_jianpan, 4);

    /* 设置键盘背景图片 */
    sgl_keyboard_set_pixmap(g_jianpan, NULL);

    /* 设置边框颜色 */
    sgl_keyboard_set_border_color(g_jianpan, SGL_COLOR_CYAN);

    /* 设置边框宽度 */
    sgl_keyboard_set_border_width(g_jianpan, 1);

    /* 设置边框透明度 */
    sgl_keyboard_set_border_alpha(g_jianpan, 200);

    /* 设置按键文字颜色 */
    sgl_keyboard_set_text_color(g_jianpan, SGL_COLOR_WHITE);

    /* 设置按键文字字体 */
    sgl_keyboard_set_text_font(g_jianpan, &consolas14);

    /* 设置按钮圆角 */
    sgl_keyboard_set_btn_radius(g_jianpan, 4);

    /* 设置按钮透明度 */
    sgl_keyboard_set_btn_alpha(g_jianpan, 230);

    /* 设置按钮主体透明度 */
    sgl_keyboard_set_btn_main_alpha(g_jianpan, 220);

    /* 设置按钮颜色 */
    sgl_keyboard_set_btn_color(g_jianpan, SGL_COLOR_NAVY);

    /* 设置按钮背景图片 */
    sgl_keyboard_set_btn_pixmap(g_jianpan, NULL);

    /* 设置按钮边框颜色 */
    sgl_keyboard_set_btn_border_color(g_jianpan, SGL_COLOR_CYAN);

    /* 设置按钮边框宽度 */
    sgl_keyboard_set_btn_border_width(g_jianpan, 1);

    /* 设置按钮边框透明度 */
    sgl_keyboard_set_btn_border_alpha(g_jianpan, 200);

    /* 获取操作码 */
    sgl_keyboard_get_opcode(g_jianpan);

    /* 设置文本输入区缓冲区 */
    sgl_keyboard_set_textarea(g_jianpan, g_edit_buf, sizeof(g_edit_buf));

    /* 注册事件回调：按键后刷新显示 */
    sgl_obj_set_event_cb(g_jianpan, keyboard_event, NULL);
}

/* 调出键盘按钮回调 */
static void btn_open_kbd(sgl_event_t *e)
{
    (void)e;
    /* 清空输入缓冲区 */
    g_edit_buf[0] = '\0';
    if (g_disp) {
        sgl_obj_set_dirty(g_disp);
    }
    if (g_jianpan == NULL || g_jianpan->destroyed) {
        create_keyboard();
    } else {
        g_jianpan->hide = 0;
    }
}

void sgd_keyboard_demo(sgl_obj_t *parent)
{
    g_parent = parent;

    /* 创建文本框（放在键盘上方，支持多行显示）*/
    g_disp = sgl_textbox_create(parent);
    sgl_obj_set_pos(g_disp, 20, 15);
    sgl_obj_set_size(g_disp, 280, 36);
    sgl_textbox_set_text_font(g_disp, &consolas14);
    sgl_textbox_set_text_color(g_disp, SGL_COLOR_WHITE);
    sgl_textbox_set_bg_color(g_disp, SGL_COLOR_DARK_GRAY);
    sgl_textbox_set_radius(g_disp, 4);
    sgl_textbox_set_text(g_disp, g_edit_buf);

    /* 创建键盘 */
    create_keyboard();

    /* 调出键盘按钮 */
    sgl_obj_t *btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, 20, 275);
    sgl_obj_set_size(btn, 120, 32);
    sgl_button_set_text(btn, "Show KBD");
    sgl_button_set_font(btn, &consolas14);
    sgl_button_set_color(btn, SGL_COLOR_NAVY);
    sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
    sgl_button_set_radius(btn, 4);
    sgl_obj_set_event_cb(btn, btn_open_kbd, NULL);
}
#endif
