/*
 * ao_ui.h
 *
 *  Created on: May 9, 2024
 *      Author: Grupo_3
 */

#ifndef AO_UI_H_
#define AO_UI_H_

#include "cmsis_os.h"
#include "stm32f4xx_hal.h"

#include "dwt.h"
#include "board.h"
#include "logger.h"
#include "oa_led.h"
#include "task_button.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// Estructura del objeto activo de la interfaz de usuario
typedef struct {
    ButtonActiveObject_t *button_ao; // Referencia al objeto activo del botón
    LEDActiveObject *led_ao;         // Referencia al objeto activo de los LEDs
} UIActiveObject_t;

// Prototipos de funciones
void ui_initialize_ao(UIActiveObject_t *ao, ButtonActiveObject_t *button_ao);
void ui_destroy_ao(UIActiveObject_t *ao);
void ui_task(void *parameters);

#endif /* AO_UI_H_ */
