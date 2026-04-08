#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_pm.h"

#define BLINK_GPIO CONFIG_BLINK_GPIO

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          BLINK_GPIO // Define the output GPIO
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY               (2048) // Set duty to 25%. (2 ** 13) * 25% = 2048
#define LEDC_DUTY2              (128) // Set duty to 15%. (2 ** 13) * 15% = 128
#define LEDC_CLK_SRC            LEDC_AUTO_CLK
#define LEDC_FREQUENCY          (4000) // Frequency in Hertz. Set frequency at 4 kHz

#define LEDC_TEST_FADE_TIME     (48)
#define LEDC_TEST_FADE_TIME2    (96)

/* Warning:
 * For ESP32, ESP32S2, ESP32S3, ESP32C3, ESP32C2, ESP32C6, ESP32H2 (rev < 1.2), ESP32P4 (rev < 3.0) targets,
 * when LEDC_DUTY_RES selects the maximum duty resolution (i.e. value equal to SOC_LEDC_TIMER_BIT_WIDTH),
 * 100% duty cycle is not reachable (duty cannot be set to (2 ** SOC_LEDC_TIMER_BIT_WIDTH)).
 */

static void example_ledc_init(void)
{
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .duty_resolution  = LEDC_DUTY_RES,
        .timer_num        = LEDC_TIMER,
        .freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 4 kHz
        .clk_cfg          = LEDC_CLK_SRC,
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .gpio_num       = LEDC_OUTPUT_IO,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0,
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    // Initialize fade service
    ledc_fade_func_install(0);

}


void heartbeat(void *arg)
{
    // Set the LEDC peripheral configuration
    example_ledc_init();

    while(1)
    {
        // Set duty to 0%
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0));
        // Update duty to apply the new value
        ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
        vTaskDelay( 900 / portTICK_PERIOD_MS );
        // Pulse 1            
        ledc_set_fade_with_time(LEDC_MODE,
                                LEDC_CHANNEL, LEDC_DUTY, LEDC_TEST_FADE_TIME);
        ledc_fade_start(LEDC_MODE,
                        LEDC_CHANNEL, LEDC_FADE_NO_WAIT);

        ledc_set_fade_with_time(LEDC_MODE,
                                LEDC_CHANNEL, 0, LEDC_TEST_FADE_TIME);
        ledc_fade_start(LEDC_MODE,
                        LEDC_CHANNEL, LEDC_FADE_NO_WAIT);

        vTaskDelay( 300 / portTICK_PERIOD_MS );
        // Pulse 2
        ledc_set_fade_with_time(LEDC_MODE,
                                LEDC_CHANNEL, LEDC_DUTY2, LEDC_TEST_FADE_TIME2);
        ledc_fade_start(LEDC_MODE,
                        LEDC_CHANNEL, LEDC_FADE_NO_WAIT);

        ledc_set_fade_with_time(LEDC_MODE,
                                LEDC_CHANNEL, 0, LEDC_TEST_FADE_TIME2);
        ledc_fade_start(LEDC_MODE,
                        LEDC_CHANNEL, LEDC_FADE_NO_WAIT);

    }

}
