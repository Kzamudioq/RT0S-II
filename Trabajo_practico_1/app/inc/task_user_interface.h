/*
 * @file   : task_user_interface.h
 * @date   : May 9, 2024
 * @author : grupo_3
 *
 * @brief  : Header file for the user interface task
 *
 * This file declares macros, enumerations, and structures used by the user interface task.
 * It defines the time intervals for different button press durations and LED on times,
 * as well as enumerations for button states and LED turn-on statuses.
 * Additionally, it declares the function prototype for the user interface task.
 */

#ifndef TASK_USER_INTERFACE_H_
#define TASK_USER_INTERFACE_H_

/********************** Macro Definitions ************************************/

#define TIME_PULSE_LOW          200     // Time interval for a low pulse (ms)
#define TIME_PULSE_MODERATE     1000    // Time interval for a moderate pulse (ms)
#define TIME_PULSE_LONG         2000    // Time interval for a long pulse (ms)
#define TIME_TURN_ON_LED_RED    1000    // Time interval for turning on the red LED (ms)
#define TIME_TURN_ON_LED_BLUE   2000    // Time interval for turning on the blue LED (ms)
#define TIME_TURN_ON_LED_GREEN  3000    // Time interval for turning on the green LED (ms)

/********************** Type Definitions ************************************/

/**
 * @brief Enumeration of button states
 */
typedef enum state_button
{
    PULSE_OUT,      // Button is not pressed or in a state other than specified
    PULSE_PULSE,    // Button is pressed for a short duration
    PULSE_SHORT,    // Button is pressed for a moderate duration
    PULSE_LONG,     // Button is pressed for a long duration
    PULSE_ERROR,    // Button press duration is unrecognized or erroneous
} state_button_t;

/**
 * @brief Enumeration of LED turn-on statuses
 */
typedef enum turn_on
{
    TURN_ON,        // LED should be turned on
    TURN_ERROR,     // Error occurred while turning on LED
    TURN_OUT        // LED should be turned off
} turn_on_t;

/**
 * @brief Structure representing a message for controlling an LED
 */
typedef struct message_led
{
    turn_on_t turn_on_led;  // LED turn-on status
    uint32_t tick_time_led; // Time interval for LED turn-on (ms)
} message_led_t;

/********************** Function Declarations *******************************/

/**
 * @brief Task function for controlling the user interface.
 *
 * This function is responsible for monitoring button presses and
 * controlling the LEDs accordingly.
 *
 * @param parameter Task parameters (unused).
 */
void task_user_interface(void *parameter);

#endif /* TASK_USER_INTERFACE_H_ */
