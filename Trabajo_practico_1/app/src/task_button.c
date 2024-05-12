/*
 * task_button.c
 *
 *  Created on: May 9, 2024
 *      Author: royer.sanabria
 */
#include "main.h"
#include "task_button.h"
#include <stdbool.h>
#include "cmsis_os.h"
#include "logger.h"
#include "dwt.h"
#include "board.h"
#include "app.h"
#include "FreeRTOS.h"
/// | define-------------------
#define LENGTH_QUEUE_PULSE 5
#define SIZE_QUEUE_PULSE (sizeof(TickType_t))
#define TASK_PERIOD_MS_         (1000)
#define BUTTON_PRESSED GPIO_PIN_RESET


/// | Private variables ------------------------------

void task_button(void *parameters);

void button_initialize_ao(ButtonActiveObject_t *parameters)
{
	BaseType_t ret;
	ButtonActiveObject_t* const AO = (ButtonActiveObject_t *)parameters;
    ret = xTaskCreate(task_button,
    				  "Task button",
					  (2 * configMINIMAL_STACK_SIZE),
					  (void *)AO,
					  (tskIDLE_PRIORITY + 1UL),
					  AO->task_button_h);
    configASSERT(ret == pdPASS);

     AO->queue_button_h = xQueueCreate(LENGTH_QUEUE_PULSE, SIZE_QUEUE_PULSE);
    configASSERT (AO->queue_button_h != NULL);
 }


 void task_button(void *parameters)
{
	ButtonActiveObject_t* const AO = (ButtonActiveObject_t *)parameters;
	TickType_t time_tick;
	TickType_t check_send;

	while(true)
	{
		if (BUTTON_PRESSED == HAL_GPIO_ReadPin(PORT_BUTTON, PIN_BUTTON))
		{
			time_tick = xTaskGetTickCount();
			while (BUTTON_PRESSED == HAL_GPIO_ReadPin(PORT_BUTTON, PIN_BUTTON))
			{
			}
			time_tick = xTaskGetTickCount() - time_tick;
			check_send = xQueueSend(AO->queue_button_h, &time_tick, 0);
			if (check_send == pdPASS){LOGGER_LOG("\r\n --> Task Button Sending message %d\r\n",time_tick);}
		}
	}
}

