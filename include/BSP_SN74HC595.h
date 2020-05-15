/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   BSP_74HC595.h provides types and interfaces for using SN74HC595 8 bit
--|   shift register integrated circuits.
--|   
--|----------------------------------------------------------------------------|
--| REFERENCES:
--|   sn74hc595.pdf
--|
--|----------------------------------------------------------------------------|
*/

#ifndef BSP_SN74HC595_H_INCLUDED
#define BSP_SN74HC595_H_INCLUDED

/*
--|----------------------------------------------------------------------------|
--| INCLUDE FILES
--|----------------------------------------------------------------------------|
*/

#include <stdint.h>
#include "PSP_GPIO.h"

/*
--|----------------------------------------------------------------------------|
--| PUBLIC DEFINES
--|----------------------------------------------------------------------------|
*/

/* None */

/*
--|----------------------------------------------------------------------------|
--| PUBLIC TYPES
--|----------------------------------------------------------------------------|
*/

/*
--| NAME: BSP_SN74HC595_t
--| DESCRIPTION: structure for a SN74HC595 8 bit shift register integrated circuit.
*/
typedef struct BSP_SN74HC595_Type
{
    GPIO_Pin_t * p_SER_pin;   // pointer to the data pin
    GPIO_Pin_t * p_SRCLK_pin; // pointer to the clock pin
    GPIO_Pin_t * p_RCLK_pin;  // pointer to the latch pin
} BSP_SN74HC595_t;

/*
--|----------------------------------------------------------------------------|
--| PUBLIC CONSTANTS
--|----------------------------------------------------------------------------|
*/

/* None */

/*
--|----------------------------------------------------------------------------|
--| PUBLIC VARIABLES
--|----------------------------------------------------------------------------|
*/

/* None */

/*
--|----------------------------------------------------------------------------|
--| PUBLIC FUNCTION PROTOTYPES
--|----------------------------------------------------------------------------|
*/

/*------------------------------------------------------------------------------
Function Name:
    BSP_SN74HC595_Init

Function Description:
    Initialize the given SN74HC595. Sets the data, clock, and latch pins
    to outputs and writes the initial pin levels.

Parameters:
    p_SN74HC595: pointer to the SN74HC595 pin to initialize.

Returns:
    None

Assumptions/Limitations:
    Assumes that the given SN74HC595 has valid data, clock, and latch pins.
------------------------------------------------------------------------------*/
void BSP_SN74HC595_Init(BSP_SN74HC595_t * p_SN74HC595);

/*------------------------------------------------------------------------------
Function Name:
    BSP_SN74HC595_Write

Function Description:
    Write the given 8 bit value to the given SN74HC595 integrated circuit, 
    msb first. 

Parameters:
    p_SN74HC595: pointer to the SN74HC595 to write to.
    value: the 8 bit value to write.

Returns:
    None

Assumptions/Limitations:
    Assumes that the given 74HC595 has been initialized.
------------------------------------------------------------------------------*/
void BSP_SN74HC595_Write(BSP_SN74HC595_t * p_SN74HC595, uint8_t value);

#endif
