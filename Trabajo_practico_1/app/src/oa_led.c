/*
 * oa_led.c
 *
 *  Created on: May 8, 2024
 *   Author: Grupo_3
 */

#include "cmsis_os.h"
#include "logger.h"
#include "board.h"
#include "dwt.h"

#include "oa_led.h"
#include "task_button.h"

#include <stdlib.h>

// Define LED states
#define LED_ON GPIO_PIN_SET
#define LED_OFF GPIO_PIN_RESET
#define LENGTH_QUEUE_PULSE 5
#define SIZE_QUEUE_PULSE sizeof(state_button_t)

// Task function for LED control
static void task_led(void *parameters);

/**
 * @brief Initializes the LED active object.
 *
 * @param parameters Pointer to the LED active object.
 * @param ao_task_name Name of the LED task.
 * @param led_type Type of LED.
 * @param led_config Configuration for the LED.
 */
void led_initialize_ao(void *parameters, const char *ao_task_name,
		led_type_t led_type, LedConfig_t led_config) {
	BaseType_t ret;
	send_message_led_t *const send_message_led =
			(send_message_led_t*) pvPortMalloc(sizeof(send_message_led_t));
	if (send_message_led == NULL) {
		return;
	}

	// Initialize message structure
	send_message_led->LAO_MS_UI = (LedActiveObject_t*) parameters;
	send_message_led->color_led = led_type;

	LedActiveObject_t *AO = (LedActiveObject_t*) parameters;

	// Create LED task
	ret = xTaskCreate(task_led, ao_task_name, 2 * configMINIMAL_STACK_SIZE,
			(void*) send_message_led, tskIDLE_PRIORITY + 1UL, AO->task_led_h);
	configASSERT(ret == pdPASS);

	// Create LED queue
	AO->queue_led_h = xQueueCreate(LENGTH_QUEUE_PULSE, SIZE_QUEUE_PULSE);
	configASSERT(AO->queue_led_h != NULL);

	// Assign LED configuration
	AO->led_config = led_config;

	LOGGER_LOG(" --> '%s' created for LED control\r\n", ao_task_name);
}

/**
 * @brief Task for controlling the LED.
 *
 * @param parameters Pointer to the message structure for the task.
 */
void task_led(void *parameters) {
	send_message_led_t *message = (send_message_led_t*) parameters;
	LedActiveObject_t *led = message->LAO_MS_UI;
	state_button_t event;

	GPIO_TypeDef *port = led->led_config.port;
	uint16_t pin = led->led_config.pin;
	TickType_t delay_led = led->led_config.delay_led;

	while (true) {
		// Receive events from the LED queue
		if (xQueueReceive(led->queue_led_h, &event, portMAX_DELAY) == pdPASS) {
			LOGGER_LOG(" LED turned ON by: %s\r\n", pcTaskGetName(NULL));
			// Turn on LED
			HAL_GPIO_WritePin(port, pin, LED_ON);
			HAL_Delay(delay_led);
			// Turn off LED
			HAL_GPIO_WritePin(port, pin, LED_OFF);
			LOGGER_LOG(" LED turned OFF by: %s\r\n", pcTaskGetName(NULL));
		}
	}
}
