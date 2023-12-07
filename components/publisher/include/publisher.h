/*
 * Publisher function header file
 *
 * Author: Oleksii Leznovskyi
 */

#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

/**
 * @brief Function for publisher task
 * Publisher function increment counter and put result in queue
 * Period of incremention set by INC_PERIOD_SEC definition(located in publisher.c)
 */
void Publisher(void *arg);


/**
 * @brief Function for register task handle, pointer to queue and setup timer
 * @arg   publisher_handle_ptr - pointer to publisher task
 * @arg   queue_handle_ptr     - pointer to queue 
 */
void Publisher_init(
                     TaskHandle_t*  publisher_handle_ptr,  ///< pointer to publisher task 
                     QueueHandle_t* queue_handle_ptr       ///< pointer to queue 
                   );

#endif //PUBLISHER_H