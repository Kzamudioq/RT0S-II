#ifndef INC_TASK_BUTTON_H_
#define INC_TASK_BUTTON_H_

#include "cmsis_os.h"
#include "stm32f4xx_hal.h"

// Estructura para la configuración del botón
typedef struct {
    GPIO_TypeDef *port;    // Puntero al puerto GPIO del botón
    uint16_t pin;          // Número de pin del botón
} ButtonConfig_t;

// Estructura para el objeto activo del botón
typedef struct {
    QueueHandle_t queue_button_h;  // Manejador de la cola del botón
    TaskHandle_t *task_button_h;   // Manejador de la tarea del botón
    ButtonConfig_t button_config;  // Configuración del botón
} ButtonActiveObject_t;

// Enumeración para los estados del botón
typedef enum  {
    PULSE_OUT = 0,    // No presionado o pulsación no calificante
    PULSE_PULSE,      // Presionado entre 200 ms y 1000 ms
    PULSE_SHORT,      // Presionado entre 1000 ms y 2000 ms
    PULSE_LONG,       // Presionado más de 2000 ms
    PULSE_ERROR       // Estado de error o comportamiento indefinido
} state_button_t;

// Prototipos de funciones
void button_initialize_ao(ButtonActiveObject_t *parameters, ButtonConfig_t button_config, const char *ao_task_name);

#endif /* INC_TASK_BUTTON_H_ */
