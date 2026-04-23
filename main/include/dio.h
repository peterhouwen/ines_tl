/** @file dio.h
 *  @brief The interface definition for the dio.
 * 
 * This is the header file for the definition of the interface for a
 * digital input/output peripheral on a standard microcontroller.
 */
#pragma once

/************************************************************************
 * Includes
 ***********************************************************************/
#include <stdint.h>          /* For standard type definitions */
#include "dio_cfg.h"         /* For dio configuration */
#include "constants.h"       /* For HIGH, LOW, etc */

/************************************************************************
 * Preprocessor Constants
 ***********************************************************************/

/************************************************************************
 * Configuration Constants
 ***********************************************************************/

/************************************************************************
 * Macros
 ***********************************************************************/

/************************************************************************
 * Typedefs
 ***********************************************************************/

/************************************************************************
 * Variables
 ***********************************************************************/

/************************************************************************
 * Function Prototypes
 ***********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

void Dio_Init(const DioConfig_t * const Config);
DioPinState_t Dio_ChannelRead(DioChannel_t Channel);
void Dio_ChannelWrite(DioChannel_t Channel, DioPinState_t State);
void Dio_ChannelToggle(DioChannel_t Channel);
void Dio_RegisterWrite(uint32_t Address, TYPE Value);
TYPE Dio_RegisterRead(uint32_t Address);
void Dio_CallbackRegister(DioCallback_t Function, TYPE (*CallbackFunction)(type));

#ifdef __cplusplus
} // extern "C"
#endif

/***End of File*********************************************************/