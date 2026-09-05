#ifndef LED_H
#define LED_H

#include <stdint.h>
#include <stdbool.h>
#include "main.h"

#define NODE_IDENT_LED0 DT_ALIAS(led00)

typedef struct {
    const struct gpio_dt_spec *gpio;
    uint8_t led_state;
} usr_led; 


int led_init(usr_led *led);

int led_toggle(usr_led *led);

bool led_get_state(void);

uint32_t led_get_period_ms(void);

const char *led_get_label(void);

int led_off(usr_led *led);

#endif