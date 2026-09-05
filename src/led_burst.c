#include "main.h"
#include "led.h"
#include "led_burst.h"





void led_burst_work_handler(struct k_work *work){

    uint32_t remaining = 0;
    //getting  sitruct k_work_delayable work pointer from struct k_work *work
    struct k_work_delayable *dwork = k_work_delayable_from_work(work);

    struct led_burst_ctx *led_brst = CONTAINER_OF(dwork, struct led_burst_ctx, work);

    if(led_brst->toggles_remaining == 0U){
        led_off(led_brst->led);
        return;
    }

    k_spinlock_key_t key = k_spin_lock(&led_brst->toggle_lock);
    led_brst->toggles_remaining--;
    remaining = led_brst->toggles_remaining;
    k_spin_unlock(&led_brst->toggle_lock, key);


    led_toggle(led_brst->led);

    if(remaining > 0){

        (void)k_work_reschedule(&led_brst->work, K_MSEC(led_brst->period_ms));
    }else{

        led_off(led_brst->led);

    }

}

void led_burst_init(struct led_burst_ctx *led_burst, usr_led *burst_led){

    led_burst->period_ms = 250;
    led_burst->count = 6;
    led_burst->toggles_remaining = led_burst->count*2U;
    led_burst->led = burst_led;

    led_off(led_burst->led);


    k_work_init_delayable(&led_burst->work, led_burst_work_handler);
}

void led_burst_start_or_restart(struct led_burst_ctx *led_burst){


    k_spinlock_key_t key = k_spin_lock(&led_burst->toggle_lock);
    led_burst->toggles_remaining = led_burst->count*2U;
    k_spin_unlock(&led_burst->toggle_lock, key);


    (void)k_work_reschedule(&led_burst->work, K_MSEC(500));
}

void led_burst_cancel(struct led_burst_ctx *led_burst){
    (void)k_work_cancel_delayable(&led_burst->work);
    led_off(led_burst->led);
}