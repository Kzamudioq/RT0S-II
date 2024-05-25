/*
 * oa_led.c
 *
 * Created on: May 8, 2024
 * Author: Grupo_3
 */

#include "cmsis_os.h"
#include "logger.h"
#include "board.h"
#include "dwt.h"
#include "oa_led.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define LED_AO_QUEUE_LENGTH 15
#define NUM_LEDS (sizeof(led_configs) / sizeof(led_configs[0]))

// LED Configuration Array
const LedConfig_t led_configs[] = {
    { .port = LED_R_GPIO_Port, .pin = LED_R_Pin, .color = RED },
    { .port = LED_G_GPIO_Port, .pin = LED_G_Pin, .color = GREEN },
    { .port = LED_B_GPIO_Port, .pin = LED_B_Pin, .color = BLUE },
};

// Private Function Prototypes
static void led_task(void* parameters);
static void process_led_event(const LEDEvent* event);

// LED Control Functions
void led_toggle(uint8_t led_index) {
    assert(led_index < NUM_LEDS);  // Check that led_index is within range
    HAL_GPIO_TogglePin(led_configs[led_index].port, led_configs[led_index].pin);
}

void led_write(uint8_t led_index, const LEDStatus status) {
    if (led_index >= NUM_LEDS) {
        LOGGER_LOG("Error: Invalid LED index\r\n");
        return;
    }

    assert(status == LED_ON || status == LED_OFF);
    GPIO_PinState state = (status == LED_ON) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(led_configs[led_index].port, led_configs[led_index].pin, state);
}

void led_set(uint8_t led_index) {
    led_write(led_index, LED_ON);
}

void led_clear(uint8_t led_index) {
    led_write(led_index, LED_OFF);
}

// LED Active Object Functions
void led_initialize_ao(LEDActiveObject* ao, const char* ao_task_name) {
    BaseType_t ret;
    ret = xTaskCreate(led_task, ao_task_name, (2 * configMINIMAL_STACK_SIZE), (void*) ao, (tskIDLE_PRIORITY + 1UL), &ao->task);
    configASSERT(ret == pdPASS);
    ao->queue = xQueueCreate(LED_AO_QUEUE_LENGTH, sizeof(LEDEvent));
    configASSERT(ao->queue);
}

void led_destroy_ao(LEDActiveObject* ao) {
    if (ao->task != NULL) {
        vTaskDelete(ao->task);
        ao->task = NULL;
    }
    if (ao->queue != NULL) {
        vQueueDelete(ao->queue);
        ao->queue = NULL;
    }
}

void led_ao_send_event(LEDActiveObject* ao, const LEDEvent* event) {
    if (ao == NULL || event == NULL) {
        LOGGER_LOG("Error: Se detectó un puntero NULL en led_ao_send_event\n");
        return;
    }

    if (xQueueSend(ao->queue, event, portMAX_DELAY) != pdPASS) {
        LOGGER_LOG("Error al enviar el evento LED\n");
    }
}

// Private Functions
static void led_task(void* parameters) {
    LEDActiveObject* const AO = (LEDActiveObject*) parameters;
    LEDEvent event;
    LOGGER_LOG("  --> '%s' created for LED control\n", pcTaskGetName(NULL));

    while (1) {
        if (xQueueReceive(AO->queue, &event, portMAX_DELAY) == pdPASS) {
            process_led_event(&event);
        }
    }
}

static void process_led_event(const LEDEvent* event) {
    LOGGER_LOG("[%s] Event Received: ", pcTaskGetName(NULL));
    if (event == NULL) {
        LOGGER_LOG("Error: Received NULL event\r\n");
        return;
    }

    if (event->led_index >= NUM_LEDS) {
        LOGGER_LOG("Error: Invalid LED index\r\n");
        return;
    }

    switch (event->type) {
    case LED_EVENT_ON:
        LOGGER_LOG("LED_EVENT_ON\r\n");
        led_set(event->led_index);
        break;
    case LED_EVENT_OFF:
        LOGGER_LOG("LED_EVENT_OFF\r\n");
        led_clear(event->led_index);
        break;
    case LED_EVENT_TOGGLE:
        LOGGER_LOG("LED_EVENT_TOGGLE\r\n");
        led_toggle(event->led_index);
        break;
    default:
        LOGGER_LOG("Invalid LED event type\r\n");
        configASSERT(pdFAIL && "Invalid LED event");
        break;
    }
}
