#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "heartbeat.h"

static const char *TAG = "ines_tl";


void app_main(void)
{
    launch_heartbeat();

    for( ;; )
    {
        // empty
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}