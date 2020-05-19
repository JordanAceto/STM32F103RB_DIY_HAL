/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   simple_sysTick_blink.c provides a simple demo which blinks the onboard LED 
--|   using the SysTick timer.
--|  
--|   Following this example should give you an idea of how to use the SysTick
--|   timer and basic GPIO pin writing.
--|  
--|   On the NUCLEO-F103RB, the onboard LED is port A, pin 5.
--|   If using a different board, or to attach an LED to a different pin for 
--|   experimentation, change the definitions for the LED pin number and GPIO 
--|   port as needed.
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

#include "PSP_GPIO.h"
#include "PSP_RCC.h"
#include "PSP_SysTick.h"

/*
--|----------------------------------------------------------------------------|
--| DEFINES
--|----------------------------------------------------------------------------|
*/

/*
--| NAME: LED_BLINK_TIME_mSec
--| DESCRIPTION: blink time for the onboard LED in milliseconds
--| TYPE: uint32_t
*/
#define LED_BLINK_TIME_mSec (100u)

/*
--| NAME: LED_PIN_NUMBER
--| DESCRIPTION: the pin number for the onboard LED
--| TYPE: uint32_t
*/
#define LED_PIN_NUMBER (5u)

/*
--| NAME: LED_GPIO_PORT
--| DESCRIPTION: the GPIO port which contains the onboard LED pin
--| TYPE: GPIO_Port_t*
*/
#define LED_GPIO_PORT (GPIO_Port_A)

/*
--|----------------------------------------------------------------------------|
--| TYPES
--|----------------------------------------------------------------------------|
*/

/* None */

/*
--|----------------------------------------------------------------------------|
--| CONSTANTS
--|----------------------------------------------------------------------------|
*/

/* None */

/*
--|----------------------------------------------------------------------------|
--| VARIABLES
--|----------------------------------------------------------------------------|
*/

/*
--| NAME: periodic_timer
--| DESCRIPTION: periodic timeout timer structure for scheduling the LED blink
--| TYPE: SysTick_Timeout_Timer_t
*/
SysTick_Timeout_Timer_t periodic_timer;

/*
--| NAME: LED_pin
--| DESCRIPTION: GPIO pin structure for blinking the LED
--| TYPE: GPIO_Pin_t
*/
GPIO_Pin_t LED_pin =
{
    LED_GPIO_PORT,
    LED_PIN_NUMBER
};

/*
--| NAME: LED_pin_init_data
--| DESCRIPTION: initialization data for the LED pin
--| TYPE: GPIO_Pin_Initialization_Data_t
*/
GPIO_Pin_Initialization_Data_t LED_pin_init_data = 
{
    GPIO_PIN_CNFy_GENERAL_PURPOSE_OUTPUT_PUSH_PULL,
    GPIO_PIN_MODEy_OUTPUT_10MHz_MAX,
    GPIO_PIN_NO_PULL_UP_OR_DOWN
};

/*
--|----------------------------------------------------------------------------|
--| FUNCTION PROTOTYPES
--|----------------------------------------------------------------------------|
*/

/*------------------------------------------------------------------------------
Function Name:
    main

Function Description:
    main application function which blinks the onboard LED in an endless loop. 

Parameters:
    None

Returns:
    int [return is never reached]

Assumptions/Limitations:
    None
------------------------------------------------------------------------------*/
int main(void);

/*
--|----------------------------------------------------------------------------|
--| FUNCTION DEFINITIONS
--|----------------------------------------------------------------------------|
*/

int main(void)
{
    // enable the clock control for GPIO port A
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN_FLAG;

    // set the led pin as ouput    
    PSP_GPIO_Set_Pin_Mode(&LED_pin, &LED_pin_init_data);

    // write the pin high right away, so you see the LED light up immediately
    PSP_GPIO_Write_Pin(&LED_pin, GPIO_PIN_OUTPUT_WRITE_HIGH);

    periodic_timer.timeout_period_mSec = LED_BLINK_TIME_mSec;

    SysTick_Start_Timeout_Timer(&periodic_timer);
    
    while (1)
    {
        if (SysTick_Poll_Periodic_Timer(&periodic_timer))
		{
			PSP_GPIO_Toggle_Pin(&LED_pin);
		}
    }

    // never reached
    return 0;
}
