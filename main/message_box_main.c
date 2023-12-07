/*
 * Omnic test project
 *
 * Author: Oleksii Leznovskyi
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "message_box_types.h"
#include "consumer.h"
#include "publisher.h"

// Task handlers 
static TaskHandle_t publisherTaskHandle = NULL;
static TaskHandle_t consumerTaskHandle = NULL;

static QueueHandle_t xMessageQueue; 

void app_main(void)
{
  xMessageQueue = xQueueCreate(QUEUE_LENGTH, sizeof(Counter_size_t));
  // Check if QueueCreate was successful 
  ESP_ERROR_CHECK(xMessageQueue == NULL);

  Publisher_init(&publisherTaskHandle, &xMessageQueue);
  // Start publisher task
  xTaskCreate(Publisher, "Publisher_Task", 2048, NULL, 10, &publisherTaskHandle);
  ESP_ERROR_CHECK(publisherTaskHandle == NULL);

  Consumer_init(&xMessageQueue);
  // Start consumer task
  xTaskCreate(Consumer, "consumer_Task", 2048, NULL, 10, &consumerTaskHandle);
  ESP_ERROR_CHECK(consumerTaskHandle == NULL);

}
