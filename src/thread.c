#include "thread.h"
#include "led_burst.h"

/*

#define K_THREAD_DEFINE 	( 		
            name,
			stack_size,
			entry,
			p1,
			p2,
			p3,
			prio,
			options,
			delay )

name	        Name of the thread.
stack_size	    Stack size in bytes.
entry	        Thread entry function, see k_thread_entry_t.
p1	            1st entry point parameter.
p2	            2nd entry point parameter.
p3	            3rd entry point parameter.
prio	        Thread priority.
options	        Thread options.
delay	        Scheduling delay (in milliseconds), zero for no delay.

*/
K_THREAD_DEFINE 	( 		
            button_event_thread_object, 1024,
			button_event_handler,
			NULL,
			NULL,
			NULL,
			3,
			0,
			0 
        );


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

K_MSGQ_DEFINE(button_msgq, sizeof(struct button_event), 10 , 1); 

atomic_t  button_press_count;
extern struct led_burst_ctx led_burst;


void button_event_handler(void *p1, void *p2, void *p3){

     ARG_UNUSED(p1);   
     ARG_UNUSED(p2);
     ARG_UNUSED(p3);

     struct button_event evt;

     while(true){

          k_msgq_get(&button_msgq, &evt, K_FOREVER);

          if(evt.state){
               //pressed

               /* Make increment atomic */
               atomic_inc(&button_press_count);
               led_burst_start_or_restart(&led_burst);
               printf("button pressed, count is: %ld\n", button_press_count);


          } else {
               //released
          }

     }
    
}

void on_button(uint32_t t_ms, uint8_t state){

    struct button_event evt;
    evt.t_ms =  t_ms;
    evt.state =  state;

    //Post message to queue
    if(k_msgq_put(&button_msgq, &evt, K_NO_WAIT) != 0){

    }
}
