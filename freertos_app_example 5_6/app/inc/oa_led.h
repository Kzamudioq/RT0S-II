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
	RED, GREEN, BLUE
} led_type_t;

// Structure to hold LED configuration
typedef struct {
	GPIO_TypeDef *port;     // Pointer to the GPIO port of the LED
	uint16_t pin;           // Pin number of the LED
	TickType_t delay_led;   // Delay duration for the LED
	led_type_t color;       // Color of the LED
} LedConfig_t;

// Structure for the LED active object
typedef struct {
	QueueHandle_t queue_led_h;  // Handle for the LED queue
	TaskHandle_t *task_led_h;   // Handle for the LED task
	LedConfig_t *led_configs;   // Array of LED configurations
	uint8_t num_leds;           // Number of LEDs
} LedActiveObject_t;

// Function to initialize the LED active object
void led_initialize_ao(void *parameters, const char *ao_task_name,
		LedConfig_t *led_configs, uint8_t num_leds);

#endif /* INC_OA_LED_H_ */
