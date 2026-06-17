/** @file button.c
 *  @brief Crosswalk button.
 */

/****************************************************************************
 * Includes
 ****************************************************************************/
#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "time.h"
#include "driver/gpio.h"
#include "io_hal.h"

/**
 * Brief:
 * 
 * GPIO status:
 * GPIO_INPUT_IO_0:  input, pulled up, interrupt from falling edge
 * 
 */

#define GPIO_INPUT_IO_0    CONFIG_GPIO_INPUT_0
#define GPIO_INPUT_PIN_SEL (1ULL<<GPIO_INPUT_IO_0)

#define ESP_INTR_FLAG_DEFAULT 0

static const char *TAG = "button";
TaskHandle_t xHandleButton = NULL;
extern TaskHandle_t xHandleController;

/****************************************************************************
 * Function : gpio_interrupt_handler()
 ****************************************************************************/
static void IRAM_ATTR gpio_isr_handler( void *arg )
{
    ESP_EARLY_LOGI(TAG, "Button pressed");
    vTaskNotifyGiveFromISR( xHandleController,
                            NULL);
}

/****************************************************************************
 * Function : button()
 ****************************************************************************/
void button(void *arg)
{
    uint8_t value = 0;
    hal_io_t io_handle;

    get_io_handle(&io_handle);

    gpio_config_t io_conf = {};
    //interrupt of falling edge
    io_conf.intr_type = GPIO_INTR_NEGEDGE;
    //bit mask of the pins
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    //set as input mode
    io_conf.mode = GPIO_MODE_INPUT;
    //enable pull-up mode
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);

    //install gpio isr service
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    //hook isr handler for specific gpio pin
    gpio_isr_handler_add(GPIO_INPUT_IO_0, gpio_isr_handler, (void *)GPIO_INPUT_IO_0);
    ESP_LOGI(TAG, "button started");
    
    while (true)
    {
        //wait for crosswalk to finish
        ulTaskNotifyTake( pdTRUE, portMAX_DELAY);
        //clear interrupt by reading GPIO
        io_handle.register_read( 0x13, &value, 1);
        ESP_LOGI(TAG, "button is hot");
    }
}

/****************************************************************************
 * Function : launch_button()
 ****************************************************************************/
int launch_button()
{
    esp_err_t ret = xTaskCreate( button, "Button", 2048, NULL, 1, &xHandleButton );
    configASSERT( xHandleButton );

    if (ret != pdPASS) {
        ESP_LOGE(TAG, "Task creation failed: %s", esp_err_to_name(ret));
    }

    return 0;
}