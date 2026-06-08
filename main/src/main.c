#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "heartbeat.h"
#include "init_hardware.h"
#include "controller.h"
#include "traffic_light1.h"
#include "traffic_light2.h"

void app_main(void)
{
    launch_heartbeat();
    init_hardware();
    launch_controller();
    launch_traffic_light();
    launch_traffic_light2();

    for(;;)
    {
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}