/** @file controller.c
 *  @brief Traffic light controller.
 */

/****************************************************************************
 * Includes
 ****************************************************************************/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "types.h"

static const char *TAG = "controller";

static t_state_machine state = INIT;
static t_state_machine state2 = INIT;

/****************************************************************************
 * Function : controller()
 ****************************************************************************/
void controller(void *arg)
{
    ESP_LOGI(TAG, "controller");
    vTaskDelay(5000 / portTICK_PERIOD_MS);

    while (true)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        state = DRIVE;
        state2 = STOP;
        ESP_LOGI(TAG, "road");

        vTaskDelay(1000 / portTICK_PERIOD_MS);
        state = STOP;
        state2 = DRIVE;
        ESP_LOGI(TAG, "crosswalk");
    }
}

/****************************************************************************
 * Function : launch_controller()
 ****************************************************************************/
int launch_controller()
{
    TaskHandle_t xHandle = NULL;

    esp_err_t ret = xTaskCreate( controller, "Controller", 2048, NULL, 1, &xHandle );
    configASSERT( xHandle );

    if (ret != pdPASS) {
        ESP_LOGE(TAG, "Task creation failed: %s", esp_err_to_name(ret));
    }

    return 0;
}