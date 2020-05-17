/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   PSP_SPI.h provides types and functions for interfacing with SPI. 
--|    
--|----------------------------------------------------------------------------|
--| REFERENCES:
--|   stm32f10x reference manual, page 699
--|
--|----------------------------------------------------------------------------|
*/

#ifndef PSP_SPI_H_INCLUDED
#define PSP_SPI_H_INCLUDED

/*
--|----------------------------------------------------------------------------|
--| INCLUDE FILES
--|----------------------------------------------------------------------------|
*/

#include "Common_Typedefs.h"
#include "PSP_GPIO.h"
#include "PSP_Peripherals_Memory_Map.h"

/*
--|----------------------------------------------------------------------------|
--| PUBLIC DEFINES
--|----------------------------------------------------------------------------|
*/

/*
--| NAME: SPI1 
--| DESCRIPTION: pointer to SPI 1 
--| TYPE: SPI_t*
*/
#define SPI1 ((volatile SPI_t *)PSP_PERIPHERAL_SPI1_BASE)

/*
--| NAME: SPI2
--| DESCRIPTION: pointer to SPI 2
--| TYPE: SPI_t*
*/
#define SPI2 ((volatile SPI_t *)PSP_PERIPHERAL_SPI2_BASE)

/*
--|----------------------------------------------------------------------------|
--| PUBLIC TYPES
--|----------------------------------------------------------------------------|
*/

/*
--| NAME: SPI_t
--| DESCRIPTION: SPIn register structure
*/
typedef struct SPI_Type
{
    vuint32_t CR1;     // control register 1
    vuint32_t CR2;     // control register 2
    vuint32_t SR;      // status register
    vuint32_t DR;      // data register
    vuint32_t CRCPR;   // CRC polynomial register
    vuint32_t RXCRCR;  // RX CRC register
    vuint32_t TXCRCR;  // TX CRC register
    vuint32_t I2SCFGR; // I2S configuration register
    vuint32_t I2SPR;   // I2S prescaler register
} SPI_t;

/*
--| NAME: SPI_CR1_BR_MASKS_enum
--| DESCRIPTION: baud rate control configuration for a given SPI CR1 BR field [3 bits, rw]
*/
typedef enum SPI_CR1_BR_MASKS_Enumeration
{
    SPI_CR1_BR_fpclk_over_2   = 0b000u, // f_PCLK / 2
    SPI_CR1_BR_fpclk_over_4   = 0b001u, // f_PCLK / 4
    SPI_CR1_BR_fpclk_over_8   = 0b010u, // f_PCLK / 8
    SPI_CR1_BR_fpclk_over_16  = 0b011u, // f_PCLK / 16
    SPI_CR1_BR_fpclk_over_32  = 0b100u, // f_PCLK / 32
    SPI_CR1_BR_fpclk_over_64  = 0b101u, // f_PCLK / 64
    SPI_CR1_BR_fpclk_over_128 = 0b110u, // f_PCLK / 128
    SPI_CR1_BR_fpclk_over_256 = 0b111u, // f_PCLK / 256
    SPI_CR1_BR_SHIFT_AMT      = 3u      // position of BR in SPI CR1
} SPI_CR1_BR_MASKS_enum;

/*
--| NAME: SPI_CR1_FLAGS_enum
--| DESCRIPTION: SPI control register 1 flags
*/
typedef enum SPI_CR1_FLAGS_Enumeration
{
    SPI_CR1_BIDIMODE_FLAG = (1u << 15u), // Bidirectional data mode enable [rw]
    SPI_CR1_BIDIOE_FLAG   = (1u << 14u), // Output enable in bidirectional mode [rw]
    SPI_CR1_CRCEN_FLAG    = (1u << 13u), // Hardware CRC calculation enable [rw]
    SPI_CR1_CRCNEXT_FLAG  = (1u << 12u), // CRC transfer next [rw]
    SPI_CR1_DFF_FLAG      = (1u << 11u), // Data frame format [rw]
    SPI_CR1_RXONLY_FLAG   = (1u << 10u), // Receive only [rw]
    SPI_CR1_SSM_FLAG      = (1u << 9u),  // Software slave management [rw]
    SPI_CR1_SSI_FLAG      = (1u << 8u),  // Internal slave select [rw]
    SPI_CR1_LSBFIRST_FLAG = (1u << 7u),  // Frame format [rw]
    SPI_CR1_SPE_FLAG      = (1u << 6u),  // SPI enable [rw]
    SPI_CR1_MSTR_FLAG     = (1u << 2u),  // Master selection [rw]
    SPI_CR1_CPOL_FLAG     = (1u << 1u),  // Clock polarity [rw]
    SPI_CR1_CPHA_FLAG     = (1u << 0u),  // Clock phase [rw]
} SPI_CR1_FLAGS_enum;

/*
--| NAME: SPI_CR2_FLAGS_enum
--| DESCRIPTION: SPI control register 2 flags
*/
typedef enum SPI_CR2_FLAGS_Enumeration
{
    SPI_CR2_TXEIE_FLAG   = (1u << 7u), // Tx buffer empty interrupt enable [rw]
    SPI_CR2_RXNEIE_FLAG  = (1u << 6u), // RX buffer not empty interrupt enable [rw]
    SPI_CR2_ERRIE_FLAG   = (1u << 5u), // Error interrupt enable [rw]
    SPI_CR2_SSOE_FLAG    = (1u << 2u), // SS output enable [rw]
    SPI_CR2_TXDMAEN_FLAG = (1u << 1u), // Tx buffer DMA enable [rw]
    SPI_CR2_RXDMAEN_FLAG = (1u << 0u), // Rx buffer DMA enable [rw]
} SPI_CR2_FLAGS_enum;

/*
--| NAME: SPI_SR_FLAGS_enum
--| DESCRIPTION: SPI status register flags
*/
typedef enum SPI_SR_FLAGS_Enumeration
{
    SPI_SR_BSY_FLAG    = (1u << 7u), // Busy flag [r]
    SPI_SR_OVR_FLAG    = (1u << 6u), // Overrun flag [r]
    SPI_SR_MODF_FLAG   = (1u << 5u), // Mode fault [r]
    SPI_SR_CRCERR_FLAG = (1u << 4u), // CRC error flag [rc_w0]
    SPI_SR_UDR_FLAG    = (1u << 3u), // Underrun flag [r]
    SPI_SR_CHSIDE_FLAG = (1u << 2u), // Channel side [r]
    SPI_SR_TXE_FLAG    = (1u << 1u), // Transmit buffer empty [r]
    SPI_SR_RXNE_FLAG   = (1u << 0u), // Receive buffer not empty [r]
} SPI_SR_FLAGS_enum;

/*
--| NAME: SPI_Transaction_Handle_t
--| DESCRIPTION: handle to an SPI transaction
*/
typedef struct SPI_Transaction_Handle_Type
{
    volatile SPI_t * p_SPI;
    
    GPIO_Pin_t * p_mosi_pin;
    GPIO_Pin_t * p_miso_pin;
    GPIO_Pin_t * p_sck_pin;
    GPIO_Pin_t * p_ss_pin;

} SPI_Transaction_Handle_t;

/*
--| NAME: Data_Frame_Format_enum
--| DESCRIPTION: enumeration for data frame format
*/
typedef enum Data_Frame_Format_Enumeration
{
    DATA_FRAME_FORMAT_8_BITS,
    DATA_FRAME_FORMAT_16_BITS
} Data_Frame_Format_enum;

/*
--| NAME: Data_Direction_enum
--| DESCRIPTION: enumeration for data direction
*/
typedef enum Data_Direction_Enumeration
{
    DATA_DIRECTION_MSB_FIRST,
    DATA_DIRECTION_LSB_FIRST
} Data_Direction_enum;

/*
--|----------------------------------------------------------------------------|
--| PUBLIC CONSTANTS
--|----------------------------------------------------------------------------|
*/

/* None */

/*
--|----------------------------------------------------------------------------|
--| PUBLIC VARIABLES
--|----------------------------------------------------------------------------|
*/

/* None */

/*
--|----------------------------------------------------------------------------|
--| PUBLIC FUNCTION PROTOTYPES
--|----------------------------------------------------------------------------|
*/

/*------------------------------------------------------------------------------
Function Name:
    SPI_Init

Function Description:
    Initialize a given SPI channel with the given configuration data. 

Parameters:
    p_SPI_handle: pointer to the SPI handle to initialize.
    baud_rate_divider: the baud rate divider to use.
    data_frame_format: 16 bit transfers or 8 bit transfers.
    data_direction: lsb-first or msb-first.

Returns:
    None

Assumptions/Limitations:
    Assumes that the given SPI channel has been enabled in the RCC register.
------------------------------------------------------------------------------*/
void SPI_Init(SPI_Transaction_Handle_t * p_SPI_handle, 
              SPI_CR1_BR_MASKS_enum baud_rate_divider,
              Data_Frame_Format_enum data_frame_format,
              Data_Direction_enum data_direction);

/*------------------------------------------------------------------------------
Function Name:
    SPI_Send_8

Function Description:
    Send 8 bits of data via SPI. 

Parameters:
    p_SPI_handle: pointer to the SPI handle to send data with.
    data: the data to send.

Returns:
    None

Assumptions/Limitations:
    Assumes that the given SPI channel has been configured for 8 bit mode.
------------------------------------------------------------------------------*/
void SPI_Send_8(SPI_Transaction_Handle_t * p_SPI_handle, uint8_t data);

/*------------------------------------------------------------------------------
Function Name:
    SPI_Send_16

Function Description:
    Send 16 bits of data via SPI. 

Parameters:
    p_SPI_handle: pointer to the SPI handle to send data with.
    data: the data to send.

Returns:
    None

Assumptions/Limitations:
    Assumes that the given SPI channel has been configured for 16 bit mode.
------------------------------------------------------------------------------*/
void SPI_Send_16(SPI_Transaction_Handle_t * p_SPI_handle, uint16_t data);

#endif
