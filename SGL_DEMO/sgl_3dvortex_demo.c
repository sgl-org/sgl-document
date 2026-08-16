/**
 * @file    sgl_3dvortex_demo.c
 * @brief   SGL 3DVortex 3D 粒子漩涡控件 Demo — 覆盖所有接口
 *          深色背景衬底，展示 3D 粒子漩涡动画
 */
#include "sgl_demo.h"
#if SGD_ENABLE_3DVORTEX
void sgd_3dvortex_demo(sgl_obj_t *parent)
{
    /* 创建深色背景衬底 */
    sgl_obj_t *bg = sgl_rect_create(parent);
    sgl_obj_set_pos(bg, 0, 0);
    sgl_obj_set_size(bg, SGL_SCREEN_WIDTH, SGL_SCREEN_HEIGHT);
    sgl_rect_set_color(bg, sgl_rgb(0x08, 0x08, 0x12));
    sgl_rect_set_alpha(bg, 255);

    /* 创建 3D 粒子漩涡控件 */
    sgl_obj_t *xuanwo = sgl_3dvortex_create(parent);
    sgl_obj_set_pos(xuanwo, 0, 0);
    sgl_obj_set_size(xuanwo, 60, 60);

    /* 设置运行状态（启动粒子动画）*/
    sgl_3dvortex_set_running(xuanwo, true);

    /* 设置拖尾透明度 */
    sgl_3dvortex_set_trail_alpha(xuanwo, 38);

    /* 重置粒子系统（重新初始化粒子位置）*/
    sgl_3dvortex_reset(xuanwo);
}
#endif
