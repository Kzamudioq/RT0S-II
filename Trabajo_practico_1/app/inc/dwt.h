/*
 * @file   : dwt.h
 * @date   : Set 26, 2023
 * @author : Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>
 * @version: v1.0.0
 *
 * @brief  : Header file for Data Watchpoint and Trace (DWT) cycle counter
 *
 * This file provides macros and functions to initialize, reset, enable, disable,
 * and read the cycle counter of the DWT unit. It also includes an example usage.
 */

#ifndef DWT_INC_DWT_H_
#define DWT_INC_DWT_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

#include "stm32f4xx.h"  // Include the necessary STM32F4xx header file

/********************** macros ***********************************************/

/* Initialize cycle counter */
#define cycle_counter_init() ({\
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;     /* enable DWT hardware */\
    DWT->CYCCNT = 0;                                    /* reset cycle counter */\
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;                /* start counting */\
})

/* Reset cycle counter */
#define cycle_counter_reset() (DWT->CYCCNT = 0)

/* Enable counting */
#define cycle_counter_enable() (DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk)

/* Disable counting if not used anymore */
#define cycle_counter_disable() (~DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk)

/* Read cycle counter */
#define cycle_counter_get() (DWT->CYCCNT)
#define cycles_per_us (SystemCoreClock / 1000000)
#define cycle_counter_time_us() (DWT->CYCCNT / cycles_per_us)

/********************** macros ***********************************************/

/********************** typedef **********************************************/

/********************** external data declaration ****************************/

/********************** external functions declaration ***********************/

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* DWT_INC_DWT_H_ */

