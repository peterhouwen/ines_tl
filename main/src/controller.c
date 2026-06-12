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

t_state_machine_A road = STOP;
t_state_machine_B crosswalk = HALT;

/****************************************************************************
 * Function : controller()
 ****************************************************************************/
void controller(void *arg)
{
    ESP_LOGI(TAG, "controller");
    vTaskDelay(5000 / portTICK_PERIOD_MS);

    while (true)
    {
        road = STOP;
        crosswalk = WALK;
        ESP_LOGI(TAG, "road: stop");
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        crosswalk = HURRY;
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        crosswalk = HALT;
        road = PREPARE;
        ESP_LOGI(TAG, "road: prepare");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        road = GO;
        ESP_LOGI(TAG, "road: go");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        road = SLOW;
        ESP_LOGI(TAG, "road: slow");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
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