/** @file mcp23017.h
 *  @brief The interface definition for the io-expander
 * 
 *  This is the header file for the definition of the interface for a
 *  io-expander.
 */
#pragma once

#include "driver/i2c_master.h"
#include "mcp23017.h"

#define IODIRA    0x00
#define IODIRB    0x01
#define IPOLA     0x02
#define IPOLB     0x03
#define GPINTENA  0x04
#define GPINTENB  0x05
#define DEFVALA   0x06
#define DEFVALB   0x07
#define INTCONA   0x08
#define INTCONB   0x09
#define IOCON     0x0A
#define GPPUA     0x0C
#define GPPUB     0x0D
#define INTFA     0x0E
#define INTFB     0x0F
#define INTCAPA   0x10
#define INTCAPB   0x11
#define GPIOA     0x12
#define GPIOB     0x13
#define OLATA     0x14
#define OLATB     0x15

/****************************************************************************
 * Function prototypes
 ****************************************************************************/
void mcp23017_init(void);
void mcp23017_register_read(uint8_t reg, uint8_t * data, size_t len);
void mcp23017_register_write_byte(uint8_t reg, uint8_t value);
void mcp23017_register_set_level(uint8_t reg, uint8_t bitmask, uint8_t level);

/***End of File**************************************************************/
