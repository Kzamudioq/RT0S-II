/*
 * queue_priority.h
 *
 *  Created on: Jun 9, 2024
 *      Author: ktzam
 */

#ifndef INC_QUEUE_PRIORITY_H_
#define INC_QUEUE_PRIORITY_H_

#include "cmsis_os.h"

#include "logger.h"
#include <stdlib.h>
#include <stdint.h>


// Estructura de un elemento de la cola de prioridad
typedef struct {
    uint8_t priority;  // Prioridad del elemento
    void *data;        // Datos del elemento
} priority_queue_item_t;

// Estructura de la cola de prioridad
typedef struct {
    priority_queue_item_t *array;  // Array de elementos de la cola
    uint32_t capacity;              // Capacidad máxima de la cola
    uint32_t size;                  // Tamaño actual de la cola
} priority_queue_t;

// Funciones públicas
priority_queue_t* priority_queue_create(uint32_t capacity);
void priority_queue_destroy(priority_queue_t *queue);
int priority_queue_push(priority_queue_t *queue, void *data, uint8_t priority);
void* priority_queue_pop(priority_queue_t *queue);
int priority_queue_is_empty(priority_queue_t *queue);

#endif /* INC_QUEUE_PRIORITY_H_ */
