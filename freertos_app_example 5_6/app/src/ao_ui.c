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

void user_interface_initialize_ao(void *parameters, void *BAO, void *LAO) {
    InterfaceUserActiveObject_t *const AO = (InterfaceUserActiveObject_t*) parameters;
    message_user_interface_t *const message_user_interface = (message_user_interface_t*) pvPortMalloc(sizeof(message_user_interface_t));
    if (message_user_interface == NULL) {
        return;
    }

    message_user_interface->BAO_MS_UI = (ButtonActiveObject_t*) BAO;
    message_user_interface->LAO_MS_UI = (LedActiveObject_t*) LAO;

    BaseType_t ret = xTaskCreate(task_user_interface, "Task user interface", 2 * configMINIMAL_STACK_SIZE, (void*) message_user_interface, tskIDLE_PRIORITY + 1UL, AO->task_user_interface_h);
    configASSERT(ret == pdPASS);
}

void task_user_interface(void *parameters) {
    message_user_interface_t *message = (message_user_interface_t*) parameters;
    ButtonActiveObject_t *button = (ButtonActiveObject_t*) message->BAO_MS_UI;
    LedActiveObject_t *led = (LedActiveObject_t*) message->LAO_MS_UI;
    TickType_t event;

    state_button_t pulse = PULSE_OUT;

    while (true) {
        if (xQueueReceive(button->queue_button_h, &event, 0) == pdPASS) {
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

            switch (pulse) {
            case PULSE_PULSE:
                if (xQueueSend(led->queue_led_h, &pulse, 0) != pdPASS) {
                }
                LOGGER_LOG(" Pulse sent: PULSE_PULSE\r\n");
                break;

            case PULSE_LONG:
                if (xQueueSend(led->queue_led_h, &pulse, 0) != pdPASS) {
                }
                LOGGER_LOG("  Pulse sent: PULSE_LONG\r\n");
                break;

            case PULSE_SHORT:
                if (xQueueSend(led->queue_led_h, &pulse, 0) != pdPASS) {
                }
                LOGGER_LOG(" Pulse sent: PULSE_SHORT\r\n");
                break;

            default:
                LOGGER_LOG("Invalid pulse\r\n");
                break;
            }
        }
    }
}
