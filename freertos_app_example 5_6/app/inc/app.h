/*
 * app.h
 *
 *  Created on: May 9, 2024
 *      Author: Grupo_3
 */

#ifndef APP_INC_APP_H_
#define APP_INC_APP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cmsis_os.h"
#include "stm32f4xx_hal.h"

#include "dwt.h"
#include "board.h"
#include "logger.h"
#include "oa_led.h"
#include "ao_ui.h"
#include "task_button.h"

// Function to initialize the application
void app_init(void);

#ifdef __cplusplus
}
#endif

#endif /* APP_INC_APP_H_ */
