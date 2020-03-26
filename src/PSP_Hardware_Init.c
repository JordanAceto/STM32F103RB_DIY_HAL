/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   PSP_Hardware_Init.c provides the implementation for initializing
--|   the hardware.
--|   
--|----------------------------------------------------------------------------|
--| REFERENCES:
--|   None.
--|
--|----------------------------------------------------------------------------|
*/

/*
--|----------------------------------------------------------------------------|
--| INCLUDE FILES
--|----------------------------------------------------------------------------|
*/

#include "Common_Masks.h"
#include "PSP_GPIO.h"
#include "PSP_Hardware_Init.h"
#include "PSP_RCC.h"
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
    Clock_Init

Function Description:
    Perform Clock initialization 

Parameters:
    None

Returns:
    None

Assumptions/Limitations:
    None
------------------------------------------------------------------------------*/
static void Clock_Init(void);

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

/*------------------------------------------------------------------------------
Function Name:
    GPIO_Init

Function Description:
    Perform GPIO initialization 

Parameters:
    None

Returns:
    None

Assumptions/Limitations:
    None
------------------------------------------------------------------------------*/
static void GPIO_Init(void);

/*
--|----------------------------------------------------------------------------|
--| PUBLIC FUNCTION DEFINITIONS
--|----------------------------------------------------------------------------|
*/

void Hardware_Init(void)
{
    Clock_Init();
    SysTick_Init();
    GPIO_Init();
}

/*
--|----------------------------------------------------------------------------|
--| PRIVATE HELPER FUNCTION DEFINITIONS
--|----------------------------------------------------------------------------|
*/

static void Clock_Init(void)
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

static void GPIO_Init(void)
{
    // enable the clock control for port A
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN_FLAG;

    GPIO_Pin_t LED_pin;
    LED_pin.number = 5u;
    LED_pin.port = GPIO_Port_A;

    // set the led pin as ouput
    GPIO_Pin_Initialization_Data_t init_data = {0};
    init_data.CNFy         = GPIO_PIN_CNFy_GENERAL_PURPOSE_OUTPUT_PUSH_PULL;
    init_data.MODEy        = GPIO_PIN_MODEy_OUTPUT_10MHz_MAX;
    init_data.pull_up_down = GPIO_PIN_NO_PULL_UP_OR_DOWN;
    PSP_GPIO_Set_Pin_Mode(&LED_pin, &init_data);
}
