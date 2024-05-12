/*
 * task_user_interface.c
 *
 *  Created on: May 9, 2024
 *      Author: royer.sanabria
 */

#include "main.h"
#include "cmsis_os.h"
#include <stdbool.h>
#include "app.h"
#include "logger.h"
#include "board.h"
#include "dwt.h"
#include "task_user_interface.h"
#include "task_button.h"
#include "task_led.h"
#include <stdlib.h>

#define TIME_PULSE_LOW 			200
#define TIME_PULSE_MODERATE		1000
#define TIME_PULSE_LONG		 	2000
#define TIME_TURN_ON_LED_RED 	1000
#define TIME_TURN_ON_LED_BLUE 	2000
#define TIME_TURN_ON_LED_GREEN	3000

typedef struct send_message_user_interface {
    ButtonActiveObject_t *BAO_MS_UI;
    LedActiveObject_t *LAOR_MS_UI;
    LedActiveObject_t *LAOG_MS_UI;
    LedActiveObject_t *LAOB_MS_UI;
} message_user_interface_t;


void task_user_interface(void *parameters);

void user_interface_initialize_ao(void* parameters, void*  BAO, void*  LAOR, void*  LAOG, void*  LAOB)
{
	InterfaceUserActiveObject_t* const AO = (InterfaceUserActiveObject_t*) parameters;
	message_user_interface_t* const message_user_interface = malloc(sizeof(message_user_interface_t));
	if (message_user_interface == NULL) { return;}


	message_user_interface->BAO_MS_UI = (ButtonActiveObject_t*) BAO;
    message_user_interface->LAOR_MS_UI = (LedActiveObject_t*) LAOR;
    message_user_interface->LAOB_MS_UI = (LedActiveObject_t*) LAOB;
    message_user_interface->LAOG_MS_UI = (LedActiveObject_t*) LAOG;

	BaseType_t ret;
    ret = xTaskCreate(task_user_interface,
    				  "Task user interface",
					  (2 * configMINIMAL_STACK_SIZE),
					  (void *)message_user_interface,
					  (tskIDLE_PRIORITY + 1UL),
					  AO->task_user_interface_h);
    configASSERT(ret == pdPASS);
    // LOGGER_LOG("\r\n --> Initialization of task button completed \r\n");

}


void task_user_interface(void *parameters)
{
	message_user_interface_t* message = (message_user_interface_t*) parameters;
	ButtonActiveObject_t*  button = message->BAO_MS_UI;
	LedActiveObject_t*  led_red= message->LAOR_MS_UI;
	LedActiveObject_t*  led_blue = message->LAOB_MS_UI;
	LedActiveObject_t*  led_green = message->LAOG_MS_UI;
	TickType_t event;

	state_button_t pulse = PULSE_OUT;

    while (true)
    {

    	if (xQueueReceive(button->queue_button_h, &event, portMAX_DELAY) == pdPASS)
    	{
    		LOGGER_LOG("PULSE %lu",event);

        	if(event < TIME_PULSE_LOW){pulse = PULSE_OUT;}
        	else if (event < TIME_PULSE_MODERATE){pulse = PULSE_PULSE;}
        	else if (event < TIME_PULSE_LONG){pulse = PULSE_SHORT;}
        	else if (event > TIME_PULSE_LONG){pulse = PULSE_LONG;}
        	else {pulse=PULSE_ERROR; }
    	}

    	switch (pulse)
    	{
    	case PULSE_PULSE:
    		if(xQueueSend(led_red->queue_led_h, &pulse, portMAX_DELAY) != pdPASS){}
    		    LOGGER_LOG(" -->PULSE SENT TO QUEUE RED\r\n");
    		    break;

    	case PULSE_LONG:
    		if(xQueueSend(led_blue->queue_led_h, &pulse, portMAX_DELAY) != pdPASS){}
    		    LOGGER_LOG(" --> PULSE SENT TO QUEUE BLUE\r\n");
    		    break;

    	case PULSE_SHORT:
    	    if(xQueueSend(led_green->queue_led_h, &pulse, portMAX_DELAY) != pdPASS){}
    	    	LOGGER_LOG(" --> PULSE SENT TO QUEUE GREEN\r\n");
    	    	break;
    	default:
    	    	LOGGER_LOG(" --> PULSE UNSEND\r\n");
    			break;
    	}
    }

}
