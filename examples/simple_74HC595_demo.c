/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   simple_74HC595_demo.c provides a simple demo of a 74HC595. A HDSP-7503
--|   7-segment display counts up numbers 0 - 9 in an endless loop.
--|
--|----------------------------------------------------------------------------|
--| REFERENCES:
--|   sn74hc595.pdf
--|   av02-2553en_ds_hdsp-740x_2015-10-09-1828105.pdf
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
#include "BSP_SN74HC595.h"
#include "PSP_SysTick.h"

/*
--|----------------------------------------------------------------------------|
--| DEFINES
--|----------------------------------------------------------------------------|
*/

/*
--| NAME: UPDATE_TIME_mSec
--| DESCRIPTION: the update period for the demo.
--| TYPE: uint32_t
*/
#define UPDATE_TIME_mSec (500u)

/*
--| NAME: DATA_PIN_NUMBER
--| DESCRIPTION: the pin number for the data pin
--| TYPE: uint32_t
*/
#define DATA_PIN_NUMBER (8u)

/*
--| NAME: CLOCK_PIN_NUMBER
--| DESCRIPTION: the pin number for the clock pin
--| TYPE: uint32_t
*/
#define CLOCK_PIN_NUMBER (6u)

/*
--| NAME: LATCH_PIN_NUMBER
--| DESCRIPTION: the pin number for the latch pin
--| TYPE: uint32_t
*/
#define LATCH_PIN_NUMBER (5u)

/*
--| NAME: SN74HC595_GPIO_PORT
--| DESCRIPTION: the GPIO port which contains the pins for the 74HC595
--| TYPE: GPIO_Port_t*
*/
#define SN74HC595_GPIO_PORT (GPIO_Port_C)

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

/*
--| NAME: SEVEN_SEGMENT_NUMBERS
--| DESCRIPTION: array of bit patterns for writing numbers 0 - 9 to a HDSP-7503
--|              seven segment display via the SN74HC595
--|              
--|              bit-to-segment mapping: 
--|              0 -> D, 1 -> E, 2 -> DP, 3 -> G, 4 -> C, 5 -> F, 6 -> B, 7 -> A
--| TYPE: uint8_t
*/
const uint8_t SEVEN_SEGMENT_NUMBERS[] = 
{
    0b11110011, // these patterns work for the wiring I have for the quad ADSR project
    0b01010000, // the kooky mapping is to make the board layout easy
    0b11001011,
    0b11011001,
    0b01111000,
    0b10111001,
    0b10111011,
    0b11010000,
    0b11111011,
    0b11111001
};

/*
--|----------------------------------------------------------------------------|
--| VARIABLES
--|----------------------------------------------------------------------------|
*/

/*
--| NAME: periodic_timer
--| DESCRIPTION: periodic timeout timer structure for scheduling
--| TYPE: SysTick_Timeout_Timer_t
*/
SysTick_Timeout_Timer_t periodic_timer;

/*
--| NAME: data_pin
--| DESCRIPTION: the data pin for the 74HC595 demo
--| TYPE: GPIO_Pin_t
*/
GPIO_Pin_t data_pin =
{
    SN74HC595_GPIO_PORT,
    DATA_PIN_NUMBER
};

/*
--| NAME: clock_pin
--| DESCRIPTION: the clock pin for the 74HC595 demo
--| TYPE: GPIO_Pin_t
*/
GPIO_Pin_t clock_pin =
{
    SN74HC595_GPIO_PORT,
    CLOCK_PIN_NUMBER
};

/*
--| NAME: latch_pin
--| DESCRIPTION: the latch pin for the 74HC595 demo
--| TYPE: GPIO_Pin_t
*/
GPIO_Pin_t latch_pin =
{
    SN74HC595_GPIO_PORT,
    LATCH_PIN_NUMBER
};

/*
--| NAME: SN74HC595
--| DESCRIPTION: the SN74HC595 to use for the demo
--| TYPE: BSP_74HC595_t
*/
BSP_SN74HC595_t SN74HC595 =
{
    &data_pin,
    &clock_pin,
    &latch_pin
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
    main application function. 

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
    // enable the clock control for GPIO port C
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN_FLAG;

    BSP_SN74HC595_Init(&SN74HC595);

    periodic_timer.timeout_period_mSec = UPDATE_TIME_mSec;
    SysTick_Start_Timeout_Timer(&periodic_timer);

    uint8_t value_to_write = 0u;

    while (1)
    {
        if (SysTick_Poll_Periodic_Timer(&periodic_timer))
		{
			BSP_SN74HC595_Write(&SN74HC595, SEVEN_SEGMENT_NUMBERS[value_to_write % 10]);

            ++value_to_write;
		}
    }

    // never reached
    return 0;
}
