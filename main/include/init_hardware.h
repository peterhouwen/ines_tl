/** @file init_hardware.h
 *  @brief Initialize hardware
 * 
 *  This is the header file for initialize hardware
 */
#pragma once


/****************************************************************************
 * Typedefs
 ****************************************************************************/

#define I2C_MASTER_SCL_IO           (gpio_num_t)22                         /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO           (gpio_num_t)21                         /*!< gpio number for I2C master data */
#define I2C_MASTER_NUM              I2C_NUM_0
#define I2C_MASTER_FREQ_HZ          100000                                 /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                                      /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                                      /*!< I2C master doesn't need buffer */
#define DATA_LENGTH                 64                                     /*!< Data buffer length for test buffer */

#define I2C_MASTER_TIMEOUT_MS       1000



/****************************************************************************
 * Function prototypes
 ****************************************************************************/
void init_hardware();