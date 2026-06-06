/** @file io_hal.h
 *  @brief The interface definition for the io-expander
 * 
 *  This is the header file for the definition of the interface for a
 *  io-expander.
 */
#pragma once

#include "driver/i2c_master.h"

/****************************************************************************
 * Typedefs
 ****************************************************************************/
typedef struct
{
    void (*init) ();
    void (*register_read) (uint8_t const reg, uint8_t * const state, size_t const len);
    void (*register_write_byte) (uint8_t const reg, uint8_t const value);
} hal_io_t;

/****************************************************************************
 * Function prototypes
 ****************************************************************************/
void get_io_handle(hal_io_t *ret_handle);

/***End of File**************************************************************/
