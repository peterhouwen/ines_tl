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
#include "io_hal.h"

static const char *TAG = "controller";

t_state_machine_A road = STOP;
t_state_machine_B crosswalk = HALT;

TaskHandle_t xHandleController = NULL;
extern TaskHandle_t xHandleButton;

/****************************************************************************
 * Function : controller()
 ****************************************************************************/
void controller(void *arg)
{
    ESP_LOGI(TAG, "controller");
    vTaskDelay(5000 / portTICK_PERIOD_MS);

    while (true)
    {
        road = PREPARE;
        ESP_LOGI(TAG, "road: prepare");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        road = GO;
        ESP_LOGI(TAG, "road: go");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        ulTaskNotifyTake( pdTRUE, portMAX_DELAY);
        ESP_LOGI(TAG, "Enable crosswalk");
        road = SLOW;
        ESP_LOGI(TAG, "road: slow");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        road = STOP;
        vTaskDelay(500 / portTICK_PERIOD_MS);
        crosswalk = WALK;
        ESP_LOGI(TAG, "crosswalk: walk");
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        crosswalk = HURRY;
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        crosswalk = HALT;
        vTaskDelay(500 / portTICK_PERIOD_MS);
        ESP_LOGI(TAG, "Notify button");
        xTaskNotifyGive(xHandleButton);
    }
}

/****************************************************************************
 * Function : launch_controller()
 ****************************************************************************/
int launch_controller()
{
    esp_err_t ret = xTaskCreate( controller, "Controller", 2048, NULL, 1, &xHandleController );
    configASSERT( xHandleController );

    if (ret != pdPASS) {
        ESP_LOGE(TAG, "Task creation failed: %s", esp_err_to_name(ret));
    }

    return 0;
}