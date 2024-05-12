/*
 * task_button.h
 *
 *  Created on: May 9, 2024
 *      Author: royer.sanabria
 */

//#pragma once
#include "cmsis_os.h"


#ifndef INC_TASK_BUTTON_H_
#define INC_TASK_BUTTON_H_

typedef struct ButtonActiveObject
{
    QueueHandle_t queue_button_h;
    TaskHandle_t *task_button_h;
} ButtonActiveObject_t;

extern ButtonActiveObject_t ButtonActiveObject;

void button_initialize_ao(ButtonActiveObject_t *parameters);


#endif /* INC_TASK_BUTTON_H_ */
