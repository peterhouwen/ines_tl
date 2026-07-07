/** @file io_hal.c
 *  @brief Mapping the HAL to a driver
 */

/****************************************************************************
 * Includes
 ****************************************************************************/
#include "io_hal.h"
#include "mcp23017.h"

/****************************************************************************
 * Map the HAL to driver
 ****************************************************************************/
hal_io_t io =
{
    .init = mcp23017_init,
    .register_read = mcp23017_register_read,
    .register_write_byte = mcp23017_register_write_byte,
    .register_set_level = mcp23017_register_set_level
};

/****************************************************************************
 * Function : get_io_handle()
 ****************************************************************************/
void get_io_handle(hal_io_t *ret_handle)
{
    *ret_handle = io;
}