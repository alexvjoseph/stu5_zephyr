#ifndef LED_BURST_H
#define LED_BURST_H
#include "led.h"

struct led_burst_ctx
{
    uint32_t                toggles_remaining;
    struct k_spinlock       toggle_lock;
    uint32_t                period_ms;
    uint32_t                count;
    struct k_work_delayable work;
    usr_led                 *led;
};

void led_burst_work_handler(struct k_work *work);

void led_burst_init(struct led_burst_ctx *led_burst, usr_led *burst_led);

void led_burst_start_or_restart(struct led_burst_ctx *led_burst);

void led_burst_cancel(struct led_burst_ctx *led_burst);

#endif