/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   simple_SPI_demo.c provides a simple demo of the SPI peripherals which
--|   periodically sends some data over the SPI bus.
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

#include "PSP_GPIO.h"
#include "PSP_RCC.h"
#include "PSP_SPI.h"
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
#define UPDATE_TIME_mSec (10u)

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
    // enable the clock control for GPIO port A
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN_FLAG;

    // enable SPI1 clock
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN_FLAG;

    // enable alternate function clock
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN_FLAG;

    SPI_Init(&SPI_handle, 
             SPI_CR1_BR_fpclk_over_64, 
             DATA_FRAME_FORMAT_16_BITS, 
             DATA_DIRECTION_LSB_FIRST);

    periodic_timer.timeout_period_mSec = UPDATE_TIME_mSec;

    SysTick_Start_Timeout_Timer(&periodic_timer);

    uint16_t val_to_write = 0u;

    while (1)
    {
        if (SysTick_Poll_Periodic_Timer(&periodic_timer))
		{
            SPI_Send_16(&SPI_handle, val_to_write);
            val_to_write++;
		}
    }

    // never reached
    return 0;
}
