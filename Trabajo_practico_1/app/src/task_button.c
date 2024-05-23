/*
 * task_button.c
 *
 *  Created on: May 9, 2024
 *      Author: Grupo_3
 */

#include "main.h"
#include "task_button.h"
#include <stdbool.h>
#include "cmsis_os.h"
#include "logger.h"
#include "dwt.h"
#include "board.h"
#include "app.h"

// Define queue length and size for button events
#define LENGTH_QUEUE_PULSE 5
#define SIZE_QUEUE_PULSE (sizeof(TickType_t))
#define BUTTON_PRESSED GPIO_PIN_RESET

// Task function for button handling
void task_button(void *parameters);

/**
 * @brief Initializes the button active object.
 *
 * @param parameters Pointer to the button active object.
 * @param button_config Configuration for the button.
 */
void button_initialize_ao(ButtonActiveObject_t *parameters,
		ButtonConfig_t button_config) {
	BaseType_t ret;
	ButtonActiveObject_t *const AO = (ButtonActiveObject_t*) parameters;

	// Create button task
	ret = xTaskCreate(task_button, "Task button", 2 * configMINIMAL_STACK_SIZE,
			(void*) AO, tskIDLE_PRIORITY + 1UL, AO->task_button_h);
	configASSERT(ret == pdPASS);

	// Create queue for button events
	AO->queue_button_h = xQueueCreate(LENGTH_QUEUE_PULSE, SIZE_QUEUE_PULSE);
	configASSERT(AO->queue_button_h != NULL);

	// Assign button configuration
	AO->button_config = button_config;
}

/**
 * @brief Task for handling button events.
 *
 * @param parameters Pointer to the button active object.
 */
void task_button(void *parameters) {
	ButtonActiveObject_t *const AO = (ButtonActiveObject_t*) parameters;
	ButtonConfig_t *config = &(AO->button_config);
	TickType_t time_tick;
	TickType_t check_send;

	while (true) {
		// Check if button is pressed
		if (BUTTON_PRESSED == HAL_GPIO_ReadPin(config->port, config->pin)) {
			// Record time tick when button is pressed
			time_tick = xTaskGetTickCount();
			// Wait until button is released
			while (BUTTON_PRESSED == HAL_GPIO_ReadPin(config->port, config->pin)) {
			}
			// Calculate time button was held down
			time_tick = xTaskGetTickCount() - time_tick;
			// Send button event to the queue
			check_send = xQueueSend(AO->queue_button_h, &time_tick, 0);
			// Log button event
			if (check_send == pdPASS) {
				LOGGER_LOG("\r\n --> Button event sent  %lu milliseconds\r\n",
						time_tick);
			}
		}
	}
}
