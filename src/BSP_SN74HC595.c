/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   BSP_74HC595.c provides the implementation for using 74HC595 8 bit shift
--|   register integrated circuits.
--|  
--|----------------------------------------------------------------------------|
--| NOTES:
--|   None.
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

#include "BSP_SN74HC595.h"

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

void BSP_SN74HC595_Init(BSP_SN74HC595_t * p_SN74HC595)
{
    // the data, clock, and latch pins are all initialized the same
    GPIO_Pin_Initialization_Data_t pin_init_struct =
    {
        GPIO_PIN_CNFy_GENERAL_PURPOSE_OUTPUT_PUSH_PULL,
        GPIO_PIN_MODEy_OUTPUT_10MHz_MAX,
        GPIO_PIN_NO_PULL_UP_OR_DOWN
    };

    // set the data, clock, and latch pins using the given init struct
    PSP_GPIO_Set_Pin_Mode(p_SN74HC595->p_SER_pin, &pin_init_struct);
    PSP_GPIO_Set_Pin_Mode(p_SN74HC595->p_SRCLK_pin, &pin_init_struct);
    PSP_GPIO_Set_Pin_Mode(p_SN74HC595->p_RCLK_pin, &pin_init_struct);

    // write intial data, clock, and latch pin levels
    PSP_GPIO_Write_Pin(p_SN74HC595->p_SER_pin, GPIO_PIN_OUTPUT_WRITE_LOW);
    PSP_GPIO_Write_Pin(p_SN74HC595->p_SRCLK_pin, GPIO_PIN_OUTPUT_WRITE_LOW);
    PSP_GPIO_Write_Pin(p_SN74HC595->p_RCLK_pin, GPIO_PIN_OUTPUT_WRITE_HIGH);
}

void BSP_SN74HC595_Write(BSP_SN74HC595_t * p_SN74HC595, uint8_t value)
{
    // set the latch pin low to begin a write operation
    PSP_GPIO_Write_Pin(p_SN74HC595->p_RCLK_pin, GPIO_PIN_OUTPUT_WRITE_LOW);

    // go through the 8 bits of the input value one by one
    for(int i = 0; i < 8; ++i)
    {
        // set the clock pin low
        PSP_GPIO_Write_Pin(p_SN74HC595->p_SRCLK_pin, GPIO_PIN_OUTPUT_WRITE_LOW);

        // write the value of the bit
        uint8_t bit_to_write = (value >> (7u - i)) & 1u;
        PSP_GPIO_Write_Pin(p_SN74HC595->p_SER_pin, bit_to_write);

        // set the clock pin high
        PSP_GPIO_Write_Pin(p_SN74HC595->p_SRCLK_pin, GPIO_PIN_OUTPUT_WRITE_HIGH);
    }

    // set the latch pin high to end a write operation
    PSP_GPIO_Write_Pin(p_SN74HC595->p_RCLK_pin, GPIO_PIN_OUTPUT_WRITE_HIGH);
}

/*
--|----------------------------------------------------------------------------|
--| PRIVATE HELPER FUNCTION DEFINITIONS
--|----------------------------------------------------------------------------|
*/

/* None */
