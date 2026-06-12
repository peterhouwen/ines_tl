/** @file types.h
 *  @brief The definition of types
 * 
 *  This is the header file for definition of types.
 */
#pragma once

typedef enum {
    STOP,
    PREPARE,
    GO,
    SLOW
} t_state_machine_A;

typedef enum {
    HALT,
    WALK,
    HURRY
} t_state_machine_B;


/***End of File**************************************************************/