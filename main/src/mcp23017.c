/** @file mcp23017.c
 *  @brief The implementation for the io-expander
 */

/****************************************************************************
 * Includes
 ****************************************************************************/
#include "driver/i2c_master.h"

#define I2C_MASTER_FREQ_HZ          100000                                 /*!< I2C master clock frequency */
#define MCP23017_ADDR               0x20                                   /*!< MCP23017 address */

#define I2C_MASTER_TIMEOUT_MS       1000

i2c_master_bus_handle_t handle;
i2c_master_dev_handle_t dev_handle;

/**
 * @brief i2c device initialization
 */
void mcp23017_init(void)
{
    ESP_ERROR_CHECK(i2c_master_get_bus_handle(0, &handle));

    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = MCP23017_ADDR,
        .scl_speed_hz = I2C_MASTER_FREQ_HZ,
    };
    ESP_ERROR_CHECK(i2c_master_bus_add_device(handle, &dev_config, &dev_handle));
}

/****************************************************************************
 * Function : mcp23017_register_read
 ****************************************************************************/

/**
 * @brief Read a sequence of bytes from a MCP23017 I/O expander
 */
void mcp23017_register_read(uint8_t reg_addr, uint8_t *data, size_t len)
{
    ESP_ERROR_CHECK(i2c_master_transmit_receive(dev_handle, &reg_addr, 1, data, len, I2C_MASTER_TIMEOUT_MS));
}

/****************************************************************************
 * Function : mcp23017_register_write
 ****************************************************************************/

/**
 * @brief Write a byte to a MCP23017 I/O expander
 */
void mcp23017_register_write_byte(uint8_t reg_addr, uint8_t data)
{
    uint8_t write_buf[2] = {reg_addr, data};
    ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, write_buf, sizeof(write_buf), I2C_MASTER_TIMEOUT_MS));
}


/****************************************************************************
 * Function : mcp23017_register_set_level
 ****************************************************************************/

/**
 * @brief Set level of MCP23017 I/O expander register according to bitmask
 */
void mcp23017_register_set_level(uint8_t reg_addr, uint8_t bitmask, uint8_t level)
{
    uint8_t value;
    mcp23017_register_read(reg_addr, &value, 1);

    for (int i = 0; i < 8; i++)
    {
        if (1 << i & bitmask)
        {
            if (level)
            {
                value |= 1 << i;
            }
            else
            {
                value &= ~(1 << i);
            }
        }
    }
    mcp23017_register_write_byte(reg_addr, value);

}