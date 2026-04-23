/** @file dio_cfg.h
 *  @brief This module contains interface definitions for the
 * Dio configuration. This is the header file for the definition of the
 * interface for retrieving the digital input/output configuration table.
 */
#pragma once

/************************************************************************
 * Includes
 ***********************************************************************/

/************************************************************************
 * Preprocessor Constants
 ***********************************************************************/

/**
 * Defines the number of pins on each processor port.
 */
#define NUMBER_OF_CHANNELS_PER_PORT         8U

/**
 * Defines the number of ports on the processor.
 */
#define NUMBER_OF_PORTS                     2U

/************************************************************************
 * Typedefs
 ***********************************************************************/
/**
 * Defines the possible states for a digital output pin.
 */
typedef enum
{
    DIO_LOW,                          /** Defines digital state ground */
    DIO_HIGH,                         /** Defines ditigal state power */
    DIO_PIN_STATE_MAX                 /** Defines the maximum digital 
    state */
}DioPinState_t;

/**
 * Defines an enumerated list of all the channels (pins) on the MCU 
 * device. The last element is used to specify the maximum number of
 * enumerated labels.
 */
typedef enum
{
    /* TODO: Populate this list based on available MCU pins */
    FCPU_HB,                   /**< PORT1_0 */
    PORT1_1,                   /**< PORT1_1 */
    PORT1_2,                   /**< PORT1_2 */
    PORT1_3,                   /**< PORT1_3 */
    UHF_SEL,                   /**< PORT1_4 */
    PORT1_5,                   /**< PORT1_5 */
    PORT1_6,                   /**< PORT1_6 */
    PORT1_7,                   /**< PORT1_7 */
    DIO_MAX_PIN_NUMBER    /**< MAX CHANNELS */
}DioChannel_t;

/**
 * Defines the possible DIO pin multiplexing values. The datasheet
 * should be reviewd for proper muxing options.
 */
typedef enum
{
    /* TODO: Populate with possible mode options*/
    DIO_MAX_MODE
}DioMode_t;

/**
 * Defines the possible directions of all the channels (pins)
 */
typedef enum
{
    DIO_OUTPUT,              /*< Used to set pin as output */
    DIO_INPUT,               /*< Used to set pin as input */
}DioDirection_t;


/**
 * Defines the possible states of the channel pull-ups
 */
typedef enum
{
    DIO_PULLUP_DISABLED,     /*< Used to disable the internal pull-ups */
    DIO_PULLUP_ENABLED,      /*< Used to enable the internal pull-ups */
    DIO_MAX_RESISTOR         /*< Resistor states should be below this value */
}DioResistor_t;

/**
 * Defines the digital input/output configuration table's elements that are 
 * used by Dio_Init to configure the Dio peripheral.
 */
typedef struct
{
    /* TODO: Add additional members for the MCU peripheral             */
    DioChannel_t Channel;          /**< The I/O pin                    */
    DioResistor_t Resistor;        /**< ENABLED or DISABLED            */
    DioDirection_t Direction;      /**< OUTPUT or INPUT                */
    DioPinState_t Data;            /**< HIGH or LOW                    */
    DioMode_t Function;            /**< Mux Function - Dio_Peri_Select */
}DioConfig_t;

/**
 * Defines the slew rate settings available
 */
typedef enum
{
    FAST,    /**< Fast slew rate is configured on the corresponding pin */
    SLOW     /**< Slow slew rate is configured on the corresponding pin */
}DioSlew_t;

/************************************************************************
 * Function Prototypes
 ***********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

const DioConfig_t * const Dio_ConfigGet(void);

#ifdef __cplusplus
} // extern "C"
#endif

/***End of File*********************************************************/