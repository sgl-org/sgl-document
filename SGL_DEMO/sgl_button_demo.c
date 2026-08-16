/**
 * @file    sgl_button_demo.c
 * @brief   SGL Button 控件 Demo — 覆盖所有 sgl_button_xxx 接口
 *          紧凑布局，确保在 320x480 屏幕内完整显示
 */
#include "sgl_demo.h"
#if SGD_ENABLE_BUTTON
/* 图片资源 */
extern const sgl_pixmap_t pic1_pixmap;

/* 按钮尺寸 — 用较小的高度确保所有按钮在屏幕内 */
#define BTN_H  30
#define BTN_GAP 4

static uint32_t sgd_btn_cnt = 0;
static void sgd_btn_click(sgl_event_t *e) {
    if (e->type == SGL_EVENT_CLICKED) {
        sgd_btn_cnt++;
        sgl_log("BUTTON","btn clicked %d\n", (int)sgd_btn_cnt);
    }
}

void sgd_button_demo(sgl_obj_t *parent)
{
    int16_t y = SGD_MG;

    /* [1] 基础按钮 — 默认颜色 + 文本 + 圆角 */
    sgl_obj_t *btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, SGD_MG, y);  sgl_obj_set_size(btn, SGD_W, BTN_H);
    sgl_button_set_font(btn, &consolas14);
    sgl_button_set_text(btn, "[1] Basic Button");
    sgl_button_set_radius(btn, 6);
    sgl_obj_set_event_cb(btn, sgd_btn_click, NULL);
    y += BTN_H + BTN_GAP;

    /* [2] 自定义颜色 + 文字颜色 */
    btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, SGD_MG, y);  sgl_obj_set_size(btn, SGD_W, BTN_H);
    sgl_button_set_font(btn, &consolas14);
    sgl_button_set_text(btn, "[2] Red / White");
    sgl_button_set_color(btn, SGL_COLOR_RED);
    sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
    sgl_button_set_radius(btn, 6);
    sgl_obj_set_event_cb(btn, sgd_btn_click, NULL);
    y += BTN_H + BTN_GAP;

    /* [3] 边框 + 边框颜色 */
    btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, SGD_MG, y);  sgl_obj_set_size(btn, SGD_W, BTN_H);
    sgl_button_set_font(btn, &consolas14);
    sgl_button_set_text(btn, "[3] Border 3");
    sgl_button_set_border_width(btn, 3);
    sgl_button_set_border_color(btn, SGL_COLOR_CYAN);
    sgl_button_set_radius(btn, 6);
    sgl_obj_set_event_cb(btn, sgd_btn_click, NULL);
    y += BTN_H + BTN_GAP;

    /* [4] 半透明按钮 */
    btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, SGD_MG, y);  sgl_obj_set_size(btn, SGD_W, BTN_H);
    sgl_button_set_font(btn, &consolas14);
    sgl_button_set_text(btn, "[4] Alpha=80");
    sgl_button_set_color(btn, SGL_COLOR_DODGER_BLUE);
    sgl_button_set_alpha(btn, 80);
    sgl_button_set_radius(btn, 6);
    sgl_obj_set_event_cb(btn, sgd_btn_click, NULL);
    y += BTN_H + BTN_GAP;

    /* [5] 大字按钮 */
    btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, SGD_MG, y);  sgl_obj_set_size(btn, SGD_W, 34);
    sgl_button_set_font(btn, &consolas23);
    sgl_button_set_text(btn, "[5] Big 23pt");
    sgl_button_set_color(btn, SGL_COLOR_DARK_GREEN);
    sgl_button_set_text_color(btn, SGL_COLOR_LIME);
    sgl_button_set_radius(btn, 8);
    sgl_obj_set_event_cb(btn, sgd_btn_click, NULL);
    y += 34 + BTN_GAP;

    /* [6] 两列并排：左对齐 + 右对齐 */
    {
        int16_t cw = SGD_W / 2 - 3;
        sgl_obj_t *l = sgl_button_create(parent);
        sgl_obj_set_pos(l, SGD_MG, y);  sgl_obj_set_size(l, cw, BTN_H);
        sgl_button_set_font(l, &consolas14);
        sgl_button_set_text(l, "Left");
        sgl_button_set_text_align(l, SGL_ALIGN_LEFT_MID);
        sgl_button_set_color(l, SGL_COLOR_NAVY);
        sgl_button_set_text_color(l, SGL_COLOR_CYAN);
        sgl_button_set_radius(l, 6);
        sgl_obj_set_event_cb(l, sgd_btn_click, NULL);

        sgl_obj_t *r = sgl_button_create(parent);
        sgl_obj_set_pos(r, SGD_MG + cw + 6, y);  sgl_obj_set_size(r, cw, BTN_H);
        sgl_button_set_font(r, &consolas14);
        sgl_button_set_text(r, "Right");
        sgl_button_set_text_align(r, SGL_ALIGN_RIGHT_MID);
        sgl_button_set_color(r, SGL_COLOR_DARK_VIOLET);
        sgl_button_set_text_color(r, SGL_COLOR_WHITE);
        sgl_button_set_radius(r, 6);
        sgl_obj_set_event_cb(r, sgd_btn_click, NULL);
        y += BTN_H + BTN_GAP;
    }

    /* [7] flex 弹性按钮（按下缩小） */
    btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, SGD_MG, y);  sgl_obj_set_size(btn, SGD_W, BTN_H);
    sgl_button_set_font(btn, &consolas14);
    sgl_button_set_text(btn, "[7] Flexible");
    sgl_button_set_color(btn, SGL_COLOR_GOLDENROD);
    sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
    sgl_button_set_radius(btn, 12);
    sgl_obj_set_flexible(btn);
    sgl_obj_set_event_cb(btn, sgd_btn_click, NULL);
    y += BTN_H + BTN_GAP;

    /* [8] 不可点击 + 文字居中 */
    btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, SGD_MG, y);  sgl_obj_set_size(btn, SGD_W, BTN_H);
    sgl_button_set_font(btn, &consolas14);
    sgl_button_set_text(btn, "[8] Disabled");
    sgl_button_set_text_align(btn, SGL_ALIGN_CENTER);
    sgl_button_set_color(btn, SGL_COLOR_DARK_GRAY);
    sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
    sgl_button_set_radius(btn, 6);
    sgl_obj_set_unclickable(btn);
    sgl_obj_set_event_cb(btn, sgd_btn_click, NULL);
    y += BTN_H + BTN_GAP;

    /* [9] 图片背景按钮 (64x64) */
    btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, SGD_MG, y);  sgl_obj_set_size(btn, 64, 64);
    sgl_button_set_pixmap(btn, &pic1_pixmap);
    sgl_button_set_text(btn, "Pic");
    sgl_button_set_font(btn, &consolas14);
    sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
    sgl_obj_set_event_cb(btn, sgd_btn_click, NULL);
    y += 64 + BTN_GAP;
}
#endif