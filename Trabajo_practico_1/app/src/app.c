/*
 * @file   : task_app.c
 * @date   : May 9, 2024
 * @author : grupo_3
 * @version: v1.0.0
 *
 * @brief  : Application initialization and task creation
 *
 * This file initializes the application by creating tasks and queues,
 * and initializing necessary peripherals. It includes the necessary headers
 * and defines task and queue handles for the LED tasks, button task, and user interface task.
 * Additionally, it defines the application initialization function, `app_init()`.
 */

/********************** Inclusions *******************************************/

#include "task_led.h"
#include "main.h"
#include "cmsis_os.h"
#include "logger.h"
#include "dwt.h"
#include "board.h"
#include "app.h"
#include "task_button.h"
#include "task_user_interface.h"

/********************** Task and Queue Handles ********************************/

/* Task Handle */
xTaskHandle task_led_red_h;
xTaskHandle task_led_green_h;
xTaskHandle task_led_blue_h;
xTaskHandle task_button_h;
xTaskHandle task_user_interface_h;

/* Queue Handle */
xQueueHandle queue_pulse_h;
xQueueHandle queue_led_red_h;
xQueueHandle queue_led_blue_h;
xQueueHandle queue_led_green_h;

/* Message */
const char *p_sys = " RTOS - Event-Triggered Systems (ETS)\r\n";

/********************** Function Definitions *********************************/

/**
 * @brief Initializes the application.
 *
 * This function initializes the application, creating tasks and queues,
 * and initializing necessary peripherals.
 */
void app_init(void) {
    LOGGER_LOG(p_sys);

    /* Create queue for pulse */
    queue_pulse_h = xQueueCreate(LENGTH_QUEUE_PULSE, SIZE_QUEUE_PULSE);
    configASSERT(queue_pulse_h != NULL);

    /* Create queue for red LED */
    queue_led_red_h = xQueueCreate(LENGTH_QUEUE_LED, SIZE_QUEUE_LED);
    configASSERT(queue_led_red_h != NULL);

    /* Create queue for blue LED */
    queue_led_blue_h = xQueueCreate(LENGTH_QUEUE_LED, SIZE_QUEUE_LED);
    configASSERT(queue_led_blue_h != NULL);

    /* Create queue for green LED */
    queue_led_green_h = xQueueCreate(LENGTH_QUEUE_LED, SIZE_QUEUE_LED);
    configASSERT(queue_led_green_h != NULL);

    /* Create Task for red LED */
    BaseType_t ret = xTaskCreate(task_led_red,
                                  "Task led red",
                                  (2 * configMINIMAL_STACK_SIZE),
                                  NULL,
                                  (tskIDLE_PRIORITY + 1UL),
                                  &task_led_red_h);
    configASSERT(ret == pdPASS);

    /* Create Task for blue LED */
    ret = xTaskCreate(task_led_blue,
                      "Task led blue",
                      (2 * configMINIMAL_STACK_SIZE),
                      NULL,
                      (tskIDLE_PRIORITY + 1UL),
                      &task_led_blue_h);
    configASSERT(ret == pdPASS);

    /* Create Task for green LED */
    ret = xTaskCreate(task_led_green,
                      "Task led green",
                      (2 * configMINIMAL_STACK_SIZE),
                      NULL,
                      (tskIDLE_PRIORITY + 1UL),
                      &task_led_green_h);
    configASSERT(ret == pdPASS);

    /* Create Task for button */
    ret = xTaskCreate(task_button,
                      "Task button",
                      (2 * configMINIMAL_STACK_SIZE),
                      NULL,
                      (tskIDLE_PRIORITY + 1UL),
                      &task_button_h);
    configASSERT(ret == pdPASS);

    /* Create Task for user interface */
    ret = xTaskCreate(task_user_interface,
                      "Task user interface",
                      (2 * configMINIMAL_STACK_SIZE),
                      NULL,
                      (tskIDLE_PRIORITY + 1UL),
                      &task_user_interface_h);
    configASSERT(ret == pdPASS);

    /* Initialize cycle counter */
    cycle_counter_init();

    LOGGER_LOG(" <--> Tasks App Init running \r\n");
}
