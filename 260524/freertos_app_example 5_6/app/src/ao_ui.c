/*
 * ao_ui.c
 *
 *  Created on: May 9, 2024
 *      Author: Grupo_3
 */

#include "ao_ui.h"

// Función de inicialización del objeto activo de la interfaz de usuario
void ui_initialize_ao(UIActiveObject_t *ao, ButtonActiveObject_t *button_ao) {
    ao->button_ao = button_ao;
    ao->led_ao = NULL;

    // Crear la tarea ui_task
    if (xTaskCreate(ui_task, "UI_Task", configMINIMAL_STACK_SIZE, (void *)ao, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
        LOGGER_LOG("Error: Failed to create UI_Task\r\n");
    }
}

// Función para destruir el objeto activo de la interfaz de usuario
void ui_destroy_ao(UIActiveObject_t *ao) {
    // Verificar si hay un objeto activo de LED y destruirlo
    if (ao->led_ao != NULL) {
        led_destroy_ao(ao->led_ao);
        vPortFree(ao->led_ao); // Liberar la memoria asignada por FreeRTOS
        ao->led_ao = NULL;
    }
}

void process_button_event(state_button_t button_state, LEDActiveObject *led_ao) {
    // Loguear el estado del botón
    switch (button_state) {
        case PULSE_PULSE:
            LOGGER_LOG("Estado del botón: PULSE_PULSE\r\n");
            break;
        case PULSE_SHORT:
            LOGGER_LOG("Estado del botón: PULSE_SHORT\r\n");
            break;
        case PULSE_LONG:
            LOGGER_LOG("Estado del botón: PULSE_LONG\r\n");
            break;
        default:
            LOGGER_LOG("Estado del botón: Desconocido\r\n");
            return;
    }

    // Determinar qué LED encender basado en el estado del botón
    uint8_t led_index;
    switch (button_state) {
        case PULSE_PULSE:
            LOGGER_LOG("Encendiendo LED ROJO\r\n");
            led_index = 0; // Índice del LED rojo en led_configs
            break;
        case PULSE_SHORT:
            LOGGER_LOG("Encendiendo LED VERDE\r\n");
            led_index = 1; // Índice del LED verde en led_configs
            break;
        case PULSE_LONG:
            LOGGER_LOG("Encendiendo LED AZUL\r\n");
            led_index = 2; // Índice del LED azul en led_configs
            break;
        default:
            return; // No hacer nada para otros estados del botón
    }

    // Crear un evento LED para encender el LED correspondiente
    LEDEvent event_on;
    event_on.led_index = led_index;
    event_on.type = LED_EVENT_ON;

    // Crear un evento LED para apagar el LED después de 1 segundo
    LEDEvent event_off;
    event_off.led_index = led_index;
    event_off.type = LED_EVENT_OFF;

    // Enviar el evento LED para encender el LED correspondiente
    led_ao_send_event(led_ao, &event_on);

    // Esperar 1 segundo antes de enviar el evento para apagar el LED
    vTaskDelay(pdMS_TO_TICKS(1000));

    // Enviar el evento LED para apagar el LED correspondiente después de 1 segundo
    led_ao_send_event(led_ao, &event_off);
}

void ui_task(void *parameters) {
    UIActiveObject_t *const ao = (UIActiveObject_t *)parameters;
    state_button_t button_state;

    while (1) {
        // Esperar a que se reciba un evento del botón
        if (xQueueReceive(ao->button_ao->queue_button_h, &button_state, pdMS_TO_TICKS(100)) == pdPASS) {
            // Verificar si se necesita crear el objeto activo de LED
            if (ao->led_ao == NULL) {
                // Crear el objeto activo de LED de forma dinámica con pvPortMalloc
                ao->led_ao = (LEDActiveObject *)pvPortMalloc(sizeof(LEDActiveObject));
                if (ao->led_ao != NULL) {
                    led_initialize_ao(ao->led_ao, "LED_Task");
                } else {
                    LOGGER_LOG("Error: Failed to allocate memory for LEDActiveObject\r\n");
                }
            }

            // Procesar el evento del botón si hay un objeto activo de LED válido
            if (ao->led_ao != NULL) {
                process_button_event(button_state, ao->led_ao);
            } else {
                LOGGER_LOG("Error: LEDActiveObject not initialized\r\n");
            }
        } else {
            // Si no hay eventos en la cola de botón, destruir el objeto activo de LED si existe
            if (ao->led_ao != NULL) {
                led_destroy_ao(ao->led_ao);
                vPortFree(ao->led_ao); // Liberar la memoria asignada por FreeRTOS
                ao->led_ao = NULL;
                LOGGER_LOG(" --> 'LED_Task' destroyed due to lack of button events\n");
            }
        }
    }
}
