
# Trabajo Práctico 3: Memoria Dinámica

## Problema

Se requiere implementar un sistema para el control de tres LEDs (rojo, verde y azul) mediante la activación de un botón. El sistema debe responder de la siguiente forma:

1. **Estados del botón**:
    - **Pulso**: Si el botón se presiona entre 200 ms y 1000 ms. ⚡
    - **Corto**: Si el botón se presiona entre 1000 ms y 2000 ms. 🚀
    - **Largo**: Si el botón se presiona más de 2000 ms. 🕰️
    - **No presionado**: Para cualquier otro caso. ❌

2. **Funcionamiento de los LEDs**:
    - El LED rojo debe encenderse por 5 segundos si se detecta un botón pulso.
    - El LED verde debe encenderse por 5 segundos si se detecta un botón corto.
    - El LED azul debe encenderse por 5 segundos si se detecta un botón largo.
    - Solo se encenderá un LED a la vez.
    - Se debe detectar y encolar las pulsaciones del botón. Los LEDs se encienden según su prioridad: azul (mayor), verde (media) y rojo (menor).

## Requerimientos

1. **Cumplir con la descripción funcional del problema** (20 pts):
    - Enviar un video de la solución para verificar el correcto funcionamiento.

2. **Implementación de bloques de procesamiento**:
    - Implementar una tarea para el procesamiento del botón.
    - Implementar un objeto activo que realice el procesamiento del estado del botón y genere una acción sobre los LEDs. Este objeto activo se llamará Interfaz de Usuario (20 pts).
    - Implementar un objeto activo que controle los tres LEDs (20 pts).
    - El objeto activo de control de LED se debe instanciar solo si es requerido. Para esto, se solicita aplicar una arquitectura que permita crear y destruir sus recursos para poder liberar memoria para otros procesos no descriptos en este trabajo.
    - La comunicación entre las tareas debe realizarse mediante la implementación de una cola de prioridades. Los mensajes enviados a la cola deben contener información sobre su prioridad. El envío de mensajes podrá ser de forma desordenada (sin prioridad), pero la recepción siempre debe devolver el mensaje más prioritario (20 pts).

3. **Encapsulamiento**:
    - Encapsular el funcionamiento de los distintos módulos del sistema (10 pts).

4. **Proyecto STM32CubeIDE**:
    - Entregar un proyecto compatible con STM32CubeIDE (10 pts).

5. **Utilización del trabajo previo**:
    - Utilizar como base el trabajo realizado en el TP1.
    - 
## Solución

### Descripción de la Solución

Para resolver este problema, se implementó un sistema basado en un microcontrolador STM32 y el entorno de desarrollo STM32CubeIDE. El sistema consta de tres bloques de procesamiento: uno para el botón, otro para la lógica del problema y otro para los LEDs.

### Descripción del Código Implementado

El proyecto está diseñado para controlar tres LEDs (rojo, verde y azul) mediante la activación de un botón. Cada LED se enciende por 1 segundo en función del estado del botón detectado. A continuación, se describe el código implementado:

#### task_led.c

Este archivo contiene las funciones de tarea para controlar los LEDs rojo, verde y azul. Cada tarea escucha su cola correspondiente para mensajes que contienen instrucciones para encender el LED durante una duración especificada. Cuando se recibe un mensaje, la tarea enciende el LED, espera la duración especificada y luego lo apaga.

#### task_button.c

Esta tarea monitorea el estado del botón. Cuando se detecta una pulsación del botón, mide la duración de la pulsación y envía la duración (en ticks) a una cola para su procesamiento adicional. La tarea se ejecuta continuamente, verificando periódicamente el estado del botón.

#### task_user_interface.c

Esta tarea gestiona la interfaz de usuario, incluyendo la detección de pulsaciones de botón y el control de los LEDs en función de la duración de las pulsaciones del botón. Se encarga de recibir mensajes de la cola del botón, determinar el estado del botón y tomar acciones correspondientes, como encender o apagar los LEDs.

### Encapsulamiento y Objetos Activos

Cada tarea se implementa como una función separada, lo que permite un encapsulamiento adecuado del funcionamiento de cada tarea. Además, se utilizan colas para la comunicación entre las tareas, lo que facilita la separación de las responsabilidades y el diseño modular del sistema.

Los objetos activos se utilizan en este diseño para representar entidades independientes que pueden realizar acciones autónomamente en respuesta a eventos externos. La interfaz de usuario y las tareas de los LEDs son objetos activos porque toman decisiones y ejecutan acciones de forma independiente en función de los eventos externos, como las pulsaciones del botón. Esto facilita una arquitectura flexible y escalable del sistema.

### Placa de Desarrollo

Cada integrante del grupo 3 dispone de una placa de desarrollo STM32 F401RE.

### Verificación y Entrega

Se realizó una verificación del correcto funcionamiento del sistema, lo cual incluye una demostración en video. El proyecto se entrega como un proyecto compatible con STM32CubeIDE, listo para su compilación y carga en el microcontrolador.

[Ver video de demostración](https://github.com/Kzamudioq/RT0S-II/tree/4fa53415525d0978f9875a9e825755bc4aea497d/Trabajo_practico_3/Video) 📹 📹

### Integrantes del Grupo 3

Los integrantes del grupo 3 son: Royer Sanabria, Karen Zamudio y Lautaro Quarín. La mente central Royer y Tatiana, pero indudablemente el código pasó por manos de los tres integrantes. 💡💻

## Contribuciones

Las contribuciones al proyecto son bienvenidas. Siéntete libre de proponer mejoras en el código, sugerir nuevas funcionalidades o reportar problemas encontrados durante su uso. 🚀
