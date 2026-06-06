#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "heartbeat.h"
#include "driver/i2c_master.h"
#include "io_hal.h"

#define I2C_MASTER_SCL_IO           (gpio_num_t)22                         /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO           (gpio_num_t)21                         /*!< gpio number for I2C master data */
#define I2C_MASTER_NUM              I2C_NUM_0
#define I2C_MASTER_FREQ_HZ          100000                                 /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                                      /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                                      /*!< I2C master doesn't need buffer */
#define DATA_LENGTH                 64                                     /*!< Data buffer length for test buffer */

#define I2C_MASTER_TIMEOUT_MS       1000

#define MCP23017_ADDR               0x20                                   /*!< MCP23017 address */

static const char *TAG = "ines_tl";
i2c_master_bus_handle_t bus_handle;
i2c_master_dev_handle_t dev_handle;

TaskHandle_t xHandle_CTRL = NULL;
TaskHandle_t xHandle_TL = NULL;
TaskHandle_t xHandle_TL2 = NULL;

hal_io_t io_handle;

typedef enum {
    INIT,
    DRIVE,
    SLOW,
    STOP
} t_state_machine;

static t_state_machine state = INIT;
static t_state_machine state2 = INIT;

/**
 * @brief i2c master initialization
 */
static void i2c_master_init(i2c_master_bus_handle_t *bus_handle)
{
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_MASTER_NUM,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, bus_handle));

}


void controller(void *arg)
{
    ESP_LOGI(TAG, "controller");
    vTaskDelay(5000 / portTICK_PERIOD_MS);

    while (true)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        state = DRIVE;
        state2 = STOP;
        ESP_LOGI(TAG, "road");

        vTaskDelay(1000 / portTICK_PERIOD_MS);
        state = STOP;
        state2 = DRIVE;
        ESP_LOGI(TAG, "crosswalk");
    }
}

int launch_controller()
{
    esp_err_t ret = xTaskCreate( controller, "Controller", 2048, NULL, 1, &xHandle_CTRL );
    configASSERT( xHandle_CTRL );

    if (ret != pdPASS) {
        ESP_LOGE(TAG, "Task creation failed: %s", esp_err_to_name(ret));
    }

    return 0;
}

void traffic_light(void *arg)
{

    while (true)
    {
        switch (state)
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

void traffic_light2(void *arg)
{
\
    while (true)
    {
        switch (state2)
        {
        case INIT:
            io_handle.register_write_byte(0x13, 0x04); // red
            //ESP_ERROR_CHECK(mcp23017_register_write_byte(dev_handle, 0x13, 0x04)); // red
            vTaskDelay(500 / portTICK_PERIOD_MS);
            io_handle.register_write_byte(0x13, 0x00); // off
            //ESP_ERROR_CHECK(mcp23017_register_write_byte(dev_handle, 0x13, 0x00)); // off
            vTaskDelay(500 / portTICK_PERIOD_MS);
            break;
            case SLOW:
            break;
            case DRIVE:
            io_handle.register_write_byte(0x13, 0x01); // green
            //ESP_ERROR_CHECK(mcp23017_register_write_byte(dev_handle, 0x13, 0x01)); // green
            break;
            case STOP:
            io_handle.register_write_byte(0x13, 0x04); // red
            //ESP_ERROR_CHECK(mcp23017_register_write_byte(dev_handle, 0x13, 0x04)); // red
            break;
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);

    }
}

int launch_traffic_light()
{
    esp_err_t ret = xTaskCreate( traffic_light, "Traffic light", 2048, NULL, 1, &xHandle_TL );
    configASSERT( xHandle_TL );

    if (ret != pdPASS) {
        ESP_LOGE(TAG, "Task creation failed: %s", esp_err_to_name(ret));
    }

    return 0;
}

int launch_traffic_light2()
{
    esp_err_t ret = xTaskCreate( traffic_light2, "Traffic light2", 2048, NULL, 1, &xHandle_TL2 );
    configASSERT( xHandle_TL2 );

    if (ret != pdPASS) {
        ESP_LOGE(TAG, "Task creation failed: %s", esp_err_to_name(ret));
    }

    return 0;
}

void app_main(void)
{

    launch_heartbeat();

    get_io_handle(&io_handle);

    //uint8_t data[2];
    i2c_master_init(&bus_handle);
    ESP_LOGI(TAG, "I2C initialized successfully");

    io_handle.init();

    //ESP_ERROR_CHECK(mcp23017_register_write_byte(dev_handle, 0x00, 0x00)); // GPA OUTPUT
    //ESP_ERROR_CHECK(mcp23017_register_write_byte(dev_handle, 0x01, 0x00)); // GPB OUTPUT
    //ESP_ERROR_CHECK(mcp23017_register_write_byte(dev_handle, 0x12, 0x00));
    //ESP_ERROR_CHECK(mcp23017_register_write_byte(dev_handle, 0x13, 0x00));

    io_handle.register_write_byte(0x00, 0x00); // GPA OUTPUT
    io_handle.register_write_byte(0x01, 0x00); // GPB OUTPUT
    io_handle.register_write_byte(0x12, 0x00);
    io_handle.register_write_byte(0x13, 0x00);


    launch_controller();
    launch_traffic_light();
    launch_traffic_light2();

    for(;;)
    {
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

}