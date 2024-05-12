/*
 * @file   : app.h
 * @date   : May 8, 2024
 * @author : grupo_3
 * @version: v1.0.0
 *
 * @brief  : Header file for the application
 *
 * This file contains declarations for initializing the application and
 * defines constants related to task queues and handles.
 */

#ifndef APP_INC_APP_H_
#define APP_INC_APP_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Define queue parameters */
#define LENGTH_QUEUE_PULSE 5          /**< Maximum length of the pulse queue */
#define SIZE_QUEUE_PULSE (sizeof(TickType_t)) /**< Size of each item in the pulse queue */
#define LENGTH_QUEUE_LED 5            /**< Maximum length of the LED queue */
#define SIZE_QUEUE_LED (sizeof(message_led_t)) /**< Size of each item in the LED queue */

/* Extern Task Handles */
extern xTaskHandle task_led_red_h;       /**< Handle for the red LED task */
extern xTaskHandle task_led_green_h;     /**< Handle for the green LED task */
extern xTaskHandle task_led_blue_h;      /**< Handle for the blue LED task */
extern xTaskHandle task_button_h;        /**< Handle for the button task */
extern xTaskHandle task_user_interface_h;/**< Handle for the user interface task */

/* Extern Queues */
extern xQueueHandle queue_pulse_h;       /**< Queue for pulse messages */
extern xQueueHandle queue_led_red_h;     /**< Queue for red LED messages */
extern xQueueHandle queue_led_green_h;   /**< Queue for green LED messages */
extern xQueueHandle queue_led_blue_h;    /**< Queue for blue LED messages */

/* Function prototypes */
void app_init(void); /**< Initialize the application */

#ifdef __cplusplus
}
#endif

#endif /* APP_INC_APP_H_ */

