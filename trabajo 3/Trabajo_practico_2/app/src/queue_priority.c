/*
 * queue_priority.c
 *
 *  Created on: Jun 9, 2024
 *      Author: Grupo_3
 */

#include "queue_priority.h"

// Crear una nueva cola de prioridad
priority_queue_t* priority_queue_create(uint32_t capacity) {
    priority_queue_t *queue = (priority_queue_t *)malloc(sizeof(priority_queue_t));
    if (queue != NULL) {
        queue->array = (priority_queue_item_t *)malloc(capacity * sizeof(priority_queue_item_t));
        if (queue->array != NULL) {
            queue->capacity = capacity;
            queue->size = 0;
            return queue;
        } else {
            free(queue);
        }
    }
    return NULL;
}

// Destruir una cola de prioridad
void priority_queue_destroy(priority_queue_t *queue) {
    if (queue != NULL) {
        free(queue->array);
        free(queue);
    }
}

// Insertar un elemento en la cola de prioridad
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
    LOGGER_LOG(" <<< QUEUE PUSH: priority %d, size %lu >>>\r\n", priority, queue->size);
    return 0; // Success
}

// Extraer el elemento de mayor prioridad de la cola
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

// Verificar si la cola está vacía
int priority_queue_is_empty(priority_queue_t *queue) {
    return (queue == NULL || queue->size == 0);
}
