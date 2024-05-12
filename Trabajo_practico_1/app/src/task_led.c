/*
 * led.c
 *
 *  Created on: May 8, 2024
 *      Author: royer.sanabria
 */

/********************** inclusions *******************************************/

#include "task_led.h"
#include "main.h"
#include "cmsis_os.h"
#include "logger.h"
#include "dwt.h"
#include "app.h"
#include "board.h"
#include "task_user_interface.h"
#include <stdlib.h>


#define LED_ON					GPIO_PIN_SET
#define LED_OFF					GPIO_PIN_RESET
#define TIME_TURN_ON_LED_RED	1000
#define TIME_TURN_ON_LED_BLUE	1000
#define TIME_TURN_ON_LED_GREEN	1000
#define LENGTH_QUEUE_PULSE 5
#define SIZE_QUEUE_PULSE sizeof(state_button_t)

uint16_t	  ldx_pin[]			= {LED_R_Pin,       LED_G_Pin,       LED_B_Pin};
GPIO_TypeDef* ldx_gpio_port[]	= {LED_R_GPIO_Port, LED_G_GPIO_Port, LED_B_GPIO_Port};

static void task_led(void *parameters);

typedef struct send_message_led {
  LedActiveObject_t *LAO_MS_UI;
  led_type_t color_led;
} send_message_led_t;

typedef enum flag{
	OUT_,
	PULSE_,
	SHORT_,
	LONG_,
	ERROR_,
}flag_t;

void led_initialize_ao(void* parameters, const char* ao_task_name, led_type_t led_type)
{
	BaseType_t ret;
	send_message_led_t* const send_message_led = malloc(sizeof(send_message_led_t));
	if (send_message_led == NULL) { return;}

	send_message_led->LAO_MS_UI = (LedActiveObject_t*) parameters;
	send_message_led->color_led = led_type;

	LedActiveObject_t *AO = (LedActiveObject_t *)parameters;
    ret = xTaskCreate(task_led,
    				  ao_task_name,
					  (2 * configMINIMAL_STACK_SIZE),
					  (void *)send_message_led,
					  (tskIDLE_PRIORITY + 1UL),
					  AO->task_led_h);
    configASSERT(ret == pdPASS);

    AO->queue_led_h = xQueueCreate(LENGTH_QUEUE_PULSE, SIZE_QUEUE_PULSE);
        configASSERT (AO->queue_led_h);
       // LOGGER_LOG("\r\n --> Initialization of task button completed \r\n");
LOGGER_LOG(" --> %s created \r\n", ao_task_name);
}




void task_led(void *parameters)
{

	send_message_led_t* message = (send_message_led_t*) parameters;
	LedActiveObject_t*  led = message->LAO_MS_UI;
	led_type_t pin_led = message->color_led;
	state_button_t event;

	GPIO_TypeDef* port;
	uint16_t	pin;
	TickType_t delay_led;
	TickType_t time_tick;

	if(RED == pin_led){  port=ldx_gpio_port[0];  pin =  ldx_pin[0]; delay_led = TIME_TURN_ON_LED_RED;}
	else if(GREEN== pin_led){port=ldx_gpio_port[1]; pin =  ldx_pin[1]; delay_led = TIME_TURN_ON_LED_GREEN ; }
	else {port=ldx_gpio_port[2]; pin =  ldx_pin[2];delay_led = TIME_TURN_ON_LED_BLUE;}

	while(true)
	{
		if (xQueueReceive(led->queue_led_h, &event, portMAX_DELAY) == pdPASS)
		{
			printf(" --> TURN ON [%s]\r\n", pcTaskGetName(NULL));
			time_tick = xTaskGetTickCount();
			HAL_GPIO_WritePin(port, pin, LED_ON);
			HAL_Delay(delay_led);
			HAL_GPIO_WritePin(port, pin, LED_OFF);
			time_tick = xTaskGetTickCount()-time_tick;
			printf(" --> TURN OFF %s Time ON: %lu \r\n", pcTaskGetName(NULL), time_tick);

		}
	}
}


