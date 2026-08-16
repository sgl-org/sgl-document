/**
 * @file    sgl_img_demo.c
 * @brief   SGL IMG 图片控件 Demo — 覆盖所有 sgl_img_xxx 接口
 这个控件有一个接口，就是设置数量。就是他可以用来点单张图片，也可以用来点 GIF
 但 GIF 的话用连续的图片来点的，通过这个空间可以实现接入 SGL 的定时器或者动画系统来使用 
 Index 这个接口来控制显示图片的的顺序，就比如第一、第二、第三，以此类出推
 还有一个控件叫做imag_EXT这个控件可以读取外部图片也就是说，
 你把图片可以存在外部 flash 里面然后把你的读取外部Flash 
 的接口接入到那个控件的接口里面即可，这边不详细写那个控
 件的作用后续会独立成单独工程以便展示
 */
#include "sgl_demo.h"
#if SGD_ENABLE_IMG
extern const sgl_pixmap_t pic1_pixmap;

void sgd_img_demo(sgl_obj_t *parent)
{
    sgl_obj_t *tupian = sgl_img_create(parent);
    sgl_obj_set_pos(tupian, (SGL_SCREEN_WIDTH - 120) / 2, 30);
    sgl_obj_set_size(tupian, 64, 64);

    /* 设置图片数据 */
    sgl_img_set_pixmap(tupian, &pic1_pixmap);

    /* 设置透明度 */
    sgl_img_set_alpha(tupian, 220);

    /* 第二个图片（带读取操作）*/
    sgl_obj_t *tupian2 = sgl_img_create(parent);
    sgl_obj_set_pos(tupian2, (SGL_SCREEN_WIDTH - 80) / 2, 180);
    sgl_obj_set_size(tupian2, 80, 80);
    sgl_img_set_pixmap(tupian2, &pic1_pixmap);
    sgl_img_set_alpha(tupian2, 180);
    sgl_img_set_pixmap_num(tupian2, 1, false);
    sgl_img_set_pixmap_index(tupian2, 0);
}
#endif
