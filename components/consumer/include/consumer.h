/*
 * Consumer function header file
 *
 * Author: Oleksii Leznovskyi
 */

#ifndef CONSUMER_H
#define CONSUMER_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

/**
 * @brief Function for consumer task
 * Consumer function read data from queue and log it.
 * Also Consumer function responsible of measuring time period 
 * between messages
 */
void Consumer(void *arg);


/**
 * @brief Function for register task handle, pointer to queue 
 * @arg   consumer_handle_ptr  - pointer to consumer task 
 * @arg   queue_handle_ptr     - pointer to queue 
 */
void Consumer_init(
                     QueueHandle_t* queue_handle_ptr        ///< pointer to queue 
                  );

#endif //CONSUMER_H