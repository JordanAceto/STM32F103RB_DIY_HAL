/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   PSP_RCC.h provides types and interfaces for the Reset and Clock Control
--|   Registers.
--|  
--|----------------------------------------------------------------------------|
--| REFERENCES:
--|   stm32f10x reference manual, page 99
--|
--|----------------------------------------------------------------------------|
*/

#ifndef PSP_RCC_H_INCLUDED
#define PSP_RCC_H_INCLUDED

/*
--|----------------------------------------------------------------------------|
--| INCLUDE FILES
--|----------------------------------------------------------------------------|
*/

#include "Common_Masks.h"
#include "Common_Typedefs.h"
#include "PSP_Peripherals_Memory_Map.h"

/*
--|----------------------------------------------------------------------------|
--| PUBLIC DEFINES
--|----------------------------------------------------------------------------|
*/

/*
--| NAME: RCC
--| DESCRIPTION: pointer to RCC 
--| TYPE: RCC_Register_t*
*/
#define RCC ((volatile RCC_Register_t *)PSP_PERIPHERAL_RCC_BASE)

/*
--|----------------------------------------------------------------------------|
--| PUBLIC TYPES
--|----------------------------------------------------------------------------|
*/

/*
--| NAME: RCC_Register_t
--| DESCRIPTION: Reset and Clock Control Registers
*/
typedef struct RCC_Register_Type
{
    vuint32_t CR;       // clock control register
    vuint32_t CFGR;     // clock configuration register
    vuint32_t CIR;      // clock interrupt register
    vuint32_t APB2RSRT; // APB2 peripheral reset register
    vuint32_t APB1RSRT; // APB1 peripheral reset register
    vuint32_t AHBENR;   // AHB peripheral clock enable register
    vuint32_t APB2ENR;  // APB2 peripheral clock enable register
    vuint32_t APB1ENR;  // APB1 peripheral clock enable register
    vuint32_t BDCR;     // backup domain control register
    vuint32_t CSR;      // control/status register
} RCC_Register_t;

/*
--| NAME: RCC_CR_FLAGS_enum
--| DESCRIPTION: RCC Clock control register flags
*/
typedef enum RCC_CR_FLAGS_Enumeration
{
    RCC_CR_PLL3RDY_FLAG = (1u << 29u), // PLL3 clock ready flag [r]
    RCC_CR_PLL3ON_FLAG  = (1u << 28u), // PLL3 enable [rw]
    RCC_CR_PLL2RDY_FLAG = (1u << 27u), // PLL2 clock ready flag [r]
    RCC_CR_PLL2ON_FLAG  = (1u << 26u), // PLL2 enable [rw]
    RCC_CR_PLLRDY_FLAG  = (1u << 25u), // PLL clock ready flag [r]
    RCC_CR_PLLON_FLAG   = (1u << 24u), // PLL enable [rw]
    RCC_CR_CSSON_FLAG   = (1u << 19u), // Clock security system enable [rw]
    RCC_CR_HSEBYP_FLAG  = (1u << 18u), // External high-speed clock bypass [rw]
    RCC_CR_HSERDY_FLAG  = (1u << 17u), // External high-speed clock ready flag [r]
    RCC_CR_HSEON_FLAG   = (1u << 16u), // HSE clock enable [rw]
    RCC_CR_HSIRDY_FLAG  = (1u << 1u),  // Internal high-speed clock ready flag [r]
    RCC_CR_HSION_FLAG   = (1u << 0u),  // Internal high-speed clock enable [rw]
} RCC_CR_FLAGS_enum;

/*
--| NAME: RCC_CR_HSICAL_Masks_enum
--| DESCRIPTION: RCC clock control register Internal high-speed clock calibration masks
*/
typedef enum RCC_CR_HSICAL_Masks_Enumeration
{
    RCC_CR_HSICAL_MASK      = EIGHT_BIT_MASK, // Internal high-speed clock calibration [8 bits, r]
    RCC_CR_HSICAL_SHIFT_AMT = 8u,             // position of HSICAL in RCC CR
} RCC_CR_HSICAL_Masks_enum;

/*
--| NAME: RCC_CR_HSITRIM_Masks_enum
--| DESCRIPTION: RCC clock control register Internal high-speed clock trimming masks
*/
typedef enum RCC_CR_HSITRIM_Masks_Enumeration
{
    RCC_CR_HSITRIM_MASK      = FIVE_BIT_MASK, // Internal high-speed clock trimming [5 bits, rw]
    RCC_CR_HSITRIM_SHIFT_AMT = 3u,            // position of HSITRIM in RCC CR
} RCC_CR_HSITRIM_Masks_enum;


/*
--| NAME: RCC_CFGR_FLAGS_enum
--| DESCRIPTION: RCC Clock configuration register flags
*/
typedef enum RCC_CFGR_FLAGS_Enumeration
{
    RCC_CFGR_OTGFSPRE_FLAG = (1u << 22u), // USB OTG FS prescaler [rw]
    RCC_CFGR_PLLXTPRE_FLAG = (1u << 17u), // LSB of division factor PREDIV1 [rw]
    RCC_CFGR_PLLSRC_FLAG   = (1u << 16u), // PLL entry clock source [rw]
} RCC_CFGR_FLAGS_enum;

/*
--| NAME: RCC_CFGR_MCO_MASKS_enum
--| DESCRIPTION: RCC CFGR Microcontroller clock output masks [3 bits, rw]
*/
typedef enum RCC_CFGR_MCO_MASKS_Enumeration
{
    RCC_CFGR_MCO_NO_CLOCK  = 0b000u, // No clock
    RCC_CFGR_MCO_SYSCLK    = 0b100u, // System clock (SYSCLK) selected
    RCC_CFGR_MCO_HSI       = 0b101u, // HSI clock selected
    RCC_CFGR_MCO_HSE       = 0b110u, // HSE clock selected
    RCC_CFGR_MCO_PLL       = 0b111u, // PLL clock divided by 2 selected
    RCC_CFGR_MCO_SHIFT_AMT = 24u     // position of MCO in RCC CFGR
} RCC_CFGR_MCO_MASKS_enum;

/*
--| NAME: RCC_CFGR_PLLMUL_MASKS_enum
--| DESCRIPTION: RCC CFGR PLL multiplication factor [4 bits, rw]
--| Caution: The PLL output frequency must not exceed 72 MHz.
*/
typedef enum RCC_CFGR_PLLMUL_MASKS_Enumeration
{
    RCC_CFGR_PLLMUL_X_4         = 0b0010u, // PLL input clock x 4
    RCC_CFGR_PLLMUL_X_5         = 0b0011u, // PLL input clock x 5
    RCC_CFGR_PLLMUL_X_6         = 0b0100u, // PLL input clock x 6
    RCC_CFGR_PLLMUL_X_7         = 0b0101u, // PLL input clock x 7
    RCC_CFGR_PLLMUL_X_8         = 0b0110u, // PLL input clock x 8
    RCC_CFGR_PLLMUL_X_9         = 0b0111u, // PLL input clock x 9
    RCC_CFGR_PLLMUL_X_6_POINT_5 = 0b1101u, // PLL input clock x 6.5
    RCC_CFGR_PLLMUL_SHIFT_AMT   = 18u      // position of PLLMUL in RCC CFGR
} RCC_CFGR_PLLMUL_MASKS_enum;

/*
--| NAME: RCC_CFGR_ADCPRE_MASKS_enum
--| DESCRIPTION: RCC CFGR ADC prescaler [2 bits, rw]
*/
typedef enum RCC_CFGR_ADCPRE_MASKS_Enumeration
{
    RCC_CFGR_ADCPRE_PCLK_DIV_2 = 0b00u, // PCLK2 divided by 2
    RCC_CFGR_ADCPRE_PCLK_DIV_4 = 0b01u, // PCLK2 divided by 4
    RCC_CFGR_ADCPRE_PCLK_DIV_6 = 0b10u, // PCLK2 divided by 6
    RCC_CFGR_ADCPRE_PCLK_DIV_8 = 0b11u, // PCLK2 divided by 8
    RCC_CFGR_ADCPRE_SHIFT_AMT  = 14u    // position of ADCPRE in RCC CFGR
} RCC_CFGR_ADCPRE_MASKS_enum;

/*
--| NAME: RCC_CFGR_PPRE2_MASKS_enum
--| DESCRIPTION: RCC CFGR APB high-speed prescaler (APB2) [3 bits, rw]
*/
typedef enum RCC_CFGR_PPRE2_MASKS_Enumeration
{
    RCC_CFGR_PPRE2_NO_DIVIDE = 0b000u, // HCLK not divided
    RCC_CFGR_PPRE2_DIV_BY_2  = 0b100u, // HCLK divided by 2
    RCC_CFGR_PPRE2_DIV_BY_4  = 0b101u, // HCLK divided by 4
    RCC_CFGR_PPRE2_DIV_BY_8  = 0b110u, // HCLK divided by 8
    RCC_CFGR_PPRE2_DIV_BY_16 = 0b111u, // HCLK divided by 16
    RCC_CFGR_PPRE2_SHIFT_AMT = 11u     // position of PPRE2 in RCC CFGR
} RCC_CFGR_PPRE2_MASKS_enum;

/*
--| NAME: RCC_CFGR_PPRE1_MASKS_enum
--| DESCRIPTION: RCC CFGR APB low-speed prescaler (APB1) [3 bits, rw]
--| Caution: frequency in this domain must not exceed 36 MHz
*/
typedef enum RCC_CFGR_PPRE1_MASKS_Enumeration
{
    RCC_CFGR_PPRE1_NO_DIVIDE = 0b000u, // HCLK not divided
    RCC_CFGR_PPRE1_DIV_BY_2  = 0b100u, // HCLK divided by 2
    RCC_CFGR_PPRE1_DIV_BY_4  = 0b101u, // HCLK divided by 4
    RCC_CFGR_PPRE1_DIV_BY_8  = 0b110u, // HCLK divided by 8
    RCC_CFGR_PPRE1_DIV_BY_16 = 0b111u, // HCLK divided by 16
    RCC_CFGR_PPRE1_SHIFT_AMT = 8u      // position of PPRE1 in RCC CFGR
} RCC_CFGR_PPRE1_MASKS_enum;

/*
--| NAME: RCC_CFGR_HPRE_MASKS_enum
--| DESCRIPTION: RCC CFGR AHB prescaler [4 bits, rw]
*/
typedef enum RCC_CFGR_HPRE_MASKS_Enumeration
{
    RCC_CFGR_HPRE_NO_DIVIDE  = 0b0000u, // SYSCLK not divided
    RCC_CFGR_HPRE_DIV_BY_2   = 0b1000u, // SYSCLK divided by 2
    RCC_CFGR_HPRE_DIV_BY_4   = 0b1001u, // SYSCLK divided by 4
    RCC_CFGR_HPRE_DIV_BY_8   = 0b1010u, // SYSCLK divided by 8
    RCC_CFGR_HPRE_DIV_BY_16  = 0b1011u, // SYSCLK divided by 16
    RCC_CFGR_HPRE_DIV_BY_64  = 0b1100u, // SYSCLK divided by 64
    RCC_CFGR_HPRE_DIV_BY_128 = 0b1101u, // SYSCLK divided by 128
    RCC_CFGR_HPRE_DIV_BY_256 = 0b1110u, // SYSCLK divided by 256
    RCC_CFGR_HPRE_DIV_BY_512 = 0b1111u, // SYSCLK divided by 512
    RCC_CFGR_HPRE_SHIFT_AMT  = 4u       // position of HPRE in RCC CFGR
} RCC_CFGR_HPRE_MASKS_enum;

/*
--| NAME: RCC_CFGR_SWS_MASKS_enum
--| DESCRIPTION: RCC CFGR System clock switch status [2 bits, r]
*/
typedef enum RCC_CFGR_SWS_MASKS_Enumeration
{
    RCC_CFGR_SWS_HSI       = 0b00u, // HSI oscillator used as system clock
    RCC_CFGR_SWS_HSE       = 0b01u, // HSE oscillator used as system clock
    RCC_CFGR_SWS_PLL       = 0b10u, // PLL used as system clock
    RCC_CFGR_SWS_FORBIDDEN = 0b11u, // not allowed
    RCC_CFGR_SWS_SHIFT_AMT = 2u     // position of SWS in RCC CFGR
} RCC_CFGR_SWS_MASKS_enum;

/*
--| NAME: RCC_CFGR_SW_MASKS_enum
--| DESCRIPTION: RCC CFGR System clock switch [2 bits, rw]
*/
typedef enum RCC_CFGR_SW_MASKS_Enumeration
{
    RCC_CFGR_SW_HSI       = 0b00u, // HSI selected as system clock
    RCC_CFGR_SW_HSE       = 0b01u, // HSE selected as system clock
    RCC_CFGR_SW_PLL       = 0b10u, // PLL selected as system clock
    RCC_CFGR_SW_FORBIDDEN = 0b11u, // not allowed
    RCC_CFGR_SW_SHIFT_AMT = 0u     // position of SW in RCC CFGR
} RCC_CFGR_SW_MASKS_enum;

/*
--| NAME: RCC_CIR_FLAGS_enum
--| DESCRIPTION: RCC Clock interrupt register register flags
*/
typedef enum RCC_CIR_FLAGS_Enumeration
{
    RCC_CIR_CSSC_FLAG      = (1u << 23u), // Clock security system interrupt clear [w]
    RCC_CIR_PLL3RDYC_FLAG  = (1u << 22u), // PLL3 Ready Interrupt Clear [w]
    RCC_CIR_PLL2RDYC_FLAG  = (1u << 21u), // PLL2 Ready Interrupt Clear [w]
    RCC_CIR_PLLRDYC_FLAG   = (1u << 20u), // PLL Ready Interrupt Clear [w]
    RCC_CIR_HSERDYC_FLAG   = (1u << 19u), // HSE ready interrupt clear [w]
    RCC_CIR_HSIRDYC_FLAG   = (1u << 18u), // HSI ready interrupt clear [w]
    RCC_CIR_LSERDYC_FLAG   = (1u << 17u), // LSE ready interrupt clear [w]
    RCC_CIR_LSIRDYC_FLAG   = (1u << 16u), // LSI ready interrupt clear [w]
    RCC_CIR_PLL3RDYIE_FLAG = (1u << 14u), // PLL3 Ready Interrupt Enable [rw]
    RCC_CIR_PLL2RDYIE_FLAG = (1u << 13u), // PLL2 Ready Interrupt Enable [rw]
    RCC_CIR_PLLRDYIE_FLAG  = (1u << 12u), // PLL Ready Interrupt Enable [rw]
    RCC_CIR_HSERDYIE_FLAG  = (1u << 11u), // HSE ready interrupt enable [rw]
    RCC_CIR_HSIRDYIE_FLAG  = (1u << 10u), // HSI ready interrupt enable [rw]
    RCC_CIR_LSERDYIE_FLAG  = (1u << 9u),  // LSE ready interrupt enable [rw]
    RCC_CIR_LSIRDYIE_FLAG  = (1u << 8u),  // LSI ready interrupt enable [rw]
    RCC_CIR_CSSF_FLAG      = (1u << 7u),  // Clock security system interrupt flag [r]
    RCC_CIR_PLL3RDYF_FLAG  = (1u << 6u),  // PLL 3 ready interrupt flag [r]
    RCC_CIR_PLL2RDYF_FLAG  = (1u << 5u),  // PLL 2 ready interrupt flag [r]
    RCC_CIR_PLLRDYF_FLAG   = (1u << 4u),  // PLL ready interrupt flag [r]
    RCC_CIR_HSERDYF_FLAG   = (1u << 3u),  // HSE ready interrupt flag [r]
    RCC_CIR_HSIRDYF_FLAG   = (1u << 2u),  // HSI ready interrupt flag [r]
    RCC_CIR_LSERDYF_FLAG   = (1u << 1u),  // LSE ready interrupt flag [r]
    RCC_CIR_LSIRDYF_FLAG   = (1u << 0u),  // LSI ready interrupt flag [r]
} RCC_CIR_FLAGS_enum;

/*
--| NAME: RCC_APB2RSTR_FLAGS_enum
--| DESCRIPTION: RCC APB2 peripheral reset register flags
*/
typedef enum RCC_APB2RSTR_FLAGS_Enumeration
{
    RCC_APB2RSTR_USART1RST_FLAG = (1u << 14u), // USART1 reset [rw]
    RCC_APB2RSTR_SPI1RST_FLAG   = (1u << 12u), // SPI 1 reset[rw]
    RCC_APB2RSTR_TIM1RST_FLAG   = (1u << 11u), // TIM1 timer reset [rw]
    RCC_APB2RSTR_ADC2RST_FLAG   = (1u << 10u), // ADC 2 interface reset [rw]
    RCC_APB2RSTR_ADC1RST_FLAG   = (1u << 9u),  // ADC 1 interface reset [rw]
    RCC_APB2RSTR_IOPERST_FLAG   = (1u << 6u),  // I/O port E reset [rw]
    RCC_APB2RSTR_IOPDRST_FLAG   = (1u << 5u),  // I/O port D reset [rw]
    RCC_APB2RSTR_IOPCRST_FLAG   = (1u << 4u),  // IO port C reset [rw]
    RCC_APB2RSTR_IOPBRST_FLAG   = (1u << 3u),  // IO port B reset [rw]
    RCC_APB2RSTR_IOPARST_FLAG   = (1u << 2u),  // I/O port A reset [rw]
    RCC_APB2RSTR_AFIORST_FLAG   = (1u << 0u),  // Alternate function I/O reset [rw]
} RCC_APB2RSTR_FLAGS_enum;

/*
--| NAME: RCC_APB1RSTR_FLAGS_enum
--| DESCRIPTION: RCC APB1 peripheral reset register flags
*/
typedef enum RCC_APB1RSTR_FLAGS_Enumeration
{
    RCC_APB1RSTR_DACRST_FLAG   = (1u << 29u), // DAC interface reset [rw]
    RCC_APB1RSTR_PWRRST_FLAG   = (1u << 28u), // Power interface reset [rw]
    RCC_APB1RSTR_BKPRST_FLAG   = (1u << 27u), // Backup interface reset [rw]
    RCC_APB1RSTR_CAN2RST_FLAG  = (1u << 26u), // CAN2RST [rw]
    RCC_APB1RSTR_CAN1RST_FLAG  = (1u << 25u), // CAN1RST [rw]
    RCC_APB1RSTR_I2C2RST_FLAG  = (1u << 22u), // I2C 2 reset [rw]
    RCC_APB1RSTR_I2C1RST_FLAG  = (1u << 21u), // I2C1 reset [rw]
    RCC_APB1RSTR_UART5RST_FLAG = (1u << 20u), // USART 5 reset [rw]
    RCC_APB1RSTR_UART4RST_FLAG = (1u << 19u), // USART 4 reset [rw]
    RCC_APB1RSTR_UART3RST_FLAG = (1u << 18u), // USART 3 reset [rw]
    RCC_APB1RSTR_UART2RST_FLAG = (1u << 17u), // USART 2 reset [rw]
    RCC_APB1RSTR_SPI3RST_FLAG  = (1u << 15u), // SPI3 reset [rw]
    RCC_APB1RSTR_SPI2RST_FLAG  = (1u << 14u), // SPI2 reset [rw]
    RCC_APB1RSTR_WWDGRST_FLAG  = (1u << 11u), // Window watchdog reset [rw]
    RCC_APB1RSTR_TIM7RST_FLAG  = (1u << 5u),  // Timer 7 reset [rw]
    RCC_APB1RSTR_TIM6RST_FLAG  = (1u << 4u),  // Timer 6 reset [rw]
    RCC_APB1RSTR_TIM5RST_FLAG  = (1u << 3u),  // Timer 5 reset [rw]
    RCC_APB1RSTR_TIM4RST_FLAG  = (1u << 2u),  // Timer 4 reset [rw]
    RCC_APB1RSTR_TIM3RST_FLAG  = (1u << 1u),  // Timer 3 reset [rw]
    RCC_APB1RSTR_TIM2RST_FLAG  = (1u << 0u),  // Timer 2 reset [rw]
} RCC_APB1RSTR_FLAGS_enum;

/*
--| NAME: RCC_AHBENR_FLAGS_enum
--| DESCRIPTION: RCC AHB Peripheral Clock enable register flags
*/
typedef enum RCC_AHBENR_FLAGS_Enumeration
{
    RCC_AHBENR_ETHMACRXEN_FLAG = (1u << 16u), // Ethernet MAC RX clock enable [rw]
    RCC_AHBENR_ETHMACTXEN_FLAG = (1u << 15u), // Ethernet MAC TX clock enable [rw]
    RCC_AHBENR_ETHMACEN_FLAG   = (1u << 14u), // Ethernet MAC clock enable [rw]
    RCC_AHBENR_OTGFSEN_FLAG    = (1u << 12u), // USB OTG FS clock enable [rw]
    RCC_AHBENR_CAN1RST_FLAG    = (1u << 25u), // CAN1RST [rw]
    RCC_AHBENR_CRCEN_FLAG      = (1u << 6u),  // CRC clock enable [rw]
    RCC_AHBENR_FLITFEN_FLAG    = (1u << 4u),  // FLITF clock enable [rw]
    RCC_AHBENR_SRAMEN_FLAG     = (1u << 2u),  // SRAM interface clock enable [rw]
    RCC_AHBENR_DMA2EN_FLAG     = (1u << 1u),  // DMA2 clock enable [rw]
    RCC_AHBENR_DMA1EN_FLAG     = (1u << 0u),  // DMA1 clock enable [rw]
} RCC_AHBENR_FLAGS_enum;

/*
--| NAME: RCC_APB2ENR_FLAGS_enum
--| DESCRIPTION: RCC APB2 peripheral clock enable register flags
*/
typedef enum RCC_APB2ENR_FLAGS_Enumeration
{
    RCC_APB2ENR_USART1EN_FLAG = (1u << 14u), // USART1 clock enable [rw]
    RCC_APB2ENR_SPI1EN_FLAG   = (1u << 12u), // SPI 1 clock enable [rw]
    RCC_APB2ENR_TIM1EN_FLAG   = (1u << 11u), // TIM1 Timer clock enable [rw]
    RCC_APB2ENR_ADC2EN_FLAG   = (1u << 10u), // ADC 2 interface clock enable [rw]
    RCC_APB2ENR_ADC1EN_FLAG   = (1u << 9u),  // ADC 1 interface clock enable [rw]
    RCC_APB2ENR_IOPEEN_FLAG   = (1u << 6u),  // I/O port E clock enable [rw]
    RCC_APB2ENR_IOPDEN_FLAG   = (1u << 5u),  // I/O port D clock enable [rw]
    RCC_APB2ENR_IOPCEN_FLAG   = (1u << 4u),  // I/O port C clock enable [rw]
    RCC_APB2ENR_IOPBEN_FLAG   = (1u << 3u),  // I/O port B clock enable [rw]
    RCC_APB2ENR_IOPAEN_FLAG   = (1u << 2u),  // I/O port A clock enable [rw]
    RCC_APB2ENR_AFIOEN_FLAG   = (1u << 0u),  // Alternate function I/O clock enable [rw]
} RCC_APB2ENR_FLAGS_enum;

/*
--| NAME: RCC_APB1ENR_FLAGS_enum
--| DESCRIPTION: RCC APB1 peripheral clock enable register flags
*/
typedef enum RCC_APB1ENR_FLAGS_Enumeration
{
    RCC_APB1ENR_DACEN_FLAG   = (1u << 29u), // DAC interface clock enable [rw]
    RCC_APB1ENR_PWREN_FLAG   = (1u << 28u), // Power interface clock enable [rw]
    RCC_APB1ENR_BKPEN_FLAG   = (1u << 27u), // Backup interface clock enable [rw]
    RCC_APB1ENR_CAN2EN_FLAG  = (1u << 26u), // CAN2 clock enable [rw]
    RCC_APB1ENR_CAN1EN_FLAG  = (1u << 25u), // CAN1 clock enable [rw]
    RCC_APB1ENR_I2C2EN_FLAG  = (1u << 22u), // I2C 2 clock enable [rw]
    RCC_APB1ENR_I2C1EN_FLAG  = (1u << 21u), // I2C 1 clock enable [rw]
    RCC_APB1ENR_UART5EN_FLAG = (1u << 20u), // USART 5 clock enable [rw]
    RCC_APB1ENR_UART4EN_FLAG = (1u << 19u), // USART 4 clock enable [rw]
    RCC_APB1ENR_UART3EN_FLAG = (1u << 18u), // USART 3 clock enable [rw]
    RCC_APB1ENR_UART2EN_FLAG = (1u << 17u), // USART 2 clock enable [rw]
    RCC_APB1ENR_SPI3EN_FLAG  = (1u << 15u), // SPI 3 clock enable [rw]
    RCC_APB1ENR_SPI2EN_FLAG  = (1u << 14u), // SPI 2 clock enable [rw]
    RCC_APB1ENR_WWDGEN_FLAG  = (1u << 11u), // Window watchdog clock enable [rw]
    RCC_APB1ENR_TIM7ENN_FLAG = (1u << 5u),  // Timer 7 clock enable [rw]
    RCC_APB1ENR_TIM6ENN_FLAG = (1u << 4u),  // Timer 6 clock enable [rw]
    RCC_APB1ENR_TIM5ENN_FLAG = (1u << 3u),  // Timer 5 clock enable [rw]
    RCC_APB1ENR_TIM4ENN_FLAG = (1u << 2u),  // Timer 4 clock enable [rw]
    RCC_APB1ENR_TIM3ENN_FLAG = (1u << 1u),  // Timer 3 clock enable [rw]
    RCC_APB1ENR_TIM2ENN_FLAG = (1u << 0u),  // Timer 2 clock enable [rw]
} RCC_APB1ENR_FLAGS_enum;

/*
--| NAME: RCC_BDCR_FLAGS_enum
--| DESCRIPTION: RCC APB1 Backup domain control register flags
*/
typedef enum RCC_BDCR_FLAGS_Enumeration
{
    RCC_BDCR_BDRST_FLAG  = (1u << 16u), // Backup domain software reset [rw]
    RCC_BDCR_RTCEN_FLAG  = (1u << 15u), // RTC clock enable [rw]
    RCC_BDCR_LSEBYP_FLAG = (1u << 2u),  // External Low Speed oscillator bypass [rw]
    RCC_BDCR_LSERDY_FLAG = (1u << 1u),  // External Low Speed oscillator ready [r]
    RCC_BDCR_LSEON_FLAG  = (1u << 0u),  // External Low Speed oscillator enable [rw]
} RCC_BDCR_FLAGS_enum;

/*
--| NAME: RCC_BDCR_RTCSEL_MASKS_enum
--| DESCRIPTION: RCC APB1 BDCR RTC clock source selection masks [2 bits, rw]
*/
typedef enum RCC_BDCR_RTCSEL_MASKS_Enumeration
{
    RCC_BDCR_RTCSEL_NO_CLOCK           = 0b00u, // No clock
    RCC_BDCR_RTCSEL_LSE_AS_RTC         = 0b01u, // LSE oscillator clock used as RTC clock
    RCC_BDCR_RTCSEL_LSI_AS_RTC         = 0b10u, // LSI oscillator clock used as RTC clock
    RCC_BDCR_RTCSEL_HSE_DIV_128_AS_RTC = 0b11u, // HSE oscillator clock divided by 128 used as RTC clock
    RCC_BDCR_RTCSEL_SHIFT_AMT          = 8u,    // Position of RTCSEL in RCC BDCR
} RCC_BDCR_RTCSEL_MASKS_enum;

/*
--| NAME: RCC_CSR_FLAGS_enum
--| DESCRIPTION: RCC Control/status register flags
*/
typedef enum RCC_CSR_FLAGS_Enumeration
{
    RCC_CSR_LPWRRSTF_FLAG = (1u << 31u), // Low-power reset flag [rw]
    RCC_CSR_WWDGRSTF_FLAG = (1u << 30u), // Window watchdog reset flag [rw]
    RCC_CSR_IWDGRSTF_FLAG = (1u << 29u), // Independent watchdog reset flag [rw]
    RCC_CSR_SFTRSTF_FLAG  = (1u << 28u), // Software reset flag [rw]
    RCC_CSR_PORRSTF_FLAG  = (1u << 27u), // POR/PDR reset flag [rw]
    RCC_CSR_PINRSTF_FLAG  = (1u << 26u), // PIN reset flag [rw]
    RCC_CSR_RMVF_FLAG     = (1u << 24u), // Remove reset flag [rw]
    RCC_CSR_LSIRDY_FLAG   = (1u << 1u),  // Internal low speed oscillator ready [r]
    RCC_CSR_LSION_FLAG    = (1u << 0u),  // Internal low speed oscillator enable [rw]
} RCC_CSR_FLAGS_enum;

/*
--| NAME: RCC_AHBRSTR_FLAGS_enum
--| DESCRIPTION: RCC AHB peripheral clock reset register flags
*/
typedef enum RCC_AHBRSTR_FLAGS_Enumeration
{
    RCC_AHBRSTR_ETHMACRST_FLAG = (1u << 14u), // Ethernet MAC reset [rw]
    RCC_AHBRSTR_OTGFSRST_FLAG  = (1u << 12u), // USB OTG FS reset [rw]
} RCC_AHBRSTR_FLAGS_enum;

/*
--| NAME: RCC_CFGR2_FLAGS_enum
--| DESCRIPTION: RCC Clock configuration register2 flags
*/
typedef enum RCC_CFGR2_FLAGS_Enumeration
{
    RCC_CFGR2_I2S3SRC_FLAG    = (1u << 18u), // I2S3 clock source [rw]
    RCC_CFGR2_I2S2SRC_FLAG    = (1u << 17u), // I2S2 clock source [rw]
    RCC_CFGR2_PREDIV1SRC_FLAG = (1u << 16u), // PREDIV1 entry clock source [rw]
} RCC_CFGR2_FLAGS_enum;

/*
--| NAME: RCC_CFGR2_PLL3MUL_MASKS_enum
--| DESCRIPTION: RCC CFGR2 PLL3 Multiplication Factor [4 bits, rw]
*/
typedef enum RCC_CFGR2_PLL3MUL_MASKS_Enumeration
{
    RCC_CFGR2_PLL3MUL_X_8       = 0b0110u, // PLL3 clock entry x 8
    RCC_CFGR2_PLL3MUL_X_9       = 0b0111u, // PLL3 clock entry x 9
    RCC_CFGR2_PLL3MUL_X_10      = 0b1000u, // PLL3 clock entry x 10
    RCC_CFGR2_PLL3MUL_X_11      = 0b1001u, // PLL3 clock entry x 11
    RCC_CFGR2_PLL3MUL_X_12      = 0b1010u, // PLL3 clock entry x 12
    RCC_CFGR2_PLL3MUL_X_13      = 0b1011u, // PLL3 clock entry x 13
    RCC_CFGR2_PLL3MUL_X_14      = 0b1100u, // PLL3 clock entry x 14
    RCC_CFGR2_PLL3MUL_X_16      = 0b1110u, // PLL3 clock entry x 16
    RCC_CFGR2_PLL3MUL_X_20      = 0b1111u, // PLL3 clock entry x 20
    RCC_CFGR2_PLL3MUL_SHIFT_AMT = 12u,     // Position of PLL3MUL in RCC CFGR2
} RCC_CFGR2_PLL3MUL_MASKS_enum;

/*
--| NAME: RCC_CFGR2_PLL2MUL_MASKS_enum
--| DESCRIPTION: RCC CFGR2 PLL2 Multiplication Factor [4 bits, rw]
*/
typedef enum RCC_CFGR2_PLL2MUL_MASKS_Enumeration
{
    RCC_CFGR2_PLL2MUL_X_8       = 0b0110u, // PLL2 clock entry x 8
    RCC_CFGR2_PLL2MUL_X_9       = 0b0111u, // PLL2 clock entry x 9
    RCC_CFGR2_PLL2MUL_X_10      = 0b1000u, // PLL2 clock entry x 10
    RCC_CFGR2_PLL2MUL_X_11      = 0b1001u, // PLL2 clock entry x 11
    RCC_CFGR2_PLL2MUL_X_12      = 0b1010u, // PLL2 clock entry x 12
    RCC_CFGR2_PLL2MUL_X_13      = 0b1011u, // PLL2 clock entry x 13
    RCC_CFGR2_PLL2MUL_X_14      = 0b1100u, // PLL2 clock entry x 14
    RCC_CFGR2_PLL2MUL_X_16      = 0b1110u, // PLL2 clock entry x 16
    RCC_CFGR2_PLL2MUL_X_20      = 0b1111u, // PLL2 clock entry x 20
    RCC_CFGR2_PLL2MUL_SHIFT_AMT = 8u,      // Position of PLL3MUL in RCC CFGR2
} RCC_CFGR2_PLL2MUL_MASKS_enum;

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

/* None */

#endif
