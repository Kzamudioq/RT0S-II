/*
 * @file   : task_button.h
 * @date   : May 9, 2024
 * @author : grupo_3
 *
 * @brief  : Header file for the button task
 *
 * This file declares macros and functions related to the button task.
 * It defines the task period in milliseconds and the value to indicate a button press.
 */

#ifndef INC_TASK_BUTTON_H_
#define INC_TASK_BUTTON_H_

/********************** Macro Definitions ************************************/

#define TASK_PERIOD_MS_    (1000)        // Task period in milliseconds
#define BUTTON_PRESSED      GPIO_PIN_RESET   // Value to indicate a button press

/********************** Function Declarations *******************************/

/**
 * @brief Task function for handling button events.
 *
 * This function is responsible for handling button events and performing
 * appropriate actions based on the button state.
 *
 * @param parametros Task parameters (unused).
 */
void task_button(void *parametros);

#endif /* INC_TASK_BUTTON_H_ */
