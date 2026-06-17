/** @file button.c
 *  @brief Crosswalk button.
 */

/****************************************************************************
 * Includes
 ****************************************************************************/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "time.h"
#include "driver/gpio.h"
#include "io_hal.h"

#define INPUT_PIN 15

static const char *TAG = "button";
TaskHandle_t xHandleButton = NULL;
extern TaskHandle_t xHandleController;



/****************************************************************************
 * Function : gpio_interrupt_handler()
 ****************************************************************************/
static void gpio_isr_handler( void *arg )
{
//    BaseType_t xHigherPriorityTaskWoken;

//    xHigherPriorityTaskWoken = pdFALSE;

    ESP_EARLY_LOGI(TAG, "Button pressed");
    vTaskNotifyGiveFromISR( xHandleController,
                            NULL);
//    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
//    ESP_LOGI(TAG, "Woken %d", xHigherPriorityTaskWoken);
}

/****************************************************************************
 * Function : button()
 ****************************************************************************/
void button(void *arg)
{
    uint8_t value = 0;
    hal_io_t io_handle;

    ESP_LOGI(TAG, "button started");
    get_io_handle(&io_handle);
    
    gpio_set_direction(INPUT_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(INPUT_PIN, GPIO_PULLUP_ONLY);
    gpio_set_intr_type(INPUT_PIN, GPIO_INTR_NEGEDGE);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(INPUT_PIN, gpio_isr_handler, (void *)INPUT_PIN);
    
    while (true)
    {
        ulTaskNotifyTake( pdTRUE, portMAX_DELAY);
        /* Clear interrupt by reading GPIO */
        io_handle.register_read( 0x13, &value, 1);
        ESP_LOGI(TAG, "button is hot");
        vTaskDelay(100 / portTICK_PERIOD_MS);
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