/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   PSP_Hardware_Init.c provides the implementation for initializing
--|   the RCC and SysTick hardware.
--|   
--|----------------------------------------------------------------------------|
--| REFERENCES:
--|   RCC: stm32f10x reference manual, page 99
--|   SysTick: PM0056 programming manual, page 150
--|----------------------------------------------------------------------------|
*/

/*
--|----------------------------------------------------------------------------|
--| INCLUDE FILES
--|----------------------------------------------------------------------------|
*/

#include "Common_Masks.h"
#include "PSP_RCC.h"
#include "PSP_System_Clock_Init.h"
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

/* None */

/*
--|----------------------------------------------------------------------------|
--| PRIVATE HELPER FUNCTION PROTOTYPES
--|----------------------------------------------------------------------------|
*/

/*------------------------------------------------------------------------------
Function Name:
    RCC_Init

Function Description:
    Perform RCC register Clock initialization 

Parameters:
    None

Returns:
    None

Assumptions/Limitations:
    None
------------------------------------------------------------------------------*/
static void RCC_Init(void);

/*------------------------------------------------------------------------------
Function Name:
    SysTick_Init

Function Description:
    Perform SysTick initialization 

Parameters:
    None

Returns:
    None

Assumptions/Limitations:
    None
------------------------------------------------------------------------------*/
static void SysTick_Init(void);

/*
--|----------------------------------------------------------------------------|
--| PUBLIC FUNCTION DEFINITIONS
--|----------------------------------------------------------------------------|
*/

void System_Clock_Init(void)
{
    RCC_Init();
    SysTick_Init();
}

/*
--|----------------------------------------------------------------------------|
--| PRIVATE HELPER FUNCTION DEFINITIONS
--|----------------------------------------------------------------------------|
*/

static void RCC_Init(void)
{
    // enable the internal high speed clock
    RCC->CR |= RCC_CR_HSION_FLAG;

    while (!(RCC->CR & RCC_CR_HSIRDY_FLAG))
    {
        // wait for the internal clock to be ready
    }

    // set the PLL multiplier
    RCC->CFGR &= ~(FOUR_BIT_MASK << RCC_CFGR_PLLMUL_SHIFT_AMT);
    RCC->CFGR |= RCC_CFGR_PLLMUL_X_8 << RCC_CFGR_PLLMUL_SHIFT_AMT;

    // set the PLL clock source
    RCC->CFGR &= ~RCC_CFGR_PLLSRC_FLAG; // HSI oscillator clock / 2 selected as PLL input clock

    // turn on the PLL
    RCC->CR |= RCC_CR_PLLON_FLAG;

    while (!(RCC->CR & RCC_CR_PLLRDY_FLAG))
    {
        // wait for the PLL to lock
    }

    // set the clock dividers
    RCC->CFGR &= ~(FOUR_BIT_MASK << RCC_CFGR_HPRE_SHIFT_AMT);
    RCC->CFGR |= RCC_CFGR_HPRE_NO_DIVIDE << RCC_CFGR_HPRE_SHIFT_AMT;

    RCC->CFGR &= ~(THREE_BIT_MASK << RCC_CFGR_PPRE2_SHIFT_AMT);
    RCC->CFGR |= RCC_CFGR_PPRE2_NO_DIVIDE << RCC_CFGR_PPRE2_SHIFT_AMT;

    // select the PLL as the system clock
    RCC->CFGR &= ~(TWO_BIT_MASK << RCC_CFGR_SW_SHIFT_AMT);
    RCC->CFGR |= RCC_CFGR_SW_PLL << RCC_CFGR_SW_SHIFT_AMT;

    while (!(RCC->CFGR & (RCC_CFGR_SWS_PLL << RCC_CFGR_SWS_SHIFT_AMT)))
    {
        // wait for the setting to take hold
    }
}

static void SysTick_Init(void)
{
    // set the load register such that the systick timer rolls over every 1mSec
    SysTick->LOAD = (SYSTEM_CLOCK_SPEED / 1000u) - 1u; 
    
    // clear the current value
    SysTick->VAL = 0u;
    
    // set the clocksource to undivided processor clock (AHB)
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_FLAG;

    // enable exception requests
    SysTick->CTRL |= SysTick_CTRL_TICKINT_FLAG;

    // enable the SysTick counter
    SysTick->CTRL |= SysTick_CTRL_ENABLE_FLAG;
}
