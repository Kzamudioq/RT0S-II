/*
 * ao_ui.h
 *
 *  Created on: May 9, 2024
 *      Author: Grupo_3
 */

#ifndef TASK_USER_INTERFACE_H_
#define TASK_USER_INTERFACE_H_

#include "cmsis_os.h"
#include "stm32f4xx_hal.h"

#include "dwt.h"
#include "board.h"
#include "logger.h"
#include "oa_led.h"
#include "task_button.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the structure for the interface user active object
typedef struct {
	TaskHandle_t *task_user_interface_h; // Handle for the user interface task
} InterfaceUserActiveObject_t;

// Define the structure for the message used by the user interface
typedef struct {
	ButtonActiveObject_t *BAO_MS_UI; // Pointer to the button active object
	LedActiveObject_t *LAOR_MS_UI;   // Pointer to the red LED active object
	LedActiveObject_t *LAOG_MS_UI;   // Pointer to the green LED active object
	LedActiveObject_t *LAOB_MS_UI;   // Pointer to the blue LED active object
} message_user_interface_t;

// Function to initialize the user interface active object
void user_interface_initialize_ao(void *parameters, void *BAO, void *LAOR,
		void *LAOG, void *LAOB);

#endif /* TASK_USER_INTERFACE_H_ */
