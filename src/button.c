#include "button.h"
#include <zephyr/drivers/gpio.h>


int button_init(usr_button *button){
    int ret;
    if(button == NULL){

        return -EINVAL;
    }
    if (!gpio_is_ready_dt(button->gpio)) {
        return -ENODEV; // Driver not instantiated, return zero from main
    }
    // 2. Perform the actual port/pin-level bring-up
    // 3. Configure the LED pin as a GPIO output with initial state off
    
    ret = gpio_pin_configure_dt(button->gpio, GPIO_INPUT);

    if(ret<0){
        return ret;
    }
    
    //1. init the gpio_callback structure
    gpio_init_callback(&button->button_cb, button_isr, BIT(button->gpio->pin));
    
    //2. install button isr (add call back)
    ret = gpio_add_callback_dt(button->gpio, &button->button_cb);
    if(ret<0){
        return ret;
    }
    
    //3. configure the pin for interrupt(edge or level triggering)
    ret = gpio_pin_interrupt_configure_dt( button->gpio, GPIO_INT_EDGE_RISING);
    if(ret<0){
        return ret;
    }
}

void button_isr(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins){
    //CONTAINER_OF(ptr, type, field)
    //ptr: The pointer to the member field.
    //type: The C struct type name of the parent container.
    //field: The specific name of the member field inside the structure that ptr points to.
    
    usr_button *button = CONTAINER_OF(cb, usr_button, button_cb);
    if(button->app_cb != NULL){
        uint32_t tms = k_uptime_get_32();
        uint8_t state = (gpio_pin_get_dt(button->gpio) > 0) ? 1U : 0U;
        button->app_cb(tms, state);
    }

}
