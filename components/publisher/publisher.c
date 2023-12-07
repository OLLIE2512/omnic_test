#include "publisher.h"
#include "driver/gptimer.h"
#include "message_box_types.h"

#define INC_PERIOD_SEC     5
#define QUEUE_TICK_TO_WAIT 100

static TaskHandle_t*      publisherTaskHandle_ptr = NULL;
static QueueHandle_t*     queueHandle_ptr         = NULL;
static gptimer_handle_t   gptimer = NULL;


//************************************************************************************************************
static void incCounterValue(Counter_size_t* value_ptr)
{
  if(*value_ptr <= UINT32_MAX)
  {
    (*value_ptr)++;
  }
}


//************************************************************************************************************
static bool IRAM_ATTR timer_group_isr_callback(
                                                gptimer_handle_t timer, 
                                                const gptimer_alarm_event_data_t *edata, 
                                                void *user_data
                                              )
{
    BaseType_t xHigherPriorityTaskWoken;
    ESP_ERROR_CHECK((*publisherTaskHandle_ptr) == NULL);

    xTaskNotifyFromISR(
                        (*publisherTaskHandle_ptr),
                        0,                      /* no value needed, just notify */  
                        eNoAction,
                        &xHigherPriorityTaskWoken 
                      );

    return (xHigherPriorityTaskWoken == pdTRUE);
}


//************************************************************************************************************
static void publisher_timer_init()
{
    /* Select and initialize basic parameters of the timer */

    gptimer_config_t timer_config = 
    {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1000000, // 1MHz, 1 tick=1us
    };

    ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &gptimer));

    gptimer_event_callbacks_t cbs = 
    {
        .on_alarm = timer_group_isr_callback,
    };
    ESP_ERROR_CHECK(gptimer_register_event_callbacks(gptimer, &cbs, NULL));

    gptimer_alarm_config_t alarm_config = 
    {
        .reload_count = 0,
        .alarm_count = INC_PERIOD_SEC * 1000000, // period = 1s
        .flags.auto_reload_on_alarm = true,
    };

    ESP_ERROR_CHECK(gptimer_set_alarm_action(gptimer, &alarm_config));
    ESP_ERROR_CHECK(gptimer_enable(gptimer));
    
}


//************************************************************************************************************
void Publisher_init(TaskHandle_t* publisher_handle_ptr, QueueHandle_t* queue_handle_ptr)
{
  // init must be called before xTaskCreate
  ESP_ERROR_CHECK(publisher_handle_ptr == NULL);  
  ESP_ERROR_CHECK(queue_handle_ptr == NULL);  

  // register task handle
  publisherTaskHandle_ptr = publisher_handle_ptr;

  //register queue handle
  queueHandle_ptr = queue_handle_ptr;

  //setup timer
  publisher_timer_init();
}


//************************************************************************************************************
void Publisher(void *arg)
{
  static Counter_size_t cnt = 0;
  ESP_ERROR_CHECK(gptimer_start(gptimer));
  for( ;; )
    {
      // wait for notification from timer isr
      xTaskNotifyWait( 0x00, ULONG_MAX, NULL, portMAX_DELAY);  

      // increment counter value when notification recived
      incCounterValue(&cnt);
      
      // put new value of counter in queue
      ESP_ERROR_CHECK(xQueueSendToBack((*queueHandle_ptr), &cnt, (TickType_t)QUEUE_TICK_TO_WAIT) != pdPASS);
    }
}
