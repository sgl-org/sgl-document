/**
 ****************************************************************************************************
 * @file        sgldemo.h
 * @brief       SGL 控件 Demo 公共头文件
 *             所有坐标/尺寸基于 SGL_SCREEN_WIDTH / HEIGHT，自动适配不同分辨率
 *             
 *             使用方式：
 *               1. 将需要测试的 Demo 对应的开关宏设为 1
 *               2. 在 Keil 工程中添加对应的 .c 文件（SGL_Demo/sgl_xxx_demo.c）
 *               3. 编译运行
 *               
 *             开关宏 = 1 ：启用该 Demo
 *             开关宏 = 0 ：禁用该 Demo（不会编译对应的代码）
 ****************************************************************************************************
 本 demo 请优先学习一下标签和按钮，因为标签和按钮到时候会和其他进行交互的
 
 */
#ifndef __SGLDEMO_H__
#define __SGLDEMO_H__

#include "sgl.h"
#include <sgl_event.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern const sgl_font_t ChironGoRoundTC_700B_24;
/* ================================================================
 * Demo 开关宏 — 设为 1 启用，设为 0 禁用
 * 用户只需打开需要的 Demo，并在 Keil 中添加对应的 .c 文件
 * ================================================================ */
#define SGD_ENABLE_LABEL            1
#define SGD_ENABLE_BUTTON           0
#define SGD_ENABLE_SLIDER           0
#define SGD_ENABLE_PROGRESS         0
#define SGD_ENABLE_BAR              0
#define SGD_ENABLE_SWITCH           0
#define SGD_ENABLE_TEXTLINE         0
#define SGD_ENABLE_TEXTBOX          0
#define SGD_ENABLE_CHECKBOX         0
#define SGD_ENABLE_DROPDOWN         0
#define SGD_ENABLE_CIRCLE           0
#define SGD_ENABLE_ARC              0
#define SGD_ENABLE_RECTANGLE        0
#define SGD_ENABLE_LINE             0
#define SGD_ENABLE_RING             0
#define SGD_ENABLE_POLYGON          0
#define SGD_ENABLE_LED              0
#define SGD_ENABLE_2DBALL           0
#define SGD_ENABLE_GAUGE            0
#define SGD_ENABLE_BATTERY          0
#define SGD_ENABLE_ANALOGCLOCK      0
#define SGD_ENABLE_STATUSBAR        0
#define SGD_ENABLE_ROLLER           0
#define SGD_ENABLE_VIEWLIST         0
#define SGD_ENABLE_TEXTLIST         0
//#define SGD_ENABLE_SCROLL           0//不会修，有bug,存在功能重复控件， 讨论决定删除这个控件
#define SGD_ENABLE_SCOPE            0
#define SGD_ENABLE_SPECTRUM         0
#define SGD_ENABLE_WIN              0
#define SGD_ENABLE_MSGBOX           0
#define SGD_ENABLE_BOX              0
#define SGD_ENABLE_CANVAS           0
#define SGD_ENABLE_IMG              0
#define SGD_ENABLE_ICON             0
#define SGD_ENABLE_SPRITE           0
#define SGD_ENABLE_QRCODE           0
#define SGD_ENABLE_NUMBERKBD        0
#define SGD_ENABLE_KEYBOARD         0
#define SGD_ENABLE_LAUNCHER         0
#define SGD_ENABLE_TIMER            0
#define SGD_ENABLE_3DVORTEX         0
#define SGD_ENABLE_ARC_LABEL        0
#define SGD_ENABLE_PIECHART         0
#define SGD_ENABLE_BARCHART         0
#define SGD_ENABLE_LINECHART        0

/* 屏幕自适应宏 */
#define SGD_MG       (SGL_SCREEN_WIDTH  * 5 / 160)   /* 边距 ≈ 5@320宽 */
#define SGD_GAP      (SGL_SCREEN_HEIGHT * 2 / 240)   /* 行间距 ≈ 2@240高 */
#define SGD_H        (SGL_SCREEN_HEIGHT * 30 / 240)  /* 控件高  ≈ 30@240高 */
#define SGD_W        (SGL_SCREEN_WIDTH  - SGD_MG * 2)

/* ================================================================
 * Demo 函数声明（按开关宏条件编译）
 * ================================================================ */
#if SGD_ENABLE_LABEL
void sgd_label_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_BUTTON
void sgd_button_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_SLIDER
void sgd_slider_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_PROGRESS
void sgd_progress_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_BAR
void sgd_bar_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_SWITCH
void sgd_switch_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_TEXTLINE
void sgd_textline_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_TEXTBOX
void sgd_textbox_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_CHECKBOX
void sgd_checkbox_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_DROPDOWN
void sgd_dropdown_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_CIRCLE
void sgd_circle_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_ARC
void sgd_arc_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_RECTANGLE
void sgd_rectangle_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_LINE
void sgd_line_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_RING
void sgd_ring_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_POLYGON
void sgd_polygon_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_LED
void sgd_led_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_2DBALL
void sgd_2dball_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_GAUGE
void sgd_gauge_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_BATTERY
void sgd_battery_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_ANALOGCLOCK
void sgd_analogclock_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_STATUSBAR
void sgd_statusbar_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_ROLLER
void sgd_roller_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_VIEWLIST
void sgd_viewlist_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_TEXTLIST
void sgd_textlist_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_SCROLL
void sgd_scroll_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_SCOPE
void sgd_scope_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_SPECTRUM
void sgd_spectrum_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_WIN
void sgd_win_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_MSGBOX
void sgd_msgbox_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_BOX
void sgd_box_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_CANVAS
void sgd_canvas_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_IMG
void sgd_img_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_ICON
void sgd_icon_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_SPRITE
void sgd_sprite_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_QRCODE
void sgd_qrcode_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_NUMBERKBD
void sgd_numberkbd_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_KEYBOARD
void sgd_keyboard_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_LAUNCHER
void sgd_launcher_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_TIMER
void sgd_timer_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_3DVORTEX
void sgd_3dvortex_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_ARC_LABEL
void sgd_arc_label_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_PIECHART
void sgd_piechart_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_BARCHART
void sgd_barchart_demo(sgl_obj_t *parent);
#endif
#if SGD_ENABLE_LINECHART
void sgd_linechart_demo(sgl_obj_t *parent);
#endif

#endif /* __SGLDEMO_H__ */
