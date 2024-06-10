/*
 * task_button.c
 *
 *  Created on: May 9, 2024
 *      Author: GRUPO_3
 */

/* Inclusions ---------------------------------------------------------------------------*/
#include "main.h"
#include "task_button.h"
#include <stdbool.h>
#include "logger.h"
#include "dwt.h"
#include "board.h"

/* Local macros -------------------------------------------------------------------------*/
#define TIME_PULSE_LOW 		200
#define TIME_PULSE_MODERATE 1000
#define TIME_PULSE_LONG		2000
/* End local macros ---------------------------------------------------------------------*/

/* Local structs ------------------------------------------------------------------------*/
/* End structs --------------------------------------------------------------------------*/

/* Queues, TaskHandles and Active Objects -----------------------------------------------*/
QueueHandle_t button_q;
/* End Queues. taskHandles and Active Objects -------------------------------------------*/

/* Local Functions ----------------------------------------------------------------------*/
void Task_BTN();
/* End local functions ------------------------------------------------------------------*/

/* Define local variables ----------------------------------------------------------------*/
/* End define local variables ------------------------------------------------------------*/

/* Goblal functions ----------------------------------------------------------------------*/
/**
 * @brief: Initializes the button task and assigns the button queue.
 * @parameters:
 * - queue: A pointer to the queue UI.
 * @retval: None.
 * @note: This function creates a task for button handling. function without a TaskHandle.
 */
void BTN_Init(void *queue) {
	button_q = *((QueueHandle_t*) queue);
	BaseType_t ret;
	ret = xTaskCreate(Task_BTN, "BUTTON", (2 * configMINIMAL_STACK_SIZE),
	NULL, (tskIDLE_PRIORITY + 1UL),
	NULL);
	configASSERT(ret == pdPASS);
	LOGGER_LOG(" *** TASK BUTTON CREATED ***\n\r");
}
/* End global functions ------------------------------------------------------------------*/

/* Local functions -----------------------------------------------------------------------*/
/**
 * @brief:		Get the time the button is pressed and process the data.
 * @parameters:	None.
 * @retval: 	None
 * @note: 		This function categorized the time button pressed in PULSE_OUT (<TIME_PULSE_LOW)
 *				PULSE_PULSE(<TIME_PULSE_MODETATE), PULSE_SHORT (<TIME_PULSE_LONG) and PULSE_LONG
 * 				(>TIME_PULSE_LONG).
 */
void Task_BTN() {
	stat_btn_ts *event;
	TickType_t ticks;
	for (;;) {
		if (BUTTON_PRESSED == BUTTON_READ_A) {
			ticks = xTaskGetTickCount();
			while (BUTTON_PRESSED == BUTTON_READ_A) {
			}

			ticks = xTaskGetTickCount() - ticks;
			event = pvPortMalloc(sizeof(stat_btn_ts));

			if (event != NULL) {
				event->time_pulse = ticks;
				if (event->time_pulse < TIME_PULSE_LOW) {
					event->type_pulse = PULSE_OUT;
				} else if (event->time_pulse < TIME_PULSE_MODERATE) {
					event->type_pulse = PULSE_PULSE;
				} else if (event->time_pulse < TIME_PULSE_LONG) {
					event->type_pulse = PULSE_SHORT;
				} else {
					event->type_pulse = PULSE_LONG;
				}

				if (pdPASS != xQueueSend(button_q, &event, 0)) {
					LOGGER_LOG(" <<< MESSAGE LOST >>> \r\n");
					vPortFree(event);
				}
			} else {
				LOGGER_LOG(" <<< MEMORY ALLOCATION FAILED >>> \r\n");
			}
		}
	}
}
/* End local functions -------------------------------------------------------------------*/
