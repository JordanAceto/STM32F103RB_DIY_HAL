/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   PSP_GPIO.c provides the private implementation for GPIO port and pin
--|   initialization, reading, and writing.
--|  
--|----------------------------------------------------------------------------|
--| REFERENCES:
--|   stm32f10x reference manual, page 159
--|
--|----------------------------------------------------------------------------|
*/

/*
--|----------------------------------------------------------------------------|
--| INCLUDE FILES
--|----------------------------------------------------------------------------|
*/

#include "PSP_GPIO.h"

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

/* None */

/*
--|----------------------------------------------------------------------------|
--| PUBLIC FUNCTION DEFINITIONS
--|----------------------------------------------------------------------------|
*/

void PSP_GPIO_Set_Pin_Mode(GPIO_Pin_t * p_GPIO_pin, 
                           GPIO_Pin_Initialization_Data_t * p_init_data)
{
    /* 
    The config setting for a given GPIO pin takes up 4 bits in CR<L/H>. 
    CR<L/H> each cover 8 GPIO pins, so we need the [(pin-num % 8) * 4] to 
    get the pin position.
    */
    const uint32_t CRn_register_offset = (p_GPIO_pin->number % 8u) << 2u;

    // 4 bit mask to avoid overwriting other pins
    const uint32_t CNFy_and_MODEy_mask = ~(0xFu << CRn_register_offset);

    // shuffle the CNFy and MODEy settings so that they take up 4 bits
    uint32_t configuration_word = (p_init_data->CNFy << 2u);
    configuration_word |= p_init_data->MODEy;
    // and shift them to the correct position for the given pin
    configuration_word <<= CRn_register_offset;

    // pins 0...7 go in the "low" port configuration register
    if (p_GPIO_pin->number < 8u)
    {
        // clear out the old pin CNFy and MODEy bits
        p_GPIO_pin->port->CRL &= CNFy_and_MODEy_mask;
        // set the new configuration
        p_GPIO_pin->port->CRL |= configuration_word;
    }
    else // pins 8...15 go in the "high" port configuration register
    {
        p_GPIO_pin->port->CRH &= CNFy_and_MODEy_mask;
        p_GPIO_pin->port->CRH |= configuration_word;
    }

    if (p_init_data->pull_up_down != GPIO_PIN_NO_PULL_UP_OR_DOWN)
    {
        // clear out the existing pull up/down setting
        p_GPIO_pin->port->ODR &= ~(1u << p_GPIO_pin->number);
        // set the new pull up/down setting
        p_GPIO_pin->port->ODR |= (p_init_data->pull_up_down << p_GPIO_pin->number);
    }
}

void PSP_GPIO_Write_Pin(GPIO_Pin_t * p_GPIO_pin,
                        GPIO_Pin_Output_Write_enum pin_direction)
{
    if (pin_direction == GPIO_PIN_OUTPUT_WRITE_LOW)
    {
        p_GPIO_pin->port->BRR = (1u << p_GPIO_pin->number);
    }
    else
    {
        p_GPIO_pin->port->BSRR = (1u << p_GPIO_pin->number);
    }
}

void PSP_GPIO_Toggle_Pin(GPIO_Pin_t * p_GPIO_pin)
{
    p_GPIO_pin->port->ODR ^= (1u << p_GPIO_pin->number);
}

GPIO_Pin_Input_Read_enum PSP_GPIO_Read_Pin(GPIO_Pin_t * p_GPIO_pin)
{
    return (p_GPIO_pin->port->IDR >> p_GPIO_pin->number) & 1u;
}

/*
--|----------------------------------------------------------------------------|
--| PRIVATE HELPER FUNCTION DEFINITIONS
--|----------------------------------------------------------------------------|
*/

/* None */
