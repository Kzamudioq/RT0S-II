/*
 * oa_led.h
 *
 * Created on: May 8, 2024
 * Author: Grupo_3
 */

#ifndef INC_OA_LED_H_
#define INC_OA_LED_H_

#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "board.h"

// LED Configuration
typedef enum {
    RED,
    GREEN,
    BLUE,
} LEDColor;

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
    LEDColor color;
} LedConfig_t;

extern const LedConfig_t led_configs[];

// LED Active Object
typedef struct {
    QueueHandle_t queue;
    TaskHandle_t task;
} LEDActiveObject;

typedef enum {
    LED_EVENT_ON,
    LED_EVENT_OFF,
    LED_EVENT_TOGGLE,
} LEDEventType;

typedef enum {
    LED_OFF = 0,
    LED_ON = 1,
} LEDStatus;

typedef struct {
    uint8_t led_index;  // Reference to index in led_configs
    LEDEventType type;
} LEDEvent;

// LED Control Functions
void led_toggle(uint8_t led_index);
void led_write(uint8_t led_index, const LEDStatus status);
void led_set(uint8_t led_index);
void led_clear(uint8_t led_index);

// LED Active Object Functions
void led_initialize_ao(LEDActiveObject* ao, const char* ao_task_name);
void led_destroy_ao(LEDActiveObject* ao);
void led_ao_send_event(LEDActiveObject* ao, const LEDEvent* event);

#endif /* INC_OA_LED_H_ */
