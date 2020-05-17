/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   simple_SPI_demo.c provides writes a ramp wave to both channels of an
--|   MCP4822 SPI DAC, with the ramps 90 degrees out of phase.
--|  
--|----------------------------------------------------------------------------|
--| REFERENCES:
--|   mcp4822_datasheet.pdf
--|
--|----------------------------------------------------------------------------|
*/

/*
--|----------------------------------------------------------------------------|
--| INCLUDE FILES
--|----------------------------------------------------------------------------|
*/

#include "BSP_MCP4822.h"
#include "PSP_GPIO.h"
#include "PSP_RCC.h"
#include "PSP_SPI.h"
#include "PSP_SysTick.h"
#include "PSP_Hardware_Init.h"

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
#define UPDATE_TIME_mSec (1u)

/*
--| NAME: MOSI_PIN_NUMBER
--| DESCRIPTION: the pin number for the MOSI pin
--| TYPE: uint32_t
*/
#define MOSI_PIN_NUMBER (7u)

/*
--| NAME: MISO_PIN_NUMBER
--| DESCRIPTION: the pin number for the MISO pin
--| TYPE: uint32_t
*/
#define MISO_PIN_NUMBER (6u)

/*
--| NAME: SCK_PIN_NUMBER
--| DESCRIPTION: the pin number for the SCK pin
--| TYPE: uint32_t
*/
#define SCK_PIN_NUMBER (5u)

/*
--| NAME: SS_PIN_NUMBER
--| DESCRIPTION: the pin number for the SS pin
--| TYPE: uint32_t
*/
#define SS_PIN_NUMBER (4u)

/*
--| NAME: SPI1_GPIO_PORT
--| DESCRIPTION: the GPIO port which contains the pins for the SPI1
--| TYPE: GPIO_Port_t*
*/
#define SPI1_GPIO_PORT (GPIO_Port_A)

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
--| DESCRIPTION: periodic timeout timer structure for scheduling the data transfer
--| TYPE: SysTick_Timeout_Timer_t
*/
SysTick_Timeout_Timer_t periodic_timer;

/*
--| NAME: mosi_pin
--| DESCRIPTION: the MOSI pin for the SPI demo
--| TYPE: GPIO_Pin_t
*/
GPIO_Pin_t mosi_pin =
{
    SPI1_GPIO_PORT,
    MOSI_PIN_NUMBER
};

/*
--| NAME: miso_pin
--| DESCRIPTION: the MISO pin for the SPI demo
--| TYPE: GPIO_Pin_t
*/
GPIO_Pin_t miso_pin =
{
    SPI1_GPIO_PORT,
    MISO_PIN_NUMBER
};

/*
--| NAME: sck_pin
--| DESCRIPTION: the SCK pin for the SPI demo
--| TYPE: GPIO_Pin_t
*/
GPIO_Pin_t sck_pin =
{
    SPI1_GPIO_PORT,
    SCK_PIN_NUMBER
};

/*
--| NAME: ss_pin
--| DESCRIPTION: the SS pin for the SPI demo
--| TYPE: GPIO_Pin_t
*/
GPIO_Pin_t ss_pin =
{
    SPI1_GPIO_PORT,
    SS_PIN_NUMBER
};

/*
--| NAME: SPI_handle
--| DESCRIPTION: the handle to the SPI transaction structure
--| TYPE: SPI_Transaction_Handle_t
*/
SPI_Transaction_Handle_t SPI_handle =
{
    SPI1,
    &mosi_pin,
    &miso_pin,
    &sck_pin,
    &ss_pin
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
    main application function which sends SPI data in an endless loop. 

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

    // enable SPI1 clock
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN_FLAG;

    // enable alternate function clock
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN_FLAG;

    SPI_Init(&SPI_handle, 
             SPI_CR1_BR_fpclk_over_64, 
             DATA_FRAME_FORMAT_16_BITS, 
             DATA_DIRECTION_MSB_FIRST);

    periodic_timer.timeout_period_mSec = UPDATE_TIME_mSec;

    SysTick_Start_Timeout_Timer(&periodic_timer);

    uint16_t val_to_write = 0u;

    while (1)
    {
        if (SysTick_Poll_Periodic_Timer(&periodic_timer))
		{

            MCP4822_Write(&SPI_handle,
                         MCP4822_CHANNEL_A,
                         MCP4822_GAIN_1x,
                         val_to_write);

            MCP4822_Write(&SPI_handle,
                         MCP4822_CHANNEL_B,
                         MCP4822_GAIN_1x,
                         val_to_write + (1u << 11u)); // 90 degree phase shift

            val_to_write += 25;
            
		}
    }

    // never reached
    return 0;
}