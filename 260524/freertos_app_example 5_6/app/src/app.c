/*
 * app.c
 *
 *  Created on: May 9, 2024
 *      Author: Grupo_3
 */

#include "app.h"

/* Message */
const char *p_sys =
		" --> RTOS2-TP2 <--> Developed by: Tatiana, Lautaro y Royer.\r\n";




// Configuration for button
ButtonConfig_t button_config = { .port = PORT_BUTTON, .pin = PIN_BUTTON };

// Active objects
ButtonActiveObject_t button_ao;
UIActiveObject_t ui_ao;

/**
 * @brief Initializes the application components.
 */
void app_init(void) {
    LOGGER_LOG(p_sys);

    button_initialize_ao(&button_ao, button_config, "Button AO");

    // Inicializar el objeto activo de la interfaz de usuario
    ui_initialize_ao(&ui_ao, &button_ao);

    // Initialize cycle counter
    cycle_counter_init();
}
