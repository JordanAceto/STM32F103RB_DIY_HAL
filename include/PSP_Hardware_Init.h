/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   PSP_Hardware_Init.h provides an interface for initializing the hardware.
--|  
--|----------------------------------------------------------------------------|
--| REFERENCES:
--|   None.
--|
--|----------------------------------------------------------------------------|
*/

#ifndef PSP_HARDWARE_INIT_H_INCLUDED
#define PSP_HARDWARE_INIT_H_INCLUDED

/*
--|----------------------------------------------------------------------------|
--| INCLUDE FILES
--|----------------------------------------------------------------------------|
*/

/* None */

/*
--|----------------------------------------------------------------------------|
--| PUBLIC DEFINES
--|----------------------------------------------------------------------------|
*/

/*
--| NAME: SYSTEM_CLOCK_SPEED
--| DESCRIPTION: system clock speed is set to 32MHz
--| TYPE: unsigned integer
*/
#define SYSTEM_CLOCK_SPEED 32000000u // TODO: not so sure this is right...

/*
--|----------------------------------------------------------------------------|
--| PUBLIC TYPES
--|----------------------------------------------------------------------------|
*/

/* None */

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
    Hardware_Init

Function Description:
    Initialize the hardware. 

    Sets the system timer to the SYSTEM_CLOCK_SPEED.

    Sets up the SysTick timer to count ticks in milliseconds.

    Initializes various GPIO pins.

Parameters:
    None

Returns:
    None

Assumptions/Limitations:
    This function is to be called before entering the main loop.
------------------------------------------------------------------------------*/
void Hardware_Init(void);

#endif
