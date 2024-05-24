/*
 * task_button.h
 *
 *  Created on: May 9, 2024
 *      Author: Grupo_3
 */

#ifndef INC_TASK_BUTTON_H_
#define INC_TASK_BUTTON_H_

#include "cmsis_os.h"
#include "stm32f4xx_hal.h"

// Structure to hold button configuration
typedef struct {
	GPIO_TypeDef *port;    // Pointer to the GPIO port of the button
	uint16_t pin;          // Pin number of the button
} ButtonConfig_t;

// Structure for the button active object
typedef struct {
	QueueHandle_t queue_button_h;  // Handle for the button queue
	TaskHandle_t *task_button_h;   // Handle for the button task
	ButtonConfig_t button_config;  // Configuration for the button
} ButtonActiveObject_t;

// Enumeration for button states
typedef enum {
	PULSE_OUT,
	PULSE_PULSE,
	PULSE_SHORT,
	PULSE_LONG,
	PULSE_ERROR
} state_button_t;

// Function to initialize the button active object
void button_initialize_ao(ButtonActiveObject_t *parameters,
        ButtonConfig_t button_config, const char *ao_task_name);

#endif /* INC_TASK_BUTTON_H_ */
