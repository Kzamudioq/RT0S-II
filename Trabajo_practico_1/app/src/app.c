/*
 * app.c
 *
 *  Created on: May 9, 2024
 *      Author: Grupo_3
 */

#include "app.h"

/* Message */
const char *p_sys =
		" --> RTOS2-TP1 <--> Developed by: Tatiana, Lautaro y Royer.\r\n";

// Configuration for red LED
LedConfig_t led_config_red = { .port = LED_R_GPIO_Port, .pin = LED_R_Pin,
		.delay_led = TIME_TURN_ON_LED };

// Configuration for green LED
LedConfig_t led_config_green = { .port = LED_G_GPIO_Port, .pin = LED_G_Pin,
		.delay_led = TIME_TURN_ON_LED };

// Configuration for blue LED
LedConfig_t led_config_blue = { .port = LED_B_GPIO_Port, .pin = LED_B_Pin,
		.delay_led = TIME_TURN_ON_LED };

// Configuration for button
ButtonConfig_t button_config = { .port = PORT_BUTTON, .pin = PIN_BUTTON };

// Active objects
ButtonActiveObject_t ao_button;
LedActiveObject_t ao_led_red;
LedActiveObject_t ao_led_blue;
LedActiveObject_t ao_led_green;
InterfaceUserActiveObject_t ao_user_interface;

/**
 * @brief Initializes the application components.
 */
void app_init(void) {
	LOGGER_LOG(p_sys);

	// Initialize button active object
	button_initialize_ao(&ao_button, button_config);

	// Initialize LED active objects
	led_initialize_ao(&ao_led_red, "Task: LED RED", RED, led_config_red);
	led_initialize_ao(&ao_led_green, "Task: LED GREEN", GREEN,
			led_config_green);
	led_initialize_ao(&ao_led_blue, "Task: LED BLUE", BLUE, led_config_blue);

	// Initialize user interface active object
	user_interface_initialize_ao(&ao_user_interface, &ao_button, &ao_led_red,
			&ao_led_green, &ao_led_blue);

	// Initialize cycle counter
	cycle_counter_init();
}
