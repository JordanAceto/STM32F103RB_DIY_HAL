/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   PSP_System_Clock_Init.h provides an interface for initializing the RCC
--|   and SysTick peripherals.
--|  
--|----------------------------------------------------------------------------|
--| REFERENCES:
--|   None.
--|
--|----------------------------------------------------------------------------|
*/

#ifndef PSP_SYSTEM_CLOCK_INIT_H_INCLUDED
#define PSP_SYSTEM_CLOCK_INIT_H_INCLUDED

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
#define SYSTEM_CLOCK_SPEED (32000000u) // TODO: not so sure this is right...

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
    System_Clock_Init

Function Description:
    Initialize the RCC and SysTick registers. 

    Sets the system timer to the SYSTEM_CLOCK_SPEED.

    Sets up the SysTick timer to count ticks in milliseconds.

Parameters:
    None

Returns:
    None

Assumptions/Limitations:
    This function is automatically called by the assembly startup routine prior
    to branching to the main c application.
------------------------------------------------------------------------------*/
void System_Clock_Init(void);

#endif
