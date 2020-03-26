/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   PSP_SysTick.h provides the implementation for SysTick related functions,
--|   and implements the SysTick_handler interrupt routine.
--|   
--|----------------------------------------------------------------------------|
--| REFERENCES:
--|   PM0056 programming manual, page 150
--|
--|----------------------------------------------------------------------------|
*/

/*
--|----------------------------------------------------------------------------|
--| INCLUDE FILES
--|----------------------------------------------------------------------------|
*/

#include "PSP_SysTick.h"

/*
--|----------------------------------------------------------------------------|
--| PRIVATE DEFINES
--|----------------------------------------------------------------------------|
*/

/* None */

/*
--|----------------------------------------------------------------------------|
--| PRIVATE TYPES
--|----------------------------------------------------------------------------|
*/

/* None */

/*
--|----------------------------------------------------------------------------|
--| PRIVATE CONSTANTS
--|----------------------------------------------------------------------------|
*/

/* None */

/*
--|----------------------------------------------------------------------------|
--| PRIVATE VARIABLES
--|----------------------------------------------------------------------------|
*/

/*
--| NAME: mSec_since_reset 
--| DESCRIPTION: the number of milliseconds since the last power on/reset.
--| TYPE: uint64_t
*/
static volatile uint32_t mSec_since_reset = 0u;

/*
--|----------------------------------------------------------------------------|
--| PRIVATE HELPER FUNCTION PROTOTYPES
--|----------------------------------------------------------------------------|
*/

/*------------------------------------------------------------------------------
Function Name:
    Systick_handler

Function Description:
    Interrupt routine for periodic Systick interrupts. Simply increments the
    mSec_since_reset variable.

Parameters:
    None

Returns:
    None

Assumptions/Limitations:
    None
------------------------------------------------------------------------------*/
void SysTick_handler(void);

/*
--|----------------------------------------------------------------------------|
--| PUBLIC FUNCTION DEFINITIONS
--|----------------------------------------------------------------------------|
*/

void SysTick_Delay_mSec(uint32_t mSec)
{
    const uint32_t start_time = SysTick_Get_mSec();

    while ((SysTick_Get_mSec() - start_time) <= mSec)
    {
        // wait
    }
}

uint64_t SysTick_Get_mSec(void)
{
    return mSec_since_reset;
}

void SysTick_Initialize_Periodic_Timer(SysTick_Periodic_Timer_t * p_timer)
{
    p_timer->last_timeout_time_mSec = SysTick_Get_mSec();
}

bool SysTick_Periodic_Timer_Timeout_Occured(SysTick_Periodic_Timer_t * p_timer)
{
    bool retval = false;

    if ((SysTick_Get_mSec() - p_timer->last_timeout_time_mSec) > p_timer->timeout_period_mSec) 
    {
        p_timer->last_timeout_time_mSec = SysTick_Get_mSec();
        retval = true;
    }

    return retval;
}

/*
--|----------------------------------------------------------------------------|
--| PRIVATE HELPER FUNCTION DEFINITIONS
--|----------------------------------------------------------------------------|
*/

void SysTick_handler(void)
{
    mSec_since_reset++;
}
