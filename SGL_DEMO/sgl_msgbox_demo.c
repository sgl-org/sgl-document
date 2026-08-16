/**
 * @file    sgl_msgbox_demo.c
 * @brief   SGL MsgBox 消息框控件 Demo — 覆盖所有接口
 *          点击 Yes 打开 LED，点击 No 关闭 LED，消息框销毁后可通过按钮重新弹出
 */
#include "sgl_demo.h"
#if SGD_ENABLE_MSGBOX

static sgl_obj_t *g_msgbox = NULL;
static sgl_obj_t *g_led = NULL;
static sgl_obj_t *g_info = NULL;
static sgl_obj_t *g_parent = NULL;
static const char *g_answer = NULL;
static uint8_t g_answer_applied = 0;

static void msgbox_apply_answer(void)
{
    if (g_led == NULL || g_info == NULL || g_answer == NULL || g_answer_applied) {
        return;
    }

    if (strcmp(g_answer, "Yes") == 0) {
        sgl_led_on(g_led);
        sgl_label_set_text_fmt_dynamic(g_info, "Answer: %s | LED: ON", g_answer);
    } else if (strcmp(g_answer, "No") == 0) {
        sgl_led_off(g_led);
        sgl_label_set_text_fmt_dynamic(g_info, "Answer: %s | LED: OFF", g_answer);
    }

    g_answer_applied = 1;
    g_answer = NULL;
}

static void msgbox_event_cb(sgl_event_t *e)
{
    if (e->type == SGL_EVENT_RELEASED || e->type == SGL_EVENT_DESTROYED) {
        msgbox_apply_answer();

        if (e->type == SGL_EVENT_DESTROYED && e->obj == g_msgbox) {
            g_msgbox = NULL;
        }
    }
}

static void create_demo_msgbox(void)
{
    if (g_parent == NULL || g_msgbox != NULL) {
        return;
    }

    g_answer = NULL;
    g_answer_applied = 0;

    g_msgbox = sgl_msgbox_create(g_parent);
    sgl_obj_set_pos(g_msgbox, 30, 40);
    sgl_obj_set_size(g_msgbox, 260, 180);

    /* 设置颜色 */
    sgl_msgbox_set_color(g_msgbox, SGL_COLOR_DARK_GRAY);

    /* 设置透明度 */
    sgl_msgbox_set_alpha(g_msgbox, 230);

    /* 设置主体透明度 */
    sgl_msgbox_set_main_alpha(g_msgbox, 220);

    /* 设置边框透明度 */
    sgl_msgbox_set_border_alpha(g_msgbox, 200);

    /* 设置圆角 */
    sgl_msgbox_set_radius(g_msgbox, 6);

    /* 设置边框宽度 */
    sgl_msgbox_set_border_width(g_msgbox, 1);

    /* 设置边框颜色 */
    sgl_msgbox_set_border_color(g_msgbox, SGL_COLOR_CYAN);

    /* 设置字体 */
    sgl_msgbox_set_font(g_msgbox, &consolas14);

    /* 设置标题文字 */
    sgl_msgbox_set_title_text(g_msgbox, "LED Control");

    /* 设置标题文字颜色 */
    sgl_msgbox_set_title_text_color(g_msgbox, SGL_COLOR_WHITE);

    /* 设置消息文字 */
    sgl_msgbox_set_msg_text(g_msgbox, "Turn the indicator LED on?\nYes = ON, No = OFF");

    /* 设置消息文字颜色 */
    sgl_msgbox_set_msg_text_color(g_msgbox, SGL_COLOR_WHITE);

    /* 设置消息行间距 */
    sgl_msgbox_set_msg_line_margin(g_msgbox, 4);

    /* 设置左按钮文字 */
    sgl_msgbox_set_left_btn_text(g_msgbox, "Yes");

    /* 设置左按钮文字颜色 */
    sgl_msgbox_set_left_btn_text_color(g_msgbox, SGL_COLOR_WHITE);

    /* 设置左按钮颜色 */
    sgl_msgbox_set_left_btn_color(g_msgbox, SGL_COLOR_DODGER_BLUE);

    /* 设置右按钮文字 */
    sgl_msgbox_set_right_btn_text(g_msgbox, "No");

    /* 设置右按钮文字颜色 */
    sgl_msgbox_set_right_btn_text_color(g_msgbox, SGL_COLOR_WHITE);

    /* 设置右按钮颜色 */
    sgl_msgbox_set_right_btn_color(g_msgbox, SGL_COLOR_TOMATO);

    /* 设置退出应答指针：消息框销毁后，这里会指向用户点击的按钮文字 */
    sgl_msgbox_set_exit_answer(g_msgbox, &g_answer);

    /* 获取当前按钮文字 */
    sgl_msgbox_get_current_btn(g_msgbox);

    /* 设置标题高度 */
    sgl_msgbox_set_title_height(g_msgbox, 30);

    /* 设置消息偏移 */
    sgl_msgbox_set_msg_x_offset(g_msgbox, 8);
    sgl_msgbox_set_msg_y_offset(g_msgbox, 6);

    /* 注册事件：消息框点击按钮销毁时，立即把 Yes/No 应答应用到 LED */
    sgl_obj_set_event_cb(g_msgbox, msgbox_event_cb, NULL);
}

static void btn_open_msgbox(sgl_event_t *e)
{
    if (e->type != SGL_EVENT_CLICKED) {
        return;
    }

    if (g_msgbox && !sgl_obj_is_destroyed(g_msgbox)) {
        sgl_obj_set_visible(g_msgbox);
        return;
    }

    g_msgbox = NULL;
    create_demo_msgbox();
}

static void msgbox_trigger_button(bool left)
{
    if (g_msgbox == NULL || sgl_obj_is_destroyed(g_msgbox)) {
        return;
    }

    sgl_msgbox_t *msgbox = sgl_container_of(g_msgbox, sgl_msgbox_t, obj);
    int16_t x_mid = (g_msgbox->coords.x1 + g_msgbox->coords.x2) / 2;
    int16_t y = g_msgbox->coords.y2 - sgl_font_get_height(msgbox->font);
    int16_t x = left ? (g_msgbox->coords.x1 + x_mid) / 2 : (x_mid + g_msgbox->coords.x2) / 2;
    sgl_event_t evt = {
        .obj = g_msgbox,
        .pos = { .x = x, .y = y },
    };

    evt.type = SGL_EVENT_PRESSED;
    sgl_event_send(evt);

    evt.type = SGL_EVENT_RELEASED;
    sgl_event_send(evt);
}

static void btn_trigger_yes(sgl_event_t *e)
{
    if (e->type != SGL_EVENT_CLICKED || g_msgbox == NULL || sgl_obj_is_destroyed(g_msgbox)) {
        return;
    }

    /* 发送一组命中左按钮区域的标准按下/释放事件，等价于真正点击 Yes */
    msgbox_trigger_button(true);
}

static void btn_trigger_no(sgl_event_t *e)
{
    if (e->type != SGL_EVENT_CLICKED || g_msgbox == NULL || sgl_obj_is_destroyed(g_msgbox)) {
        return;
    }

    /* 发送一组命中右按钮区域的标准按下/释放事件，等价于真正点击 No */
    msgbox_trigger_button(false);
}

void sgd_msgbox_demo(sgl_obj_t *parent)
{
    g_parent = parent;

    /* ================================================================
     * 1) LED 指示灯 — 用来演示消息框按钮对外部控件的控制效果
     * ================================================================ */
    g_led = sgl_led_create(parent);
    sgl_obj_set_pos(g_led, 132, 235);
    sgl_obj_set_size(g_led, 56, 56);
    sgl_led_set_radius(g_led, 28);
    sgl_led_set_on_color(g_led, SGL_COLOR_LIME);
    sgl_led_set_off_color(g_led, SGL_COLOR_DARK_GRAY);
    sgl_led_set_bg_color(g_led, SGL_COLOR_DARK_GRAY);
    sgl_led_set_alpha(g_led, 220);
    sgl_led_off(g_led);

    /* 状态标签：使用 FMT 动态显示最近一次答案和 LED 状态 */
    g_info = sgl_label_create(parent);
    sgl_obj_set_pos(g_info, 40, 300);
    sgl_obj_set_size(g_info, 240, 24);
    sgl_label_set_font(g_info, &consolas14);
    sgl_label_set_text_color(g_info, SGL_COLOR_WHITE);
    sgl_label_set_text_align(g_info, SGL_ALIGN_CENTER);
    sgl_label_set_text_fmt_dynamic(g_info, "Answer: <none> | LED: OFF");

    /* ================================================================
     * 2) 初始消息框
     * ================================================================ */
    create_demo_msgbox();

    /* ================================================================
     * 3) 外部按钮触发消息框
     *    既演示重新弹出，也演示非触摸场景下通过按键事件触发 Yes/No
     * ================================================================ */
    sgl_obj_t *btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, 20, 340);
    sgl_obj_set_size(btn, 92, 30);
    sgl_button_set_text(btn, "Open MsgBox");
    sgl_button_set_font(btn, &consolas14);
    sgl_button_set_color(btn, SGL_COLOR_NAVY);
    sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
    sgl_button_set_radius(btn, 4);
    sgl_obj_set_event_cb(btn, btn_open_msgbox, NULL);

    btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, 116, 340);
    sgl_obj_set_size(btn, 84, 30);
    sgl_button_set_text(btn, "Trigger Yes");
    sgl_button_set_font(btn, &consolas14);
    sgl_button_set_color(btn, SGL_COLOR_DODGER_BLUE);
    sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
    sgl_button_set_radius(btn, 4);
    sgl_obj_set_event_cb(btn, btn_trigger_yes, NULL);

    btn = sgl_button_create(parent);
    sgl_obj_set_pos(btn, 204, 340);
    sgl_obj_set_size(btn, 84, 30);
    sgl_button_set_text(btn, "Trigger No");
    sgl_button_set_font(btn, &consolas14);
    sgl_button_set_color(btn, SGL_COLOR_TOMATO);
    sgl_button_set_text_color(btn, SGL_COLOR_WHITE);
    sgl_button_set_radius(btn, 4);
    sgl_obj_set_event_cb(btn, btn_trigger_no, NULL);
}

#endif
