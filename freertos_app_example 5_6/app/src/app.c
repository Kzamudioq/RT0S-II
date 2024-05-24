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

// Configuration for LEDs
LedConfig_t led_configs[] = {
    { .port = LED_R_GPIO_Port, .pin = LED_R_Pin, .delay_led = TIME_TURN_ON_LED, .color = RED },
    { .port = LED_G_GPIO_Port, .pin = LED_G_Pin, .delay_led = TIME_TURN_ON_LED, .color = GREEN },
    { .port = LED_B_GPIO_Port, .pin = LED_B_Pin, .delay_led = TIME_TURN_ON_LED, .color = BLUE }
};

// Configuration for button
ButtonConfig_t button_config = { .port = PORT_BUTTON, .pin = PIN_BUTTON };

// Active objects
ButtonActiveObject_t ao_button;
LedActiveObject_t ao_led;
InterfaceUserActiveObject_t ao_user_interface;

/**
 * @brief Initializes the application components.
 */
void app_init(void) {
    LOGGER_LOG(p_sys);

    // Initialize button active object
    button_initialize_ao(&ao_button, button_config, "Task: Button Control");

    // Initialize LED active object
    led_initialize_ao(&ao_led, "Task: LED Control", led_configs, sizeof(led_configs) / sizeof(led_configs[0]));

    // Initialize user interface active object
    user_interface_initialize_ao(&ao_user_interface, &ao_button, &ao_led);

    // Initialize cycle counter
    cycle_counter_init();
}
