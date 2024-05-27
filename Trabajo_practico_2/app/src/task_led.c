/*
 * led.c
 *
 *  Created on: May 8, 2024
 *      Author: Grupo_3
 */

/* Inclusions ---------------------------------------------------------------------------*/
#include "task_led.h"
#include "main.h"
#include "cmsis_os.h"
#include "logger.h"
#include "dwt.h"
#include "app.h"
#include "board.h"
#include "task_user_interface.h"
#include <stdlib.h>

/* Local macros -------------------------------------------------------------------------*/
#define LED_ON					GPIO_PIN_SET
#define LED_OFF					GPIO_PIN_RESET
#define TIME_LED_RED			1000
#define TIME_LED_GREEN			3000
#define TIME_LED_BLUE			2000
/* End local macros ---------------------------------------------------------------------*/

/* Local structs ------------------------------------------------------------------------*/
/* End structs --------------------------------------------------------------------------*/

/* Queues, TaskHandles and Active Objects -----------------------------------------------*/
/* End Queues. taskHandles and Active Objects -------------------------------------------*/

/* Local Functions ----------------------------------------------------------------------*/
void Process_Led_Msg(stat_led_ts *type_led);
void Check_And_Delet_Task();
void Led_Task();
/* End local functions ------------------------------------------------------------------*/

/* Define local variables ----------------------------------------------------------------*/
/* End define local variables ------------------------------------------------------------*/

/* Goblal functions ----------------------------------------------------------------------*/
/**
 * @brief: Initializes the LED task and creates the necessary task.
 * @parameters:
 * - parameters: Pointer to the parameters structure for active object initialization.
 * @retval: None
 * @note: None.
 */
void LED_Init(void *parameters) {

	params_ao *led = (params_ao*) parameters;
	BaseType_t ret;
	ret = xTaskCreate(Led_Task, "TASK LED", (2 * configMINIMAL_STACK_SIZE),
	NULL, (tskIDLE_PRIORITY + 1UL), &led->OA_th);
	configASSERT(ret == pdPASS);
	LOGGER_LOG(" *** TASK LED CREATED ***\n\r");
}
/* End global functions ------------------------------------------------------------------*/

/* Local functions -----------------------------------------------------------------------*/
/**
 * @brief: Task responsible for handling LED messages.
 * @parameters: None
 * @retval: None
 * @note: Continuously receives LED messages from the LED queue, processes them, frees the
 * allocated memory, and checks if the task should be deleted.
 */
void Led_Task() {
	stat_led_ts *type_led;
	LOGGER_LOG(" *** TASK LED RUNNING *** \r\n");
	for (;;) {
		if (pdPASS == xQueueReceive(led_ao.OA_qh, &type_led, 0)) {
			Process_Led_Msg(type_led);
			vPortFree(type_led);
			Check_And_Delet_Task();
		}
	}
}

/**
 * @brief: Checks the number of messages in the LED queue and deletes the task if the queue is empty.
 * @parameters: None
 * @retval: None
 * @note: Logs the number of free spaces in the queue. If the queue is empty, the task deletes itself
 * and sets its handle to NULL.
 */
void Check_And_Delet_Task() {
	UBaseType_t msg_waiting = uxQueueMessagesWaiting(led_ao.OA_qh);
	if (msg_waiting > WITHOUT_MSG) {
		msg_waiting = LENGTH_QUEUE_LED - uxQueueMessagesWaiting(led_ao.OA_qh);
		LOGGER_LOG(" <<< FREE SPACES: %lu to %d >>> \r\n", msg_waiting,
				LENGTH_QUEUE_LED);
	} else {
		LOGGER_LOG(" <<< FREE SPACES: ALL - LED TASK DELETED >>>");
		led_ao.OA_th = NULL;
		vTaskDelete(NULL);
	}
}

/**
 * @brief: Processes the LED message and controls the corresponding LED based on the
 * message type.
 * @parameters:
 * - type_led: Pointer to a structure containing the LED type.
 * @retval: None
 * @note: This function logs the LED operation, turns the corresponding LED on for a specified
 * time, and then turns it off.
 */
void Process_Led_Msg(stat_led_ts *type_led) {
	switch (type_led->type_led) {
	case RED:
		LOGGER_LOG(" --> Led red: ON <-> %d s.\r\n ", TIME_LED_RED)
		;
		HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, LED_ON);
		HAL_Delay(TIME_LED_RED);
		HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, LED_OFF);
		break;

	case GREEN:
		LOGGER_LOG(" --> Led green: ON <-> %d s. \r\n ", TIME_LED_GREEN)
		;
		HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, LED_ON);
		HAL_Delay(TIME_LED_GREEN);
		HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, LED_OFF);
		break;

	case BLUE:
		LOGGER_LOG(" --> Led blue: ON <-> %d s. \r\n ", TIME_LED_BLUE)
		;
		HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, LED_ON);
		HAL_Delay(TIME_LED_BLUE);
		HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, LED_OFF);
		break;
	default:
		break;
	}
}
/* End local functions -------------------------------------------------------------------*/

