#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "heartbeat.h"

static const char *TAG = "ines_tl";

TaskHandle_t xHandle = NULL;

void app_main(void)
{
    BaseType_t result = xTaskCreate( heartbeat, "Heartbeat", 1024, NULL, 10, &xHandle );
    configASSERT( xHandle );

    if (result != pdPASS) {
        ESP_LOGE(TAG, "Task creation failed!");
    }

    for( ;; )
    {
        // empty
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}