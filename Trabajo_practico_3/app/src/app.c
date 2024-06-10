/*
 * task_app.c
 *
 *  Created on: May 9, 2024
 *      Author: Grupo_3
 */

#include "main.h"
#include "cmsis_os.h"
#include "logger.h"
#include "dwt.h"
#include "board.h"
#include "app.h"
#include "task_button.h"
#include "task_user_interface.h"

/*Message*/
const char *p_sys = "RTOS2-TP2 <--> DEVELOPED: TATIANA, LAUTARO y ROYER.\r\n";

params_ao UI;

void app_init(void) {
	LOGGER_LOG(p_sys);

	UI_Init(&UI);

	cycle_counter_init();
}

