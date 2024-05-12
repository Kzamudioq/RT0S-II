/*
 * @file   : logger.c
 * @date   : May 8, 2024
 * @author : Sebastian Bedin <sebabedin@gmail.com>
 * @version: v1.0.0
 *
 * @brief  : Logger implementation
 *
 * This file implements the logger functionality, including logging messages
 * to the console using semihosting or disabling logging altogether based on
 * configuration options. It includes necessary headers and defines the internal
 * data structures and functions required for logging.
 */

/********************** Inclusions *******************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "main.h"
#include "cmsis_os.h"

#include "logger.h"

/********************** Macros and Definitions *******************************/

/********************** Internal Data Declaration ****************************/

/********************** Internal Functions Declaration ***********************/

/********************** Internal Data Definition ******************************/

/********************** External Data Definition ******************************/

/* Buffer to hold the log message */
static char logger_msg_buffer_[LOGGER_CONFIG_MAXLEN];
char* const logger_msg = logger_msg_buffer_;
int logger_msg_len;

/********************** Internal Functions Definition ************************/

/********************** External Functions Definition ************************/

#if 1 == LOGGER_CONFIG_USE_SEMIHOSTING
/**
 * @brief Print the log message to the console using semihosting.
 *
 * @param msg Pointer to the message string to be printed.
 */
void logger_log_print_(char* const msg)
{
    printf(msg);
    fflush(stdout);
}
#else
/**
 * @brief Dummy function to disable logging.
 *
 * This function does nothing when logging is disabled.
 *
 * @param msg Pointer to the message string to be printed (unused).
 */
void logger_log_print_(char* const msg)
{
    return;
}
#endif

/********************** End of File ******************************************/
