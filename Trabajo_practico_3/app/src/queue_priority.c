/*
 * queue_priority.c
 *
 *  Created on: Jun 9, 2024
 *      Author: Grupo_3
 */
/* Inclusions ---------------------------------------------------------------------------*/
#include "queue_priority.h"

/* Local macros -------------------------------------------------------------------------*/
/* End local macros ---------------------------------------------------------------------*/

/* Local structs ------------------------------------------------------------------------*/
/* End local structs --------------------------------------------------------------------*/

/* Global functions ---------------------------------------------------------------------*/
/**
 * @brief: Creates a priority queue with a given capacity.
 * @parameters:
 * - capacity: The maximum number of items the queue can hold.
 * @retval: Pointer to the created priority queue, or NULL if creation failed.
 * @note: Allocates memory for the queue and initializes its fields.
 */
priority_queue_t* priority_queue_create(uint32_t capacity) {
	priority_queue_t *queue = (priority_queue_t*) pvPortMalloc(
			sizeof(priority_queue_t));
	if (queue != NULL) {
		queue->array = (priority_queue_item_t*) pvPortMalloc(
				capacity * sizeof(priority_queue_item_t));
		if (queue->array != NULL) {
			queue->capacity = capacity;
			queue->size = 0;
			return queue;
		} else {
			vPortFree(queue);
		}
	}
	return NULL;
}

/**
 * @brief: Destroys a priority queue and frees its resources.
 * @parameters:
 * - queue: Pointer to the priority queue to be destroyed.
 * @retval: None
 * @note: Frees the memory allocated for the queue and its array.
 */
void priority_queue_destroy(priority_queue_t *queue) {
	if (queue != NULL) {
		free(queue->array);
		free(queue);
	}
}

/**
 * @brief: Pushes an element with a given priority into the priority queue.
 * @parameters:
 * - queue: Pointer to the priority queue.
 * - data: Pointer to the data to be added to the queue.
 * - priority: The priority of the data.
 * @retval: 0 on success, -1 if the queue is full.
 * @note: Adds the element to the queue and maintains the priority order.
 */
int priority_queue_push(priority_queue_t *queue, void *data, uint8_t priority) {
	if (queue == NULL || queue->size >= queue->capacity) {
		return -1; // Error: queue is full or not initialized
	}
	int i = queue->size - 1;
	// Find the correct position to insert the new element based on priority
	while (i >= 0 && queue->array[i].priority < priority) {
		queue->array[i + 1] = queue->array[i];
		i--;
	}
	queue->array[i + 1].data = data;
	queue->array[i + 1].priority = priority;
	queue->size++;
	LOGGER_LOG(" <<< QUEUE PUSH: priority %d, size %lu >>>\r\n", priority,
			queue->size);
	return 0; // Success
}

/**
 * @brief: Pops the highest priority element from the priority queue.
 * @parameters:
 * - queue: Pointer to the priority queue.
 * @retval: Pointer to the data of the highest priority element, or NULL if the queue is empty.
 * @note: Removes the highest priority element from the queue and reorders the remaining elements.
 */
void* priority_queue_pop(priority_queue_t *queue) {
	if (queue == NULL || queue->size == 0) {
		return NULL; // Error: queue is empty or not initialized
	}
	void *data = queue->array[0].data;
	for (uint32_t i = 1; i < queue->size; i++) {
		queue->array[i - 1] = queue->array[i];
	}
	queue->size--;
	return data;
}

/**
 * @brief: Checks if the priority queue is empty.
 * @parameters:
 * - queue: Pointer to the priority queue.
 * @retval: 1 if the queue is empty, 0 otherwise.
 * @note: Simply compares the queue size to 0.
 */
int priority_queue_is_empty(priority_queue_t *queue) {
	return (queue == NULL || queue->size == 0);
}

/* End global functions -----------------------------------------------------------------*/
