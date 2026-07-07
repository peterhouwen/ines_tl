/** @file init_hardware.c
 *  @brief Initialize hardware.
 */

/****************************************************************************
 * Includes
 ****************************************************************************/
#include <stdio.h>
#include "esp_log.h"
#include "io_hal.h"
#include "driver/i2c_master.h"
#include "init_hardware.h"

static const char *TAG = "Initialize hardware";

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


/****************************************************************************
 * Function : init_hardware()
 ****************************************************************************/
void init_hardware()
{
    i2c_master_bus_handle_t bus_handle;
    i2c_master_init(&bus_handle);
    uint8_t value;
    ESP_LOGI(TAG, "I2C initialized successfully");

    hal_io_t io_handle;
    get_io_handle(&io_handle);
    io_handle.init();
    io_handle.register_write_byte(0x00, 0x00);     // GPA OUTPUT
    io_handle.register_write_byte(0x01, 0x00);     // GPB OUTPUT
    io_handle.register_set_level(0x01, 1 << 3, 1); // IO3 INPUT
    io_handle.register_set_level(0x0D, 1 << 3, 1); // IO3 Pull up
    io_handle.register_set_level(0x05, 1 << 3, 1); // IO3 Interrupt on change
    io_handle.register_set_level(0x07, 1 << 3, 1); // IO3 Default value
    io_handle.register_set_level(0x09, 1 << 3, 1); // IO3 Compare against default value
    io_handle.register_set_level(0x0B, 1 << 2, 1); // Interrupt Open-drain output

    /* Clear interrupt*/
    io_handle.register_read( 0x13, &value, 1);

    ESP_LOGI(TAG, "IO expander initialized successfully");
}
