/*
 * task_user_interface.h
 *
 *  Created on: May 9, 2024
 *      Author: Grupo_3
 */
#include "cmsis_os.h"
#include <stdint.h>

#ifndef TASK_USER_INTERFACE_H_
#define TASK_USER_INTERFACE_H_

/* Global macros ------------------------------------------------------------------------*/
/* End global macros --------------------------------------------------------------------*/

/* Global structs -----------------------------------------------------------------------*/
typedef struct ParametersActiveObject {
	TaskHandle_t OA_th;
	QueueHandle_t OA_qh;
} params_ao;
/* End global structs -------------------------------------------------------------------*/

/* QueueHandle and TaskHandle -----------------------------------------------------------*/
extern params_ao led_ao;
/* End Queue and TaskHandle -------------------------------------------------------------*/

/* Global function ----------------------------------------------------------------------*/
void UI_Init(void *parameters);
/* End global function ------------------------------------------------------------------*/

#endif /* TASK_USER_INTERFACE_H_ */
