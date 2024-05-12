/*
 * @file   : task_user_interface.c
 * @date   : May 9, 2024
 * @author : grupo_3
 *
 * @brief  : Task function for controlling the user interface.
 *
 * This file contains the task function for managing the user interface,
 * including monitoring button presses and controlling the LEDs based on
 * the duration of button presses.
 */

/********************** Inclusions *******************************************/

#include "main.h"
#include "cmsis_os.h"
#include <stdbool.h>
#include "app.h"
#include "logger.h"
#include "board.h"
#include "dwt.h"
#include "task_user_interface.h"

/********************** Task Functions ****************************************/

/**
 * @brief Task function for controlling the user interface.
 *
 * This task handles the user interface, including button presses
 * and controlling the LED based on the duration of button presses.
 *
 * @param parameter Task parameters (unused).
 */
void task_user_interface(void *parameter)
{
    // Variables to store the state of the button and the button press duration
    const char *p_state_button;
    TickType_t time_tick;
    state_button_t state_button;
    message_led_t messaje_led;

    // Main task loop
    while (true)
    {
        // Wait for a message from the button queue
        if (pdPASS == xQueueReceive(queue_pulse_h, &time_tick, portMAX_DELAY))
        {
            // Determine the state of the button based on the press duration
            if (time_tick < TIME_PULSE_LOW)
            {
                state_button = PULSE_OUT;
                p_state_button = "PULSE OUT";
            }
            else if (time_tick < TIME_PULSE_MODERATE)
            {
                state_button = PULSE_PULSE;
                p_state_button = "PULSE PULSE";
            }
            else if (time_tick < TIME_PULSE_LONG)
            {
                state_button = PULSE_SHORT;
                p_state_button = "PULSE SHORT";
            }
            else if (time_tick > TIME_PULSE_LONG)
            {
                state_button = PULSE_LONG;
                p_state_button = "PULSE LONG";
            }
            else
            {
                state_button = PULSE_ERROR;
                p_state_button = "PULSE ERROR";
            }

            // Log the button press duration and state
            LOGGER_LOG("  --> Time button pressed %lu ms  <-->", time_tick);
            LOGGER_LOG(" State Button: %s <-->", p_state_button);

            // Take action based on the button state
            switch (state_button)
            {
            case PULSE_OUT:
                LOGGER_LOG("  LED's TURN OFF\r\n");
                break;

            case PULSE_PULSE:
                messaje_led.turn_on_led = TURN_ON;
                messaje_led.tick_time_led = TIME_TURN_ON_LED_RED;
                xQueueSend(queue_led_red_h, &messaje_led, 0);
                break;

            case PULSE_SHORT:
                messaje_led.turn_on_led = TURN_ON;
                messaje_led.tick_time_led = TIME_TURN_ON_LED_GREEN;
                xQueueSend(queue_led_green_h, &messaje_led, 0);
                break;

            case PULSE_LONG:
                messaje_led.turn_on_led = TURN_ON;
                messaje_led.tick_time_led = TIME_TURN_ON_LED_BLUE;
                xQueueSend(queue_led_blue_h, &messaje_led, 0);
                break;

            default:
                LOGGER_LOG("ERROR PULSE\r\n");
                // Handle error case
                break;
            }
        }
    }
}
