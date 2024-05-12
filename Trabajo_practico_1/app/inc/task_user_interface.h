/*
 * task_user_interface.h
 *
 *  Created on: May 9, 2024
 *      Author: royer.sanabria
 */
#include "cmsis_os.h"
#include <stdint.h>


#ifndef TASK_USER_INTERFACE_H_
#define TASK_USER_INTERFACE_H_

typedef struct InterfaceUserObject
{
	TaskHandle_t  *task_user_interface_h;
	}InterfaceUserActiveObject_t;

	void user_interface_initialize_ao(void* parameters, void*  BAO, void*  LAOR, void*  LAOG, void*  LAOB);
#endif /* TASK_USER_INTERFACE_H_ */
