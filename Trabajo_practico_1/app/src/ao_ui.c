/*
 * ao_ui.c
 *
 *  Created on: May 9, 2024
 *      Author: Grupo_3
 */

#include "ao_ui.h"

// Define time constants for pulse durations
#define TIME_PULSE_LOW 200
#define TIME_PULSE_MODERATE 1000
#define TIME_PULSE_LONG 2000

void task_user_interface(void *parameters);

/**
 * @brief Initializes the user interface active object.
 *
 * @param parameters Pointer to the interface user active object.
 * @param BAO Pointer to the button active object.
 * @param LAOR Pointer to the red LED active object.
 * @param LAOG Pointer to the green LED active object.
 * @param LAOB Pointer to the blue LED active object.
 */
void user_interface_initialize_ao(void *parameters, void *BAO, void *LAOR,
		void *LAOG, void *LAOB) {
	InterfaceUserActiveObject_t *const AO =
			(InterfaceUserActiveObject_t*) parameters;
	// Allocate memory for message structure
	message_user_interface_t *const message_user_interface =
			(message_user_interface_t*) pvPortMalloc(
					sizeof(message_user_interface_t));
	if (message_user_interface == NULL) {
		return;
	}

	// Initialize message structure
	message_user_interface->BAO_MS_UI = (ButtonActiveObject_t*) BAO;
	message_user_interface->LAOR_MS_UI = (LedActiveObject_t*) LAOR;
	message_user_interface->LAOB_MS_UI = (LedActiveObject_t*) LAOB;
	message_user_interface->LAOG_MS_UI = (LedActiveObject_t*) LAOG;

	// Create task for user interface
	BaseType_t ret = xTaskCreate(task_user_interface, "Task user interface",
			2 * configMINIMAL_STACK_SIZE, (void*) message_user_interface,
			tskIDLE_PRIORITY + 1UL, AO->task_user_interface_h);
	configASSERT(ret == pdPASS);
}

/**
 * @brief Task for handling user interface events.
 *
 * @param parameters Pointer to the message structure for the task.
 */
void task_user_interface(void *parameters) {
	message_user_interface_t *message = (message_user_interface_t*) parameters;
	ButtonActiveObject_t *button = message->BAO_MS_UI;
	LedActiveObject_t *led_red = message->LAOR_MS_UI;
	LedActiveObject_t *led_blue = message->LAOB_MS_UI;
	LedActiveObject_t *led_green = message->LAOG_MS_UI;
	TickType_t event;

	state_button_t pulse = PULSE_OUT;

	while (true) {
		// Receive events from the button queue
		if (xQueueReceive(button->queue_button_h, &event, 0) == pdPASS) {
			// Determine pulse type based on event duration
			if (event < TIME_PULSE_LOW) {
				pulse = PULSE_OUT;
			} else if (event < TIME_PULSE_MODERATE) {
				pulse = PULSE_PULSE;
			} else if (event < TIME_PULSE_LONG) {
				pulse = PULSE_SHORT;
			} else if (event > TIME_PULSE_LONG) {
				pulse = PULSE_LONG;
			} else {
				pulse = PULSE_ERROR;
			}

			// Handle different pulse types
			switch (pulse) {
			case PULSE_PULSE:
				// Send pulse to red LED queue
				if (xQueueSend(led_red->queue_led_h, &pulse, 0) != pdPASS) {
				}
				LOGGER_LOG(" Pulse sent: PULSE_PULSE\r\n")
				;
				break;

			case PULSE_LONG:
				// Send pulse to blue LED queue
				if (xQueueSend(led_blue->queue_led_h, &pulse, 0) != pdPASS) {
				}
				LOGGER_LOG("  Pulse sent: PULSE_LONG\r\n")
				;
				break;

			case PULSE_SHORT:
				// Send pulse to green LED queue
				if (xQueueSend(led_green->queue_led_h, &pulse, 0) != pdPASS) {
				}
				LOGGER_LOG(" Pulse sent: PULSE_SHORT\r\n")
				;
				break;

			default:
				// Invalid pulse type
				LOGGER_LOG("Invalid pulse\r\n")
				;
				break;
			}
		}
	}
}
