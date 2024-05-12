/*
 * @file   : led.h
 * @date   : May 8, 2024
 * @author : grupo_3
 *
 * @brief  : Header file for LED tasks
 *
 * This file declares macros and functions related to controlling LEDs.
 * It defines macros for setting LEDs on and off, as well as function prototypes
 * for the tasks responsible for controlling each LED.
 */

#ifndef TASK_LED_H_
#define TASK_LED_H_

/********************** Header Files ****************************************/

#include "main.h"

/********************** Macro Definitions ************************************/

#define LED_ON      GPIO_PIN_SET       // Macro to set LED on
#define LED_OFF     GPIO_PIN_RESET     // Macro to set LED off

/********************** Function Declarations *******************************/

/**
 * @brief Task function for controlling the red LED.
 *
 * This function is responsible for controlling the red LED based on messages received.
 *
 * @param parameters Task parameters (unused).
 */
void task_led_red(void *parameters);

/**
 * @brief Task function for controlling the green LED.
 *
 * This function is responsible for controlling the green LED based on messages received.
 *
 * @param parameters Task parameters (unused).
 */
void task_led_green(void *parameters);

/**
 * @brief Task function for controlling the blue LED.
 *
 * This function is responsible for controlling the blue LED based on messages received.
 *
 * @param parameters Task parameters (unused).
 */
void task_led_blue(void *parameters);

#endif /* TASK_LED_H_ */
