#ifndef THREAD_H
#define THREAD_H

#include "main.h"


struct button_event{
    uint32_t t_ms;
    uint8_t state;
};


void on_button(uint32_t t_ms, uint8_t state);

void button_event_handler(void *p1, void *p2, void *p3);


#endif