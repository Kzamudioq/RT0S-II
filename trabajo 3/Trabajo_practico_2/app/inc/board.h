/*
 * board.h
 *
 *  Created on: May 8, 2024
 *      Author: Grupo 3
 */
#ifndef INC_BOARD_H_
#define INC_BOARD_H_


/* Global macros ------------------------------------------------------------------------*/
#define PORT_BUTTON_A 		GPIOC
#define PIN_BUTTON_A		GPIO_PIN_13

#define LED_R_Pin 			GPIO_PIN_0
#define LED_R_GPIO_Port 	GPIOA
#define LED_G_Pin 			GPIO_PIN_1
#define LED_G_GPIO_Port 	GPIOA
#define LED_B_Pin 			GPIO_PIN_4
#define LED_B_GPIO_Port 	GPIOA

#define BUTTON_READ_A		HAL_GPIO_ReadPin(PORT_BUTTON_A, PIN_BUTTON_A)
#define BUTTON_PRESSED		GPIO_PIN_RESET
/* End global macros --------------------------------------------------------------------*/

/* Global structs -----------------------------------------------------------------------*/
/* End global structs -------------------------------------------------------------------*/

/* QueueHandle and TaskHandle -----------------------------------------------------------*/
/* End Queue and TaskHandle -------------------------------------------------------------*/

/* Global function ----------------------------------------------------------------------*/
/* End global function ------------------------------------------------------------------*/

#endif /* INC_BOARD_H_ */
