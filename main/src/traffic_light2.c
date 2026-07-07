/** @file traffic_light2.c
 *  @brief Traffic light 2.
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
#include "externals.h"

static const char *TAG = "traffic light 2";

/****************************************************************************
 * Function : traffic_light2()
 ****************************************************************************/
void traffic_light2(void *arg)
{
    hal_io_t io_handle;

    get_io_handle(&io_handle);

    io_handle.register_set_level(0x13, 1 << 0 | 1 << 1 | 1 << 2, 0); // turn LED off

    while (true)
    {
        switch (crosswalk)
        {
        case HALT:
            io_handle.register_set_level(0x13, 
                1 << 0 | 1 << 1 | 1 << 2, 0); // turn LED off
            io_handle.register_set_level(0x13, 1 << 2, 1); // red
            break;
        case WALK:
            io_handle.register_set_level(0x13, 
                1 << 0 | 1 << 1 | 1 << 2, 0); // turn LED off
            io_handle.register_set_level(0x13, 1 << 0, 1); // green
            break;
        case HURRY:
            io_handle.register_set_level(0x13, 1 << 0, 0); // off
            vTaskDelay(250 / portTICK_PERIOD_MS);
            io_handle.register_set_level(0x13, 1 << 0, 1); // green
            vTaskDelay(250 / portTICK_PERIOD_MS);
            break;
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);

    }
}

/****************************************************************************
 * Function : launch_traffic_light2()
 ****************************************************************************/
int launch_traffic_light2()
{
    TaskHandle_t xHandle = NULL;

    esp_err_t ret = xTaskCreate( traffic_light2, "Traffic light2", 2048, NULL, 1, &xHandle );
    configASSERT( xHandle );

    if (ret != pdPASS) {
        ESP_LOGE(TAG, "Task creation failed: %s", esp_err_to_name(ret));
    }

    return 0;
}
