/*
 * @file   : board.h
 * @date   : May 8, 2024
 * @author : grupo_3
 *
 * @brief  : Header file for board-specific definitions
 *
 * This file defines the GPIO pins used for buttons and LEDs on the board.
 */

#ifndef INC_BOARD_H_
#define INC_BOARD_H_

/* Button GPIO configuration */
#define PORT_BUTTON GPIOC
#define PIN_BUTTON GPIO_PIN_13

/* LED GPIO configurations */
#define LED_R_Pin GPIO_PIN_0
#define LED_R_GPIO_Port GPIOA
#define LED_G_Pin GPIO_PIN_1
#define LED_G_GPIO_Port GPIOA
#define LED_B_Pin GPIO_PIN_4
#define LED_B_GPIO_Port GPIOA

#endif /* INC_BOARD_H_ */
