/*
 * @file   : task_button.c
 * @date   : May 9, 2024
 * @author : grupo_3
 *
 * @brief  : Task that monitors the state of the button and sends messages to a queue when a press is detected.
 *
 * This file implements a task responsible for monitoring the state of a button. When a button press is detected,
 * it measures the duration of the press and sends the duration (in ticks) to a queue for further processing.
 * The task runs continuously, polling the button state periodically.
 */

/********************** Inclusions *******************************************/

#include "main.h"
#include "task_button.h"
#include <stdbool.h>
#include "cmsis_os.h"
#include "logger.h"
#include "dwt.h"
#include "board.h"
#include "app.h"

/********************** Function Definitions *********************************/

/**
 * @brief Task function for monitoring button state.
 *
 * This function continuously monitors the state of the button. When a button press is detected,
 * it measures the duration of the press and sends the duration (in ticks) to a queue for further processing.
 *
 * @param parametros Pointer to task parameters (unused).
 */
void task_button(void *parametros)
{
    // Get the name of the task
    char *p_task_name = (char *)pcTaskGetName(NULL);
    LOGGER_LOG("Task: %s\r\n", p_task_name);

    // Variable to store the time tick when button is pressed
    TickType_t time_tick;

    // Main task loop
    while(true)
    {
        // Check if the button is pressed
        if (BUTTON_PRESSED == HAL_GPIO_ReadPin(PORT_BUTTON, PIN_BUTTON))
        {
            // Record the time tick when button is pressed
            time_tick = xTaskGetTickCount();

            // Wait for the button to be released
            while (BUTTON_PRESSED == HAL_GPIO_ReadPin(PORT_BUTTON, PIN_BUTTON))
            {
            }

            // Calculate the duration of the button press
            time_tick = xTaskGetTickCount() - time_tick;

            // Send the duration to the queue for further processing
            xQueueSend(queue_pulse_h, &time_tick, 0);
        }
    }
}
