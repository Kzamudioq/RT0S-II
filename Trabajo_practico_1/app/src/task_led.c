/*
 * @file   : led.c
 * @date   : May 8, 2024
 * @author : grupo_3
 *
 * @brief  : Task functions for controlling the LEDs.
 *
 * This file contains task functions for controlling the red, blue, and green LEDs.
 * Each task listens to its corresponding queue for messages containing instructions
 * to turn on the LED for a specified duration. Upon receiving a message, the task
 * turns on the LED, waits for the specified duration, and then turns off the LED.
 */

/********************** Inclusions *******************************************/

#include "task_led.h"
#include "main.h"
#include "cmsis_os.h"
#include "logger.h"
#include "dwt.h"
#include "app.h"
#include "board.h"
#include "task_user_interface.h"

/********************** Task Functions ****************************************/

/**
 * @brief Task function for controlling the red LED.
 *
 * This task controls the red LED based on messages received
 * through the red LED queue.
 *
 * @param parameters Task parameters (unused).
 */
void task_led_red(void *parameters) {
    // Get the name of the task
    char *p_task_name_red = (char *)pcTaskGetName(NULL);
    LOGGER_LOG("  %s is running - \r\n", p_task_name_red);

    // Variable to store the received message
    message_led_t message_user_interface;

    // Variable to store the time tick
    TickType_t time_tick;

    // Main task loop
    while (true) {
        // Wait for a message from the red LED queue
        if (pdPASS == xQueueReceive(queue_led_red_h, &message_user_interface, portMAX_DELAY)) {
            LOGGER_LOG("  TURN ON: %s  <-->", p_task_name_red);

            // Record the time tick when the LED is turned on
            time_tick = xTaskGetTickCount();

            // Turn on the red LED
            HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, SET);

            // Delay for the specified duration
            HAL_Delay(message_user_interface.tick_time_led);

            // Turn off the red LED
            HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, RESET);

            // Calculate the duration the LED was on
            time_tick = xTaskGetTickCount() - time_tick;

            // Log the time the LED was on
            LOGGER_LOG("  TIME ON %lu ms\r\n", time_tick);
        }
    }
}

/**
 * @brief Task function for controlling the blue LED.
 *
 * This task controls the blue LED based on messages received
 * through the blue LED queue.
 *
 * @param parameters Task parameters (unused).
 */
void task_led_blue(void *parameters) {
    // Get the name of the task
    char *p_task_name_blue = (char *)pcTaskGetName(NULL);
    LOGGER_LOG("  %s is running - \r\n", p_task_name_blue);

    // Variable to store the received message
    message_led_t message_user_interface;

    // Variable to store the time tick
    TickType_t time_tick;

    // Main task loop
    while (true) {
        // Wait for a message from the blue LED queue
        if (pdPASS == xQueueReceive(queue_led_blue_h, &message_user_interface, portMAX_DELAY)) {
            LOGGER_LOG("  TURN ON: %s  <-->", p_task_name_blue);

            // Record the time tick when the LED is turned on
            time_tick = xTaskGetTickCount();

            // Turn on the blue LED
            HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, SET);

            // Delay for the specified duration
            HAL_Delay(message_user_interface.tick_time_led);

            // Turn off the blue LED
            HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, RESET);

            // Calculate the duration the LED was on
            time_tick = xTaskGetTickCount() - time_tick;

            // Log the time the LED was on
            LOGGER_LOG("  TIME ON %lu ms\r\n", time_tick);
        }
    }
}

/**
 * @brief Task function for controlling the green LED.
 *
 * This task controls the green LED based on messages received
 * through the green LED queue.
 *
 * @param parameters Task parameters (unused).
 */
void task_led_green(void *parameters) {
    // Get the name of the task
    char *p_task_name_green = (char *)pcTaskGetName(NULL);
    LOGGER_LOG("  %s is running - \r\n", p_task_name_green);

    // Variable to store the received message
    message_led_t message_user_interface;

    // Variable to store the time tick
    TickType_t time_tick;

    // Main task loop
    while (true) {
        // Wait for a message from the green LED queue
        if (pdPASS == xQueueReceive(queue_led_green_h, &message_user_interface, portMAX_DELAY)) {
            LOGGER_LOG("  TURN ON: %s  <-->", p_task_name_green);

            // Record the time tick when the LED is turned on
            time_tick = xTaskGetTickCount();

            // Turn on the green LED
            HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, SET);

            // Delay for the specified duration
            HAL_Delay(message_user_interface.tick_time_led);

            // Turn off the green LED
            HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, RESET);

            // Calculate the duration the LED was on
            time_tick = xTaskGetTickCount() - time_tick;

            // Log the time the LED was on
            LOGGER_LOG("  TIME ON %lu ms\r\n", time_tick);
        }
    }
}
