/*
 * led.h
 *
 *  Created on: May 8, 2024
 *      Author: Grupo 3
 */
#include "cmsis_os.h"
#include "queue_priority.h"

#ifndef INC_TASK_LED_H_
#define INC_TASK_LED_H_

/* Global macros ------------------------------------------------------------------------*/
#define LENGTH_QUEUE_LED		10
#define SIZE_QUEUE_LED			(sizeof(stat_led_ts))
#define WITHOUT_MSG				0
/* End global macros --------------------------------------------------------------------*/

/* Global structs -----------------------------------------------------------------------*/
typedef enum led_type {
	GREEN,
	RED,
	BLUE,
	OUT,
} led_type_t;

typedef struct MsgLed {
	led_type_t type_led;
	uint32_t number;
} stat_led_ts;
/* End global structs -------------------------------------------------------------------*/

/* QueueHandle and TaskHandle -----------------------------------------------------------*/
extern priority_queue_t *led_priority_queue;
/* End Queue and TaskHandle -------------------------------------------------------------*/

/* Global function ----------------------------------------------------------------------*/
void LED_Init(void *parameters);
/* End global function ------------------------------------------------------------------*/

#endif /* INC_TASK_LED_H_ */
