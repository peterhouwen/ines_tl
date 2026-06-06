/** @file traffic_light.c
 *  @brief Traffic light.
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

static const char *TAG = "traffic light 1";

//static t_state_machine state = INIT;

/****************************************************************************
 * Function : traffic_light()
 ****************************************************************************/
void traffic_light(void *arg)
{
    hal_io_t io_handle;

    get_io_handle(&io_handle);

    while (true)
    {
        //switch (state)
        switch(0)
        {
        case INIT:
            io_handle.register_write_byte(0x12, 0x02); // yellow
            vTaskDelay(500 / portTICK_PERIOD_MS);
            io_handle.register_write_byte(0x12, 0x00); // off
            vTaskDelay(500 / portTICK_PERIOD_MS);
            break;
        case DRIVE:
            io_handle.register_write_byte(0x12, 0x01); // green
            break;
        case SLOW:
            io_handle.register_write_byte(0x12, 0x02); // yellow
            break;
        case STOP:
            io_handle.register_write_byte(0x12, 0x04); // red
            break;
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);

    }
}

/****************************************************************************
 * Function : launch_traffic_light()
 ****************************************************************************/
int launch_traffic_light()
{
    TaskHandle_t xHandle = NULL;

    esp_err_t ret = xTaskCreate( traffic_light, "Traffic light", 2048, NULL, 1, &xHandle );
    configASSERT( xHandle );

    if (ret != pdPASS) {
        ESP_LOGE(TAG, "Task creation failed: %s", esp_err_to_name(ret));
    }

    return 0;
}