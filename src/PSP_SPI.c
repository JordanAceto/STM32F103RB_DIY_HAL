/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   PSP_SPI.c provides the implementation for SPI functions.
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
#include "PSP_SPI.h"

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

void SPI_Init(SPI_Transaction_Handle_t * p_SPI_handle, 
              SPI_CR1_BR_MASKS_enum baud_rate_divider,
              Data_Frame_Format_enum data_frame_format,
              Data_Direction_enum data_direction)
{
    // set the baud rate
    p_SPI_handle->p_SPI->CR1 &= ~(THREE_BIT_MASK << SPI_CR1_BR_SHIFT_AMT);
    p_SPI_handle->p_SPI->CR1 |= baud_rate_divider << SPI_CR1_BR_SHIFT_AMT;

    // set the SPI1 data frame format
    if (data_frame_format == DATA_FRAME_FORMAT_16_BITS)
    {
        p_SPI_handle->p_SPI->CR1 |= SPI_CR1_DFF_FLAG;  
    }    
    else
    {
        p_SPI_handle->p_SPI->CR1 &= ~SPI_CR1_DFF_FLAG; 
    }
    
    // set the bit order
    if (data_direction == DATA_DIRECTION_LSB_FIRST)
    {
        p_SPI_handle->p_SPI->CR1 |= SPI_CR1_LSBFIRST_FLAG; 
    }
    else
    {
        p_SPI_handle->p_SPI->CR1 &= ~SPI_CR1_LSBFIRST_FLAG; 
    }
    
    // set the SPI channel to use software SS
    p_SPI_handle->p_SPI->CR1 |= SPI_CR1_SSM_FLAG;
    p_SPI_handle->p_SPI->CR1 |= SPI_CR1_SSI_FLAG;

    // set the SPI channel to be a master
    p_SPI_handle->p_SPI->CR1 |= SPI_CR1_MSTR_FLAG;

    // enable the SPI channel
    p_SPI_handle->p_SPI->CR1 |= SPI_CR1_SPE_FLAG;

    // create pin init data for mosi, miso, sck, and ss
    GPIO_Pin_Initialization_Data_t mosi_init_data = 
    {
        GPIO_PIN_CNFy_ALTERNATE_FUNCTION_OUTPUT_PUSH_PULL,
        GPIO_PIN_MODEy_OUTPUT_50MHz_MAX,
        GPIO_PIN_NO_PULL_UP_OR_DOWN
    };

    GPIO_Pin_Initialization_Data_t miso_init_data = 
    {
        GPIO_PIN_CNFy_FLOATING_INPUT,
        GPIO_PIN_MODEy_INPUT_MODE,
        GPIO_PIN_ENABLE_INPUT_PULLUP
    };

    GPIO_Pin_Initialization_Data_t sck_init_data = 
    {
        GPIO_PIN_CNFy_ALTERNATE_FUNCTION_OUTPUT_PUSH_PULL,
        GPIO_PIN_MODEy_OUTPUT_50MHz_MAX,
        GPIO_PIN_NO_PULL_UP_OR_DOWN
    };

    GPIO_Pin_Initialization_Data_t ss_init_data = 
    {
        GPIO_PIN_CNFy_GENERAL_PURPOSE_OUTPUT_PUSH_PULL,
        GPIO_PIN_MODEy_OUTPUT_50MHz_MAX,
        GPIO_PIN_NO_PULL_UP_OR_DOWN
    };

    // set the pin modes using the init data
    PSP_GPIO_Set_Pin_Mode(p_SPI_handle->p_mosi_pin, &mosi_init_data);
    PSP_GPIO_Set_Pin_Mode(p_SPI_handle->p_miso_pin, &miso_init_data);
    PSP_GPIO_Set_Pin_Mode(p_SPI_handle->p_sck_pin,  &sck_init_data);
    PSP_GPIO_Set_Pin_Mode(p_SPI_handle->p_ss_pin,   &ss_init_data);
}

void SPI_Send_8(SPI_Transaction_Handle_t * p_SPI_handle, uint8_t data)
{
    while (!(p_SPI_handle->p_SPI->SR & SPI_SR_TXE_FLAG))
    {
        // wait until Tx buffer is empty
    }

    PSP_GPIO_Write_Pin(p_SPI_handle->p_ss_pin, 0u);
    
    p_SPI_handle->p_SPI->DR = data;
    
    while (p_SPI_handle->p_SPI->SR & SPI_SR_BSY_FLAG)
    {
        // wait for transmission to complete
    }

    PSP_GPIO_Write_Pin(p_SPI_handle->p_ss_pin, 1u);
}

void SPI_Send_16(SPI_Transaction_Handle_t * p_SPI_handle, uint16_t data)
{
    while (!(p_SPI_handle->p_SPI->SR & SPI_SR_TXE_FLAG))
    {
        // wait until Tx buffer is empty
    }

    PSP_GPIO_Write_Pin(p_SPI_handle->p_ss_pin, 0u);
    
    p_SPI_handle->p_SPI->DR = data;
    
    while (p_SPI_handle->p_SPI->SR & SPI_SR_BSY_FLAG)
    {
        // wait for transmission to complete
    }

    PSP_GPIO_Write_Pin(p_SPI_handle->p_ss_pin, 1u);
}

/*
--|----------------------------------------------------------------------------|
--| PRIVATE HELPER FUNCTION DEFINITIONS
--|----------------------------------------------------------------------------|
*/

/* None */
