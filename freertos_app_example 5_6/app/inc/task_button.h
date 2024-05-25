/*
 * task_button.h
 *
 *  Created on: May 9, 2024
 *      Author: Grupo_3
 */
#ifndef INC_TASK_BUTTON_H_
#define INC_TASK_BUTTON_H_

#include "cmsis_os.h"
#include "stm32f4xx_hal.h"

// Structure to hold button configuration
typedef struct {
    GPIO_TypeDef *port;    // Pointer to the GPIO port of the button
    uint16_t pin;          // Pin number of the button
} ButtonConfig_t;

// Structure for the button active object
typedef struct {
    QueueHandle_t queue_button_h;  // Handle for the button queue
    TaskHandle_t *task_button_h;   // Handle for the button task
    ButtonConfig_t button_config;  // Configuration for the button
} ButtonActiveObject_t;

// Enumeration for button states
typedef enum  {
    PULSE_OUT = 0,    // Not pressed or non-qualifying press
    PULSE_PULSE,      // Pressed between 200 ms and 1000 ms
    PULSE_SHORT,      // Pressed between 1000 ms and 2000 ms
    PULSE_LONG,       // Pressed more than 2000 ms
    PULSE_ERROR       // Error state or undefined behavior
} state_button_t;

// Function prototypes
void button_initialize_ao(ButtonActiveObject_t *parameters,
                          ButtonConfig_t button_config,
                          const char *ao_task_name);

#endif /* INC_TASK_BUTTON_H_ */
