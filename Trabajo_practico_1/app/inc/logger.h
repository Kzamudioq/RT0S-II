/*
 * @file   : logger.h
 * @author : Sebastian Bedin <sebabedin@gmail.com>
 * @version: v1.0.0
 *
 * @brief  : Header file for the logger module
 *
 * This file defines macros and functions for logging messages.
 * It provides options to enable or disable logging, set the maximum message length,
 * and choose whether to use semihosting for output.
 */

#ifndef INC_LOGGER_H_
#define INC_LOGGER_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/********************** macros ***********************************************/

#define LOGGER_CONFIG_ENABLE                    (1)  // Set to 1 to enable logging
#define LOGGER_CONFIG_MAXLEN                    (64) // Maximum length of log messages
#define LOGGER_CONFIG_USE_SEMIHOSTING           (1)  // Set to 1 to use semihosting for output

#if 1 == LOGGER_CONFIG_ENABLE
#define LOGGER_LOG(...)\
    taskENTER_CRITICAL();\
    {\
        logger_msg_len = snprintf(logger_msg, (LOGGER_CONFIG_MAXLEN - 1), __VA_ARGS__);\
        logger_log_print_(logger_msg);\
    }\
    taskEXIT_CRITICAL()
#else
#define LOGGER_LOG(...) // Logging is disabled, so this macro does nothing
#endif

#define GET_NAME(var)  #var

/********************** typedef **********************************************/

extern char* const logger_msg; // Buffer for storing log messages
extern int logger_msg_len;      // Length of the last logged message (for debug information)

/********************** external functions declaration ***********************/

void logger_log_print_(char* const msg); // Function to print log messages

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* INC_LOGGER_H_ */

