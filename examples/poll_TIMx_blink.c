/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   poll_TIMx_blink.c provides a simple demo which blinks the onboard LED 
--|   using the TIM2 general purpose timer.
--|  
--|----------------------------------------------------------------------------|
--| REFERENCES:
--|   stm32f10x reference manual, page 365
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
#include "PSP_TIMx.h"

/*
--|----------------------------------------------------------------------------|
--| DEFINES
--|----------------------------------------------------------------------------|
*/

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

    // enable timer 2 clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN_FLAG;

    // use TIM2 prescaler to divide system clock down to 10kHz
    TIM2->PSC = 3200u - 1u;

    // use TIM2 auto-reload divide system clock down to 1Hz
    TIM2->ARR = 10000u - 1u;

    // clear TIM2 counter
    TIM2->CNT = 0u;

    // enable TIM2
    TIM2->CR1 |= TIMx_CR1_CEN_FLAG;

    while (1)
    {
        // check for the TIM2 event
        if ((TIM2->SR & TIMx_SR_UIF_FLAG))
		{
            // clear the TIM2 event
            TIM2->SR &= ~(TIMx_SR_UIF_FLAG);

            PSP_GPIO_Toggle_Pin(&LED_pin);
        }
    }

    // never reached
    return 0;
}
