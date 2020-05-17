/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   BSP_MCP4822.h provides types and functions for interfacing with MCP4822
--|   12-bit SPI DACs.
--|   
--|----------------------------------------------------------------------------|
--| REFERENCES:
--|   mcp4822_datasheet.pdf
--|
--|----------------------------------------------------------------------------|
*/

#ifndef BSP_MCP4822_H_INCLUDED
#define BSP_MCP4822_H_INCLUDED

/*
--|----------------------------------------------------------------------------|
--| INCLUDE FILES
--|----------------------------------------------------------------------------|
*/

#include "Common_Typedefs.h"
#include "PSP_SPI.h"

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
--| NAME: MCP4822_Channel_enum
--| DESCRIPTION: enumeration for MCP4822 channel
*/
typedef enum MCP4822_Channel_Enumeration
{
    MCP4822_CHANNEL_A = 0u,
    MCP4822_CHANNEL_B = 1u
} MCP4822_Channel_enum;

/*
--| NAME: MCP4822_Gain_enum
--| DESCRIPTION: enumeration for MCP4822 gain
*/
typedef enum MCP4822_Gain_Enumeration
{
    MCP4822_GAIN_2x = 0u,
    MCP4822_GAIN_1x = 1u
} MCP4822_Gain_enum;

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
    MCP4822_Write

Function Description:
    Write the given 12 bit signal to a MCP4822 DAC via the given SPI handle. 

Parameters:
    p_SPI_handle: pointer to the SPI handle to use
    channel: the MCP4822 channel to write to, A or B
    gain: the gain to use, 1x or 2x (2x will cause cliping in a 3.3v system)
    value_12_bits: the 12 bit value to write (bits higher than 12 are discarded)

Returns:
    None

Assumptions/Limitations:
    Assumes that the given SPI handle is configured for MSB first transfers.
------------------------------------------------------------------------------*/
void MCP4822_Write(SPI_Transaction_Handle_t * p_SPI_handle,
                   MCP4822_Channel_enum channel,
                   MCP4822_Gain_enum gain,
                   uint32_t value_12_bits);

#endif
