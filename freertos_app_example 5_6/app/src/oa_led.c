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

#define LED_ON GPIO_PIN_SET
#define LED_OFF GPIO_PIN_RESET
#define LENGTH_QUEUE_PULSE 5
#define SIZE_QUEUE_PULSE sizeof(state_button_t)

// Array de nombres de colores
const char *color_names[] = { "RED", "GREEN", "BLUE" };

// Task function for LED control
static void task_led(void *parameters);

/**
 * @brief Initializes the LED active object.
 *
 * @param parameters Pointer to the LED active object.
 * @param ao_task_name Name of the LED task.
 * @param led_configs Array of LED configurations.
 * @param num_leds Number of LEDs.
 */
void led_initialize_ao(void *parameters, const char *ao_task_name,
	LedConfig_t *led_configs, uint8_t num_leds) {
	BaseType_t ret;
	LedActiveObject_t *AO = (LedActiveObject_t*) parameters;

	// Create LED task
	ret = xTaskCreate(task_led, ao_task_name, 2 * configMINIMAL_STACK_SIZE,
			(void*) AO, tskIDLE_PRIORITY + 1UL, AO->task_led_h);
	configASSERT(ret == pdPASS);

	// Create LED queue
	AO->queue_led_h = xQueueCreate(LENGTH_QUEUE_PULSE, SIZE_QUEUE_PULSE);
	configASSERT(AO->queue_led_h != NULL);

	// Assign LED configurations
	AO->led_configs = led_configs;
	AO->num_leds = num_leds;

	LOGGER_LOG(" --> '%s' created for LED control\r\n", ao_task_name);
}

/**
 * @brief Task for controlling the LED.
 *
 * @param parameters Pointer to the LED active object.
 */
void task_led(void *parameters) {
	LedActiveObject_t *led = (LedActiveObject_t*) parameters;
	state_button_t event;

	while (true) {
		// Receive events from the LED queue
		if (xQueueReceive(led->queue_led_h, &event, portMAX_DELAY) == pdPASS) {
			uint8_t led_index = event - 1; // Assuming the event indicates LED index
			if (led_index < led->num_leds) {
				LedConfig_t *config = &(led->led_configs[led_index]);
				LOGGER_LOG(" LED of color %s turned ON by: %s\r\n",
						color_names[config->color], pcTaskGetName(NULL));
				// Turn on LED
				HAL_GPIO_WritePin(config->port, config->pin, LED_ON);
				HAL_Delay(config->delay_led);
				// Turn off LED
				HAL_GPIO_WritePin(config->port, config->pin, LED_OFF);
				LOGGER_LOG(" LED of color %s turned OFF by: %s\r\n",
						color_names[config->color], pcTaskGetName(NULL));
			}
		}
	}
}
