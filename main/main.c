#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"

static const char *TAG = "ines_tl";

#define BLINK_GPIO CONFIG_BLINK_GPIO

static uint8_t s_led_state = 0;

static void blink_led(void)
{
    gpio_set_level(BLINK_GPIO, s_led_state);
}

static void configure_led(void)
{
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}

void app_main(void)
{
    configure_led();
    const TickType_t xDelay = CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS;

    while(1)
    {
        ESP_LOGI(TAG, "Turning the led %s!", s_led_state ? "ON" : "OFF");
        blink_led();

        s_led_state = !s_led_state;
        vTaskDelay( xDelay );
    }

}