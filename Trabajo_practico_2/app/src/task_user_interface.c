/*
 * task_user_interface.c
 *
 *  Created on: May 9, 2024
 *      Author: GRUPO_3
 */

/* Inclusions ---------------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include <stdbool.h>
#include "logger.h"
#include "dwt.h"
#include "task_user_interface.h"
#include "task_button.h"
#include "task_led.h"
#include <stdlib.h>

/* Local macros -------------------------------------------------------------------------*/
#define LENGTH_QUEUE_BUTTON		10
#define SIZE_QUEUE_BUTTON		(sizeof(stat_btn_ts))
#define QUEUE_EMPTY				0
/* End local macros ---------------------------------------------------------------------*/

/* Local structs ------------------------------------------------------------------------*/
/* End structs --------------------------------------------------------------------------*/

/* Queues, TaskHandles and Active Objects -----------------------------------------------*/
params_ao led_ao;
/* End Queues. taskHandles and Active Objects -------------------------------------------*/

/* Local Functions ----------------------------------------------------------------------*/
void UI_Task(void *ui_queue);
void Check_And_CREATE_Task();
bool Status_Task_Led();
/* End local functions ------------------------------------------------------------------*/

/* Define local variables ----------------------------------------------------------------*/
UBaseType_t msg_waiting;
/* End define local variables ------------------------------------------------------------*/

/* Goblal functions ----------------------------------------------------------------------*/
/**
 * @brief: Initializes the UI task and creates UI and LED queues.
 * @parameters:
 * - struct ActiveObject (TaskHandle and QueueHandle)
 * @retval: None
 * @note: 	The task priority may change depending on the requirements.Function call to
 * 			Button_Init();
 */
void UI_Init(void *parameters) {
	params_ao *ui = (params_ao*) parameters;

	ui->OA_qh = xQueueCreate(LENGTH_QUEUE_BUTTON, SIZE_QUEUE_BUTTON);
	configASSERT(ui->OA_qh != NULL);

	led_ao.OA_qh = xQueueCreate(LENGTH_QUEUE_LED, SIZE_QUEUE_LED);
	configASSERT(led_ao.OA_qh != NULL);

	BaseType_t ret;
	ret = xTaskCreate(UI_Task, "USER INTERFACE", (2 * configMINIMAL_STACK_SIZE),
			(void*) ui->OA_qh, (tskIDLE_PRIORITY + 1UL), &ui->OA_th);
	configASSERT(ret == pdPASS);
	LOGGER_LOG(" *** Task USER INTERFACE CREATED ***\n\r");
	BTN_Init(&ui->OA_qh);
}
/* End global functions ------------------------------------------------------------------*/
/**
 *@brief: user interfaz task.
 * @parameters: pointer to event queue button
 * - Pointer to event queue of button.
 * @retval:None.
 * @note: This function received and process event queue button and send the to event queue led.
 */
void UI_Task(void *ui_queue) {
	QueueHandle_t btn_q = (QueueHandle_t) ui_queue;
	stat_btn_ts *status;
	QueueHandle_t led_q = led_ao.OA_qh;

	for (;;) {
		Check_And_CREATE_Task();
		if (pdPASS == xQueueReceive(btn_q, &status, 0)) {
			LOGGER_LOG(" --> Time button pressed: %lu ", status->time_pulse);

			stat_led_ts *event = pvPortMalloc(sizeof(stat_led_ts));
			if (event != NULL) {

				switch (status->type_pulse) {
				case PULSE_PULSE:
					event->type_led = RED;
					LOGGER_LOG(" <-> PULSE-PULSE \r\n")
					;
					break;

				case PULSE_SHORT:
					event->type_led = GREEN;
					LOGGER_LOG(" <-> PULSE-SHORT \r\n")
					;
					break;
				case PULSE_LONG:
					event->type_led = BLUE;
					LOGGER_LOG(" <-> PULSE-LONG \r\n")
					;
					break;
				default:
					event->type_led = OUT;
					LOGGER_LOG(" <-> PULSE-OUT \r\n")
					;
					break;
				}
				vPortFree(status);

				if (event->type_led != OUT) {
					if (pdPASS == xQueueSend(led_ao.OA_qh, &event, 0)) {
					} else {
						LOGGER_LOG(" <<< MESSAGE LOST >>> \r\n");
						vPortFree(event);
					}
				}
			} else {
				LOGGER_LOG("   < MEMORY ALLOCATION FAILED > \r\n");
			}
		}

	}
}
/* Local functions -----------------------------------------------------------------------*/
/**
 * @brief: Check and Create LED Task
 * @parameters: None
 * @retval: None
 * @note: This function checks if the LED task needs to be created and creates it if necessary.
 */
void Check_And_CREATE_Task() {
	if (led_ao.OA_th == NULL
			&& uxQueueMessagesWaiting(led_ao.OA_qh) != WITHOUT_MSG) {
		LED_Init(&led_ao);
	}
}
/* End local functions -------------------------------------------------------------------*/
