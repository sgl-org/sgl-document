/**
 * @file    sgl_timer_demo.c
 * @brief   SGL Timer 定时器控件 Demo — 覆盖所有接口
 
 使用sgl的timer，需要调用sgl_timer_handler();这个接口，需要在毫秒定时器里面调用这个接口，
 或者把它和sgl_tick_inc(1);放一起，这样可以节省定时器
 例如：
//你的SysTick中断处理函数，定时时间为1ms（不一定非得是SusTick这个函数，定时器中断也可以）
void SysTick_Handler(void)
{
    sgl_tick_inc(1);
    sgl_timer_handler();//放一起
}

 */
#include "sgl_demo.h"
#if SGD_ENABLE_TIMER
static uint32_t g_timer_cnt = 0;

static void timer_callback(const sgl_timer_t *timer, void *user_data)
{
    (void)timer;
    (void)user_data;
    g_timer_cnt++;
		sgl_log("TIMER","App clicked: %d", g_timer_cnt);
}

void sgd_timer_demo(sgl_obj_t *parent)
{
    /* 创建定时器 */
    sgl_timer_t *timer = sgl_timer_create();
    if (timer == NULL) return;

    /* 设置定时器：周期 100ms，循环 5 次 */
    if (!sgl_timer_setup(timer, timer_callback, 100, 5, NULL)) {
        sgl_timer_delete(timer);
        return;
    }
}
#endif
