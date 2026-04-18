#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "heartbeat.h"
#include "driver/i2c_master.h"

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

TaskHandle_t xHandle_TL = NULL;

/**
 * @brief i2c master initialization
 */
static void i2c_master_init(i2c_master_bus_handle_t *bus_handle, i2c_master_dev_handle_t *dev_handle)
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

    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = MCP23017_ADDR,
        .scl_speed_hz = I2C_MASTER_FREQ_HZ,
    };
    ESP_ERROR_CHECK(i2c_master_bus_add_device(*bus_handle, &dev_config, dev_handle));
}

/**
 * @brief Read a sequence of bytes from a MCP23017 I/O expander
 */
static esp_err_t mcp23017_register_read(i2c_master_dev_handle_t dev_handle, uint8_t reg_addr, uint8_t *data, size_t len)
{
    return i2c_master_transmit_receive(dev_handle, &reg_addr, 1, data, len, I2C_MASTER_TIMEOUT_MS);
}

/**
 * @brief Write a byte to a MCP23017 I/O expander
 */
static esp_err_t mcp23017_register_write_byte(i2c_master_dev_handle_t dev_handle, uint8_t reg_addr, uint8_t data)
{
    uint8_t write_buf[2] = {reg_addr, data};
    return i2c_master_transmit(dev_handle, write_buf, sizeof(write_buf), I2C_MASTER_TIMEOUT_MS);
}

void traffic_light(void *arg)
{
    enum State {
        DRIVE,
        SLOW,
        STOP
    } state = DRIVE;

    while (true)
    {
        enum State next_state = state;
        switch (state)
        {
        case DRIVE:
            ESP_ERROR_CHECK(mcp23017_register_write_byte(dev_handle, 0x12, 0x01)); // green
            ESP_LOGI(TAG, "green");
            vTaskDelay(5000 / portTICK_PERIOD_MS);
            next_state = SLOW;
            break;
        case SLOW:
            ESP_ERROR_CHECK(mcp23017_register_write_byte(dev_handle, 0x12, 0x02)); // yellow
            ESP_LOGI(TAG, "yellow");
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            next_state = STOP;
            break;
        case STOP:
            ESP_ERROR_CHECK(mcp23017_register_write_byte(dev_handle, 0x12, 0x04)); // red
            ESP_LOGI(TAG, "red");
            vTaskDelay(3000 / portTICK_PERIOD_MS);
            next_state = DRIVE;
            break;
        }
        state = next_state;

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

void app_main(void)
{
    launch_heartbeat();

    uint8_t data[2];
    i2c_master_init(&bus_handle, &dev_handle);
    ESP_LOGI(TAG, "I2C initialized successfully");

    ESP_ERROR_CHECK(mcp23017_register_write_byte(dev_handle, 0x00, 0x00)); // GPA OUTPUT
    ESP_ERROR_CHECK(mcp23017_register_write_byte(dev_handle, 0x01, 0x00)); // GPB OUTPUT
    ESP_ERROR_CHECK(mcp23017_register_write_byte(dev_handle, 0x13, 0x00));

    launch_traffic_light();

    for(;;)
    {
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

}