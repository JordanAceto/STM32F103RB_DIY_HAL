/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   simple_blink.c provides a simple demo which blinks the onboard LED using
--|   the SysTick timer.
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
#include "PSP_SysTick.h"
#include "PSP_Hardware_Init.h"

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
#define LED_BLINK_TIME_mSec (1000u)

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
GPIO_Pin_t LED_pin;

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
    Hardware_Init();

    periodic_timer.timeout_period_mSec = LED_BLINK_TIME_mSec;

    SysTick_Start_Timeout_Timer(&periodic_timer);

    LED_pin.number = LED_PIN_NUMBER;
    LED_pin.port = LED_GPIO_PORT;

    // write the pin high right away, so you see the LED light up immediately
    PSP_GPIO_Write_Pin(&LED_pin, GPIO_PIN_OUTPUT_WRITE_HIGH);

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
