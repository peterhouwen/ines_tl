#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BLINK_GPIO 25
#define BLINK_PERIOD 500

void app_main(void)
{
    int ledstate = 0;

    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    const TickType_t xDelay = BLINK_PERIOD / portTICK_PERIOD_MS;
    while(1)
    {
        printf("Ledstate: %d\n", ledstate);
        gpio_set_level(BLINK_GPIO, ledstate);
        //
        vTaskDelay( xDelay );
        ledstate = !ledstate;
    }

}