/** @file dio.c
 *  @brief The implementation for the dio.
 */

/************************************************************************
 * Includes
 ***********************************************************************/
#include "dio.h"                     /* For this module definitions */
#include <xxx.h>                     /* For Hardware definitions */

/************************************************************************
 * Module Preprocessor Constants
 ***********************************************************************/

/************************************************************************
 * Module Preprocessor Macros
 ***********************************************************************/

/************************************************************************
 * Module Typedefs
 ***********************************************************************/

/************************************************************************
 * Module Variable Definitions
 ***********************************************************************/
/**
 * Defines a table of pointers to the peripheral input register on the
 * microcontroller.
 */
static TYPE volatile * const DataIn[NUM_PORTS] =
{
    (TYPE*)&REGISTER1, (TYPE*)&REGISTER2,
};

/**
 * Defines a table of pointers to the peripheral data direction register
 * on the microcontroller.
 */
static TYPE volatile * const DataDirection[NUM_PORTS] =
{
    (TYPE*)&REGISTER1, (TYPE*)&REGISTER2,
};

/**
 * Defines a table of pointers to the peripheral latch register on the
 * microcontroller.
 */
static TYPE volatile * const DataOut[NUM_PORTS] =
{
    (TYPE*)&REGISTER1, (TYPE*)&REGISTER2,
};

/**
 * Defines a table of pointers to the peripheral resistor enable register
 * on the microcontroller.
 */
static TYPE volatile * const Resistor[NUM_PORTS] =
{
    (TYPE*)&REGISTER1, (TYPE*)&REGISTER2,
};

/**
 * Defines a table of pointers to the port's function select register
 * on the microcontroller.
 */
static TYPE volatile * const Function[NUM_PORTS] =
{
    (TYPE*)&REGISTER1, (TYPE*)&REGISTER2,
};

/************************************************************************
 * Function Prototypes
 ***********************************************************************/

/************************************************************************
 * Function Definitions
 ***********************************************************************/ 

/************************************************************************
 * Function : Dio_Init()
 * 
 * \b Description:
 * 
 * This function is used to initialize the Dio based on the configuration
 * table defined in dio_cfg module.
 * 
 * PRE-CONDITION: Configuration table needs to be populated (sizeof > 0) <br>
 * PRE-CONDITION: NUMBER_OF_CHANNELS_PER_PORT > 0 <br>
 * PRE-CONDITION: NUMBER_OF_PORTS > 0 <br>
 * PRE-CONDITION: The MCU clocks must be configured and enabled.
 * 
 * POST-CONDITION: The DIO peripheral is set up with the configuration
 * settings.
 * 
 * @param          Config is a pointer to the configuration table that
 *                 contains the initialization for the peripheral.
 * 
 * @return         void
 * 
 * \b Example:
 * @code
 * const Dio_Config_t *DioConfig = DioConfigGet();
 * 
 * Dio_Init(DioConfig);
 * @endcode
 * 
 * @see Dio_Init
 * @see Dio_ChannelRead
 * @see Dio_ChannelWrite
 * @see Dio_ChannelToggle
 * @see Dio_RegisterWrite
 * @see Dio_RegisterRead
 * @see Dio_CallbackRegister
 * 
 ***********************************************************************/
void Dio_Init(const Dio_Config_t * Config)
{
    /* TODO: Define implementation */
}

/************************************************************************
 * Function : Dio_ChannelRead()
 * 
 * \b Description:
 * 
 * This function is used to read the state of a dio channel (pin)
 * 
 * PRE-CONDITION: The channel is configured as INPUT <br>
 * PRE-CONDITION: The channel is configured as GPIO <br>
 * PRE-CONDITION: The channel is within the maximum DioChannel_t
 * definition
 * 
 * POST-CONDITION: The channel state is returned.
 * 
 * @param          Channel is the DioChannel_t that represents a pin
 * 
 * @return         The state of the channel as HIGH or LOW
 * 
 * \b Example:
 * @code
 *   uint8_t pin = Dio_ReadChannel(PORT1_0);
 * @endcode
 * 
 * @see Dio_Init
 * @see Dio_ChannelRead
 * @see Dio_ChannelWrite
 * @see Dio_ChannelToggle
 * @see Dio_RegisterWrite
 * @see Dio_RegisterRead
 * @see Dio_CallbackRegister
 * 
 ***********************************************************************/
DioPinState_t Dio_ChannelRead(DioChannel_t Channel)
{

}

 /************************************************************************
 * Function : Dio_ChannelWrite()
 * 
 * \b Description:
 * 
 * This function is used to write the state of a channel (pin) as either
 * logic high or low through the use of DioChannel_t enum to select
 * the channel and the DioPinState_t to define the desired state.
 * 
 * PRE-CONDITION: The channel is configured as OUTPUT <br>
 * PRE-CONDITION: The channel is configured as GPIO <br>
 * PRE-CONDITION: The channel is within the maximum DioChannel_t
 * definition
 * 
 * POST-CONDITION: The channel state will be state.
 * 
 * @param          Channel is the pin to write using the DioChannel_t 
 *                 enum definition
 * @param          State is HIGH or LOW as defined in the 
 *                 DioPinState_t enum
 * 
 * @return         void
 * 
 * \b Example:
 * @code
 *   Dio_WriteChannel(PORT1_0, LOW);    // Set the PORT1_0 pin low
 *   Dio_WriteChannel(PORT1_0, HIGH);   // Set the PORT1_0 pin high
 * @endcode
 * 
 * @see Dio_Init
 * @see Dio_ChannelRead
 * @see Dio_ChannelWrite
 * @see Dio_ChannelToggle
 * @see Dio_RegisterWrite
 * @see Dio_RegisterRead
 * @see Dio_CallbackRegister
 * 
 ***********************************************************************/
void Dio_ChannelWrite(DioChannel_t Channel, DioPinState_t State)
{
    
}

 /************************************************************************
 * Function : Dio_ChannelToggle()
 * 
 * \b Description:
 * 
 * This function is used to toggle the current state of a channel (pin).
 * 
 * PRE-CONDITION: The channel is configured as OUTPUT <br>
 * PRE-CONDITION: The channel is configured as GPIO <br>
 * PRE-CONDITION: The channel is within the maximum DioChannel_t
 * definition
 * 
 * POST-CONDITION:
 * 
 * @param          Channel is the pin from the DioChannel_t that is 
 *                 to be modified
 * 
 * @return         void
 * 
 * \b Example:
 * @code
 *   Dio_ChannelToggle(PORT1_0);        // Toggle the PORT1_0 pin
 * @endcode
 * 
 * @see Dio_Init
 * @see Dio_ChannelRead
 * @see Dio_ChannelWrite
 * @see Dio_ChannelToggle
 * @see Dio_RegisterWrite
 * @see Dio_RegisterRead
 * @see Dio_CallbackRegister
 * 
 ***********************************************************************/
void Dio_ChannelToggle(DioChannel_t Channel)
{
    
}

 /************************************************************************
 * Function : Dio_RegisterWrite()
 * 
 * \b Description:
 * 
 * This function is used to directly address and modify a Dio register.
 * The function should be used to access specialized functionality in the
 * Dio peripheral that is not exposed by any other function of the
 * interface.
 * 
 * PRE-CONDITION: Address is within the boundaries of the Dio register
 * address space
 * 
 * POST-CONDITION: The register located at Address will be updated with
 * value
 * 
 * @param          Address is a register address within the Dio
 *                 peripheral map
 * @param          Value is the value to set the Dio register to
 * 
 * @return         void
 * 
 * \b Example:
 * @code
 *   Dio_RegisterWrite(0x1000, 0x15);
 * @endcode
 * 
 * @see Dio_Init
 * @see Dio_ChannelRead
 * @see Dio_ChannelWrite
 * @see Dio_ChannelToggle
 * @see Dio_RegisterWrite
 * @see Dio_RegisterRead
 * @see Dio_CallbackRegister
 * 
 ***********************************************************************/
void Dio_RegisterWrite(uint_32_t Address, TYPE Value)
{
    
}

 /************************************************************************
 * Function : Dio_RegisterRead()
 * 
 * \b Description:
 * 
 * This function is used to directly address a Dio register. The function
 * should be used to access specialized functionality in the Dio
 * peripheral that is not exposed by any other function of the interface.
 * 
 * PRE-CONDITION: Address is within the boundaries of the Dio register
 * address space
 * 
 * POST-CONDITION: The value stored in the register is returned to the
 * caller
 * 
 * @param          Address is the address of the Dio register to read
 * 
 * @return         The current value of the Dio register.
 * 
 * \b Example:
 * @code
 *   DioValue = Dio_RegisterRead(0x1000);
 * @endcode
 * 
 * @see Dio_Init
 * @see Dio_ChannelRead
 * @see Dio_ChannelWrite
 * @see Dio_ChannelToggle
 * @see Dio_RegisterWrite
 * @see Dio_RegisterRead
 * @see Dio_CallbackRegister
 * 
 ***********************************************************************/
TYPE Dio_RegisterRead(uint_32_t Address)
{
    
}

 /************************************************************************
 * Function : Dio_CallbackRegister()
 * 
 * \b Description:
 * 
 * This function is used to set the callback functions of the dio driver.
 * By default, the callbacks are initialized to a NULL pointer. The driver
 * may contain more than one possible callback, so the function will take
 * a parameter to configure the specified callback.
 * 
 * PRE-CONDITION: The DioCallback_t has been populated.
 * PRE-CONDITION: The callback function exists within memory.
 * 
 * POST-CONDITION: The specified callback function will be registered
 * with the driver.
 * 
 * @param          Function is the callback function that will be registered
 * @param          CallbackFunction is a function pointer to the desired
 *                 function
 * 
 * @return         None.
 * 
 * \b Example:
 * @code
 *   DioCallback_t Dio_Function = DIO_SAMPLE_COMPLETE;
 *   Dio_CallbackRegister(Dio_Function, DioSampleAverage);
 * @endcode
 * 
 * @see Dio_Init
 * @see Dio_ChannelRead
 * @see Dio_ChannelWrite
 * @see Dio_ChannelToggle
 * @see Dio_RegisterWrite
 * @see Dio_RegisterRead
 * @see Dio_CallbackRegister
 * 
 ***********************************************************************/
void1 Dio_CallbackRegister(DioCallback_t Function,
TYPE (*CallbackFunction)(type))
{
    
}

/**************** END OF FUNCTIONS *************************************/