/*
 * led.h
 *
 *  Created on: May 8, 2024
 *      Author: royer.sanabria
 */
#include "cmsis_os.h"

#ifndef INC_TASK_LED_H_
#define INC_TASK_LED_H_



typedef enum state_button
{
	PULSE_OUT,
	PULSE_PULSE,
	PULSE_SHORT,
	PULSE_LONG,
	PULSE_ERROR,
}state_button_t;

typedef struct LedActiveObject
{
    QueueHandle_t queue_led_h;
    TaskHandle_t *task_led_h;
} LedActiveObject_t;

typedef enum led_type{
	GREEN,
	RED,
	BLUE,
}led_type_t;

typedef struct config_led{
	led_type_t color_led;
	TickType_t time_led;
}config_led_t;

void led_initialize_ao(void* parameters, const char* ao_task_name, led_type_t led_type);

#endif /* INC_TASK_LED_H_ */
