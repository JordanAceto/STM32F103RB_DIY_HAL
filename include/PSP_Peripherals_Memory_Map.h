/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   PSP_Peripherals_Memory_Map.h provides register addresses for the various
--|   peripherals on the STM32f103
--|  
--|----------------------------------------------------------------------------|
--| REFERENCES:
--|   stm32f103xb datasheet, page 34, figure 11     (stm32 peripherals)
--|   PM0056 programming manual, page 105, table 33 (cortex-m3 core peripherals)
--|
--|----------------------------------------------------------------------------|
*/

#ifndef PSP_PERIPHERALS_MEMORY_MAP_H_INCLUDED
#define PSP_PERIPHERALS_MEMORY_MAP_H_INCLUDED

/*
--|----------------------------------------------------------------------------|
--| INCLUDE FILES
--|----------------------------------------------------------------------------|
*/

/* None */

/*
--|----------------------------------------------------------------------------|
--| PUBLIC DEFINES
--|----------------------------------------------------------------------------|
*/

/*
--| STM32 PERIPHERALS
*/
#define PSP_PERIPHERAL_BASE (0x40000000u)

#define PSP_PERIPHERAL_CRC_BASE       (PSP_PERIPHERAL_BASE | 0x00023000u)

#define PSP_PERIPHERAL_FLASH_INT_BASE (PSP_PERIPHERAL_BASE | 0x00022000u)

#define PSP_PERIPHERAL_RCC_BASE       (PSP_PERIPHERAL_BASE | 0x00021000u)

#define PSP_PERIPHERAL_DMA_BASE       (PSP_PERIPHERAL_BASE | 0x00020000u)

#define PSP_PERIPHERAL_USART1_BASE    (PSP_PERIPHERAL_BASE | 0x00013800u)

#define PSP_PERIPHERAL_SPI1_BASE      (PSP_PERIPHERAL_BASE | 0x00013000u)
#define PSP_PERIPHERAL_TIM1_BASE      (PSP_PERIPHERAL_BASE | 0x00012C00u)
#define PSP_PERIPHERAL_ADC2_BASE      (PSP_PERIPHERAL_BASE | 0x00012800u)
#define PSP_PERIPHERAL_ADC1_BASE      (PSP_PERIPHERAL_BASE | 0x00012400u)

#define PSP_PERIPHERAL_PORTE_BASE     (PSP_PERIPHERAL_BASE | 0x00011800u)
#define PSP_PERIPHERAL_PORTD_BASE     (PSP_PERIPHERAL_BASE | 0x00011400u)
#define PSP_PERIPHERAL_PORTC_BASE     (PSP_PERIPHERAL_BASE | 0x00011000u)
#define PSP_PERIPHERAL_PORTB_BASE     (PSP_PERIPHERAL_BASE | 0x00010C00u)
#define PSP_PERIPHERAL_PORTA_BASE     (PSP_PERIPHERAL_BASE | 0x00010800u)
#define PSP_PERIPHERAL_EXTI_BASE      (PSP_PERIPHERAL_BASE | 0x00010400u)
#define PSP_PERIPHERAL_AFIO_BASE      (PSP_PERIPHERAL_BASE | 0x00010000u)

#define PSP_PERIPHERAL_PWR_BASE       (PSP_PERIPHERAL_BASE | 0x00007000u)
#define PSP_PERIPHERAL_BKP_BASE       (PSP_PERIPHERAL_BASE | 0x00006C00u)

#define PSP_PERIPHERAL_bxCAN_BASE     (PSP_PERIPHERAL_BASE | 0x00006400u)

#define PSP_PERIPHERAL_USB_BASE       (PSP_PERIPHERAL_BASE | 0x00005C00u)
#define PSP_PERIPHERAL_I2C2_BASE      (PSP_PERIPHERAL_BASE | 0x00005800u)
#define PSP_PERIPHERAL_I2C1_BASE      (PSP_PERIPHERAL_BASE | 0x00005400u)

#define PSP_PERIPHERAL_USART3_BASE    (PSP_PERIPHERAL_BASE | 0x00004800u)
#define PSP_PERIPHERAL_USART2_BASE    (PSP_PERIPHERAL_BASE | 0x00004400u)

#define PSP_PERIPHERAL_SPI2_BASE      (PSP_PERIPHERAL_BASE | 0x00003800u)

#define PSP_PERIPHERAL_IWDG_BASE      (PSP_PERIPHERAL_BASE | 0x00003000u)
#define PSP_PERIPHERAL_WWDG_BASE      (PSP_PERIPHERAL_BASE | 0x00002C00u)
#define PSP_PERIPHERAL_RTC_BASE       (PSP_PERIPHERAL_BASE | 0x00002800u)

#define PSP_PERIPHERAL_TIM4_BASE      (PSP_PERIPHERAL_BASE | 0x00000800u)
#define PSP_PERIPHERAL_TIM3_BASE      (PSP_PERIPHERAL_BASE | 0x00000400u)
#define PSP_PERIPHERAL_TIM2_BASE      (PSP_PERIPHERAL_BASE | 0x00000000u)

/*
--| CORTEX-M3 CORE PERIPHERALS
*/
#define PSP_CORE_PERIPHERAL_BASE      (0xE0000000u)

#define PSP_CORE_PERIPHERAL_STK_BASE  (PSP_CORE_PERIPHERAL_BASE | 0x0000E010u)
#define PSP_CORE_PERIPHERAL_NVIC_BASE (PSP_CORE_PERIPHERAL_BASE | 0x0000E100u)
#define PSP_CORE_PERIPHERAL_SCB_BASE  (PSP_CORE_PERIPHERAL_BASE | 0x0000ED00u)
#define PSP_CORE_PERIPHERAL_MPU_BASE  (PSP_CORE_PERIPHERAL_BASE | 0x0000ED90u)

/*
--|----------------------------------------------------------------------------|
--| PUBLIC TYPES
--|----------------------------------------------------------------------------|
*/

/* None */

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
