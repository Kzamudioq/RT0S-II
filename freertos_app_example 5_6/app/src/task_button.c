/*
 * task_button.c
 *
 *  Created on: May 9, 2024
 *      Author: Grupo_3
 */
#include "cmsis_os.h"

#include "logger.h"
#include "dwt.h"
#include "board.h"
#include "task_button.h"


#include <stdbool.h>

// Define queue length and size for button events
#define LENGTH_QUEUE_PULSE 5
#define SIZE_QUEUE_PULSE sizeof(state_button_t)
#define BUTTON_PRESSED GPIO_PIN_RESET
#define DEBOUNCE_DELAY_MS 50

// Task function for button handling
void task_button(void *parameters);

/**
 * @brief Initializes the button active object.
 *
 * @param parameters Pointer to the button active object.
 * @param button_config Configuration for the button.
 * @param ao_task_name Name of the task for logging purposes.
 */
void button_initialize_ao(ButtonActiveObject_t *parameters,
        ButtonConfig_t button_config, const char *ao_task_name) {
    BaseType_t ret;
    ButtonActiveObject_t *const ao = (ButtonActiveObject_t*) parameters;

    // Create button task
    ret = xTaskCreate(task_button, "Task button", 2 * configMINIMAL_STACK_SIZE,
            (void*) ao, tskIDLE_PRIORITY + 1UL, ao->task_button_h);
    configASSERT(ret == pdPASS);

    // Create queue for button events
    ao->queue_button_h = xQueueCreate(LENGTH_QUEUE_PULSE, SIZE_QUEUE_PULSE);
    configASSERT(ao->queue_button_h);

    // Assign button configuration
    ao->button_config = button_config;

    // Log task creation
    LOGGER_LOG(" --> '%s' created for BUTTON control\r\n", ao_task_name);
}

/**
 * @brief Task for handling button events.
 *
 * @param parameters Pointer to the button active object.
 */
void task_button(void *parameters) {
    ButtonActiveObject_t *const ao = (ButtonActiveObject_t*) parameters;
    ButtonConfig_t *config = &(ao->button_config);
    TickType_t time_pressed;
    state_button_t button_state;

    while (true) {
        // Check if button is pressed
        if (HAL_GPIO_ReadPin(config->port, config->pin) == BUTTON_PRESSED) {
            time_pressed = xTaskGetTickCount();
            // Wait until button is released
            while (HAL_GPIO_ReadPin(config->port, config->pin) == BUTTON_PRESSED) {
                vTaskDelay(pdMS_TO_TICKS(DEBOUNCE_DELAY_MS));
            }
            // Calculate time button was held down
            time_pressed = xTaskGetTickCount() - time_pressed;

            // Determine the state of button press
            if (time_pressed >= 2000) {
                button_state = PULSE_LONG;
            } else if (time_pressed >= 1000) {
                button_state = PULSE_SHORT;
            } else if (time_pressed >= 200) {
                button_state = PULSE_PULSE;
            } else {
                button_state = PULSE_ERROR; // Non-qualifying press
            }

            // Send button state to the queue
            if (xQueueSend(ao->queue_button_h, &button_state, 0) != pdPASS) {
                LOGGER_LOG("\r\n --> Failed to send button event to queue\r\n");
            } else {
                LOGGER_LOG("\r\n --> Button event sent: %d\r\n", button_state);
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10)); // Small delay to avoid rapid polling
    }
}
