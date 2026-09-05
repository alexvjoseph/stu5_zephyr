#include "led.h"

#define NODE_IDENT_LEDS DT_PARENT(NODE_IDENT_LED0)

#define DELAY_MS DT_PROP_OR(NODE_IDENT_LEDS, blink_period_ms, 2000) 


int led_init(usr_led *led){

    if(led == NULL){

        return -EINVAL;
    }
    led->led_state =  false;
    if (!gpio_is_ready_dt(led->gpio)) {
        return -ENODEV; // Driver not instantiated, return zero from main
    }
    // 2. Perform the actual port/pin-level bring-up
    // 3. Configure the LED pin as a GPIO output with initial state off
    return gpio_pin_configure_dt(led->gpio, GPIO_OUTPUT_INACTIVE);
}

int led_toggle(usr_led *led){

    int ret;

    if(led == NULL){
        return -EINVAL;
    }
    ret = gpio_pin_toggle_dt(led->gpio); 
    if(ret == 0){

        led->led_state =  !led->led_state;

    }
    return ret;
}

bool led_get_state(void){

    return false;
}

uint32_t led_get_period_ms(void){

    return DELAY_MS;

}

const char *led_get_label(void){

    return 0;

}

int led_off(usr_led *led){

    int ret;

    if(led == NULL){
        return -EINVAL;
    }
    return ret = gpio_pin_set_dt(led->gpio, 0); 
}
