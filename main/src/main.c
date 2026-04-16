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
    esp_err_t ret = xTaskCreate( heartbeat, "Heartbeat", 1024, NULL, 10, &xHandle );
    configASSERT( xHandle );

    if (ret != pdPASS) {
        ESP_LOGE(TAG, "Task creation failed: %s", esp_err_to_name(ret));
    }

    for( ;; )
    {
        // empty
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}