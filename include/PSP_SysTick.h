/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   PSP_SysTick.h provides types and interfaces for the Core SysTick Timer,
--|   as well as various scheduling and time based functionality.
--|   
--|----------------------------------------------------------------------------|
--| REFERENCES:
--|   PM0056 programming manual, page 150
--|
--|----------------------------------------------------------------------------|
*/

#ifndef PSP_SYSTICK_H_INCLUDED
#define PSP_SYSTICK_H_INCLUDED

/*
--|----------------------------------------------------------------------------|
--| INCLUDE FILES
--|----------------------------------------------------------------------------|
*/

#include "Common_Typedefs.h"
#include "PSP_Peripherals_Memory_Map.h"

/*
--|----------------------------------------------------------------------------|
--| PUBLIC DEFINES
--|----------------------------------------------------------------------------|
*/

/*
--| NAME: SysTick 
--| DESCRIPTION: pointer to the SysTick 24 bit counter
--| TYPE: SysTick_t*
*/
#define SysTick ((volatile SysTick_t *)PSP_CORE_PERIPHERAL_STK_BASE)

/*
--|----------------------------------------------------------------------------|
--| PUBLIC TYPES
--|----------------------------------------------------------------------------|
*/

/*
--| NAME: SysTick_t
--| DESCRIPTION: core SysTick 24 bit counter structure
*/
typedef struct SysTick_Type
{
    vuint32_t CTRL;  // control and status register [four 1 bit flags]
    vuint32_t LOAD;  // reload value register [24 bits]
    vuint32_t VAL;   // current value register [24 bits]
    vuint32_t CALIB; // calibration value register [24 bits plus two 1 bit flags] 
} SysTick_t;

/*
--| NAME: SysTick_CTRL_FLAGS_enum
--| DESCRIPTION: SysTick control and status register flags
*/
typedef enum SysTick_CTRL_FLAGS_Enumeration
{
    SysTick_CTRL_COUNT_FLAG     = (1u << 16u), // 1 if timer counted to 0 since last read [rw]
    SysTick_CTRL_CLKSOURCE_FLAG = (1u << 2u),  // 0: AHB/8, 1: Processor clock (AHB) [rw]
    SysTick_CTRL_TICKINT_FLAG   = (1u << 1u),  // SysTick exception request enable [rw]
    SysTick_CTRL_ENABLE_FLAG    = (1u << 0u),  // Counter enable [rw]
} SysTick_CTRL_FLAGS_enum;

/*
--| NAME: SysTick_Periodic_Timer_t
--| DESCRIPTION: structure for periodic timer storage
*/
typedef struct SysTick_Periodic_Timer_Type
{
    uint32_t timeout_period_mSec;    // the period of the timeout in mSec
    uint32_t last_timeout_time_mSec; // the time in mSec when the last timeout occured
} SysTick_Periodic_Timer_t;

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
    SysTick_Delay_mSec

Function Description:
    Wait for a given number of milliseconds.

Parameters:
    mSec: the number of milliseconds to wait.

Returns:
    None

Assumptions/Limitations:
    None
------------------------------------------------------------------------------*/
void SysTick_Delay_mSec(uint32_t mSec);

/*------------------------------------------------------------------------------
Function Name:
    SysTick_Get_mSec

Function Description:
    Get the number of milliseconds since the last power on/reset.

Parameters:
    None

Returns:
    uint32_t: the number of milliseconds since reset.

Assumptions/Limitations:
    None
------------------------------------------------------------------------------*/
uint32_t SysTick_Get_mSec(void);

/*------------------------------------------------------------------------------
Function Name:
    SysTick_Initialize_Periodic_Timer

Function Description:
    Initialize a periodic timer before using.

Parameters:
    p_timer: pointer to the periodic timer.

Returns:
    None

Assumptions/Limitations:
    Assumes that the given periodic timer has a valid timeout period.
------------------------------------------------------------------------------*/
void SysTick_Initialize_Periodic_Timer(SysTick_Periodic_Timer_t * p_timer);

/*------------------------------------------------------------------------------
Function Name:
    SysTick_Periodic_Timer_Timeout_Occured

Function Description:
    Poll a given periodic timer and return true if a timeout has occured, 
    otherwise return false.

    If a timeout has occured, the last timeout time in the given periodic 
    timer is set to the time now.

Parameters:
    p_timer: pointer to the periodic timer.

Returns:
    true if a timeout occured, else false.

Assumptions/Limitations:
    Assumes that the data in the given periodic timer is sensible.
------------------------------------------------------------------------------*/
bool SysTick_Periodic_Timer_Timeout_Occured(SysTick_Periodic_Timer_t * p_timer);

#endif
