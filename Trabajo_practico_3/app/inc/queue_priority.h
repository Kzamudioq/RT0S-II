/*
 * queue_priority.h
 *
 *  Created on: Jun 7, 2024
 *      Author: Grupo_3
 */

#ifndef INC_QUEUE_PRIORITY_H_
#define INC_QUEUE_PRIORITY_H_

#include "cmsis_os.h"            // Library for CMSIS-RTOS real-time operating system

#include "logger.h"              // Logger library for logging purposes
#include <stdlib.h>              // Standard library for general-purpose functions
#include <stdint.h>              // Standard library for integer types

/* Global structs -----------------------------------------------------------------------*/
// Structure for a priority queue element
typedef struct {
	uint8_t priority;  // Priority of the element
	void *data;        // Data of the element
} priority_queue_item_t;

// Structure for the priority queue
typedef struct {
	priority_queue_item_t *array;  // Array of queue elements
	uint32_t capacity;             // Maximum capacity of the queue
	uint32_t size;                 // Current size of the queue
} priority_queue_t;
/* End global structs -------------------------------------------------------------------*/

/* Global functions ---------------------------------------------------------------------*/

priority_queue_t* priority_queue_create(uint32_t capacity);

void priority_queue_destroy(priority_queue_t *queue);
int priority_queue_push(priority_queue_t *queue, void *data, uint8_t priority);
void* priority_queue_pop(priority_queue_t *queue);
int priority_queue_is_empty(priority_queue_t *queue);
/* End global functions -----------------------------------------------------------------*/

#endif /* INC_QUEUE_PRIORITY_H_ */
