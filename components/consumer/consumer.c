#include "consumer.h"
#include "message_box_types.h"
#include "driver/gptimer.h"

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"

static const char *TAG = "Consumer";

static QueueHandle_t* queueHandle        = NULL;
static gptimer_handle_t gptimer         = NULL;


//************************************************************************************************************
static void consumer_timer_init()
{
    /* Select and initialize basic parameters of the timer */

    gptimer_config_t timer_config = 
    {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1000000, // 1MHz, 1 tick=1us
    };
    ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &gptimer));
    ESP_ERROR_CHECK(gptimer_enable(gptimer));

    ESP_ERROR_CHECK(gptimer_start(gptimer));
}


//************************************************************************************************************
void Consumer_init(QueueHandle_t* queue_handle_ptr)
{
  // init must be called before xTaskCreate
  ESP_ERROR_CHECK(queue_handle_ptr == NULL);  

  //register queue handle
  queueHandle = queue_handle_ptr;

  // setup timer 
  consumer_timer_init();
}


//************************************************************************************************************
void Consumer(void *arg)
{
  static Counter_size_t recived_value;
  static uint64_t timestamp;
  ESP_ERROR_CHECK(gptimer_set_raw_count(gptimer, 0));
  for( ;; )
    {
      // wait for messages in queue
      xQueueReceive( (*queueHandle), &(recived_value), portMAX_DELAY);

      ESP_ERROR_CHECK(gptimer_get_raw_count(gptimer, &timestamp));
      ESP_ERROR_CHECK(gptimer_set_raw_count(gptimer, 0));

      // log counter value
      ESP_LOGI(TAG, "Recived counter value - %lu", recived_value);

      // log timestamp value
      ESP_LOGI(TAG, "Timestamp value - %llu us", timestamp);

    }
}


