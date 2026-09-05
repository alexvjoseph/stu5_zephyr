/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <stdio.h>

#include "led.h"
#include "button.h"
#include "thread.h"
#include "led_burst.h"

#if !DT_HAS_ALIAS(led00)
    #error "Missing devicetree alias: led00, add it under /aliases node"
#endif
#if !DT_HAS_ALIAS(led01)
    #error "Missing devicetree alias: led01, add it under /aliases node"
#endif
#if !DT_HAS_ALIAS(led02)
    #error "Missing devicetree alias: led02, add it under /aliases node"
#endif

#if !DT_HAS_ALIAS(button)
    #error "Missing devicetree alias: button, add it under /aliases node"
#endif


struct led_burst_ctx led_burst;

/* Fetch properties from DT */
static usr_led led1 = { .gpio = &(struct gpio_dt_spec)GPIO_DT_SPEC_GET(DT_ALIAS(led00), gpios), .led_state = 1 };
static usr_led led2 = { .gpio = &(struct gpio_dt_spec)GPIO_DT_SPEC_GET(DT_ALIAS(led01), gpios), .led_state = 2 };
static usr_led led3 = { .gpio = &(struct gpio_dt_spec)GPIO_DT_SPEC_GET(DT_ALIAS(led02), gpios), .led_state = 3 };

static usr_button button = {    .gpio = &(struct gpio_dt_spec)GPIO_DT_SPEC_GET(DT_ALIAS(button), gpios), 
                                //.button_cb is left zero-initialized here,  initialized at runtime using the gpio_init_callback()
                                .app_cb = on_button
                           };

int main(void)
{
    // 1. Get the LED device from device tree using led0 alias
    // 2. verify device is ready with device_is_ready
    // 1. Check if the controller driver is ready
    if (led_init(&led1)) {
        return 0; // Driver not instantiated, return zero from main
    }
   //if (led_init(&led2)) {
   //    return 0; // Driver not instantiated, return zero from main
   //}
   //if (led_init(&led3)) {
   //    return 0; // Driver not instantiated, return zero from main
   //}
    
    if (button_init(&button)) {
        return 0; // Driver not instantiated, return zero from main
    }

    led_burst_init(&led_burst, &led1);


    // 4. loop forever: toggle the LED & sleep for 500ms
    while(true){


    //   if(led_toggle(&led1)<0){

    //       return 0;
    //   }
    //   k_msleep(led_get_period_ms());

    //   if(led_toggle(&led2)<0){

    //       return 0;
    //   }

    //   k_msleep(led_get_period_ms());

    //   if(led_toggle(&led3)<0){

    //       return 0;
    //   }
    //   
    //  // printf("LED STATE: %s \n", led1.led_state ? "LED1_ON" : "LED1_OFF");
    //  // printf("LED STATE: %s \n", led2.led_state ? "LED2_ON" : "LED2_OFF");
    //  // printf("LED STATE: %s \n", led3.led_state ? "LED3_ON" : "LED3_OFF");

    //   k_msleep(led_get_period_ms());
    }
    // 5. Print a message on console

	return 0;
}


