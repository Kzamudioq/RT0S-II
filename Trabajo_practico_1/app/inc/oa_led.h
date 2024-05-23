/*
 * oa_led.h
 *
 *  Created on: May 8, 2024
 *      Author: Grupo_3
 */

#ifndef INC_OA_LED_H_
#define INC_OA_LED_H_

#include "cmsis_os.h"
#include "stm32f4xx_hal.h"

// Define the default time to turn on the LED (in milliseconds)
#define TIME_TURN_ON_LED 1000

// Enumeration for LED colors
typedef enum {
	GREEN, RED, BLUE
} led_type_t;

// Structure to hold LED configuration
typedef struct {
	GPIO_TypeDef *port;     // Pointer to the GPIO port of the LED
	uint16_t pin;           // Pin number of the LED
	TickType_t delay_led;   // Delay duration for the LED
} LedConfig_t;

// Structure for the LED active object
typedef struct {
	QueueHandle_t queue_led_h;  // Handle for the LED queue
	TaskHandle_t *task_led_h;   // Handle for the LED task
	LedConfig_t led_config;     // Configuration for the LED
} LedActiveObject_t;

// Structure for the message used by the LED
typedef struct {
	LedActiveObject_t *LAO_MS_UI;  // Pointer to the LED active object
	led_type_t color_led;           // Color of the LED
} send_message_led_t;

// Function to initialize the LED active object
void led_initialize_ao(void *parameters, const char *ao_task_name,
		led_type_t led_type, LedConfig_t led_config);

#endif /* INC_OA_LED_H_ */
