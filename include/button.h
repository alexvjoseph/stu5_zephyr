#ifndef BTN_H
#define BTN_H
#include "main.h"
/*

#define K_MSGQ_DEFINE 	( 		q_name,
			q_msg_size,
			q_max_msgs,
			q_align ) 

q_name	Name of the message queue.
q_msg_size	Message size (in bytes).
q_max_msgs	Maximum number of messages that can be queued.
q_align	Alignment of the message queue's ring buffer (power of 2), ie Address to start the location in RAM).   

*/

typedef void (*button_isr_cb_t)(uint32_t t_ms, uint8_t level);

typedef struct {
    const struct gpio_dt_spec *gpio;
    struct gpio_callback button_cb;
    button_isr_cb_t app_cb;
} usr_button; 


int  button_init(usr_button *button);
void button_isr(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins);

#endif