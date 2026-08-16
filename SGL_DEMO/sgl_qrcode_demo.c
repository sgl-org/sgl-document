/**
 * @file    sgl_qrcode_demo.c
 * @brief   SGL QRCode 二维码控件 Demo — 覆盖所有接口
 *          内容填入 URL 即可被扫码软件识别跳转
 */
#include "sgl_demo.h"
#if SGD_ENABLE_QRCODE

extern const sgl_pixmap_t pic1_pixmap;

void sgd_qrcode_demo(sgl_obj_t *parent)
{
    /* ================================================================
     * 1) 二维码一 — GitHub 链接
     *    手机扫码可直接跳转浏览器打开
     * ================================================================ */
    sgl_obj_t *erweima = sgl_qrcode_create(parent);
    sgl_obj_set_pos(erweima, (SGL_SCREEN_WIDTH - 140) / 2, 15);
    sgl_obj_set_size(erweima, 140, 140);

    /* 设置二维码版本 */
    sgl_qrcode_set_version(erweima, 5);

    /* 设置纠错等级 */
    sgl_qrcode_set_ecc(erweima, 2);

    /* 设置二维码内容（URL，扫码后自动跳转）*/
    sgl_qrcode_set_text(erweima, "hello sgl");

    /* 设置透明度 */
    sgl_qrcode_set_alpha(erweima, 240);

    /* 设置背景颜色 */
    sgl_qrcode_set_bg_color(erweima, SGL_COLOR_WHITE);

    /* 设置格子颜色 */
    sgl_qrcode_set_cell_color(erweima, SGL_COLOR_BLACK);

    /* 设置格子圆角 */
    sgl_qrcode_set_cell_radius(erweima, 2);

    /* 设置边距 */
    sgl_qrcode_set_zone(erweima, 2);

    /* 设置缩放 */
    sgl_qrcode_set_scale(erweima, 3);

    /* 设置中心 Logo */
    sgl_qrcode_set_logo(erweima, &pic1_pixmap);

    /* 设置 Logo 圆角 */
    sgl_qrcode_set_logo_radius(erweima, 4);

    /* ================================================================
     * 2) 二维码二 — SGL 官网链接
     * ================================================================ */
    erweima = sgl_qrcode_create(parent);
    sgl_obj_set_pos(erweima, (SGL_SCREEN_WIDTH - 140) / 2, 175);
    sgl_obj_set_size(erweima, 140, 140);
    sgl_qrcode_set_version(erweima, 5);
    sgl_qrcode_set_ecc(erweima, 2);
    sgl_qrcode_set_text(erweima, "https://sgl-docs.readthedocs.io");
    sgl_qrcode_set_alpha(erweima, 240);
    sgl_qrcode_set_bg_color(erweima, SGL_COLOR_WHITE);
    sgl_qrcode_set_cell_color(erweima, SGL_COLOR_BLACK);
    sgl_qrcode_set_cell_radius(erweima, 2);
    sgl_qrcode_set_zone(erweima, 2);
    sgl_qrcode_set_scale(erweima, 3);
}
#endif
