/*
 * task_app.c
 *
 *  Created on: May 9, 2024
 *      Author: royer.sanabria
 */

#include "task_led.h"
#include "main.h"
#include "cmsis_os.h"
#include "logger.h"
#include "dwt.h"
#include "board.h"
#include "app.h"
#include "task_button.h"
#include "task_user_interface.h"

#define a 1000


/*Message*/
const char *p_sys	= " --> RTOS2-TP1 <--> Developed by: Tatiana, Lautaro y Royer.\r\n";

ButtonActiveObject_t ao_button;
LedActiveObject_t    ao_led_red;
LedActiveObject_t    ao_led_blue;
LedActiveObject_t    ao_led_green;
InterfaceUserActiveObject_t ao_user_interface;

void app_init(void)
{
	LOGGER_LOG(p_sys);


	button_initialize_ao(&ao_button);
	led_initialize_ao(&ao_led_red, "TASK LED RED",RED);
	led_initialize_ao(&ao_led_green, "TASK LED GREEN",GREEN);
	led_initialize_ao(&ao_led_blue, "TASK LED BLUE",BLUE);

	user_interface_initialize_ao(&ao_user_interface, &ao_button, &ao_led_red, &ao_led_green, &ao_led_blue);

    cycle_counter_init();
}

