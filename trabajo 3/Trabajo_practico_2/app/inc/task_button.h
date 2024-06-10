/*
 * task_button.h
 *
 *  Created on: May 9, 2024
 *      Author: GRUPO 3
 */

#include "cmsis_os.h"
#ifndef INC_TASK_BUTTON_H_
#define INC_TASK_BUTTON_H_

/* Global macros ------------------------------------------------------------------------*/
/* End global macros --------------------------------------------------------------------*/

/* Global structs -----------------------------------------------------------------------*/
typedef enum StatusButton {
	PULSE_PULSE,
	PULSE_SHORT,
	PULSE_LONG,
	PULSE_OUT
} status_button_te;

typedef struct MsgButton {
	status_button_te type_pulse;
	TickType_t time_pulse;
} stat_btn_ts;
/* End global structs -------------------------------------------------------------------*/

/* QueueHandle and TaskHandle -----------------------------------------------------------*/
extern QueueHandle_t button_q;
/* End Queue and TaskHandle -------------------------------------------------------------*/

/* Global function ----------------------------------------------------------------------*/
void BTN_Init(void *QueueButton);
/* End global function ------------------------------------------------------------------*/

#endif /* INC_TASK_BUTTON_H_ */
