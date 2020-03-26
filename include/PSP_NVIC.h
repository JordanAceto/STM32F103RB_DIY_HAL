/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   PSP_NVIC.h provides types and interfaces for using the Nested Vector
--|   Interrupt Controller.
--|  
--|----------------------------------------------------------------------------|
--| REFERENCES:
--|   PM0056 programming manual, page 128
--|   stm32f10x reference manual, page 197
--|
--|----------------------------------------------------------------------------|
*/

#ifndef PSP_NVIC_H_INCLUDED
#define PSP_NVIC_H_INCLUDED

/*
--|----------------------------------------------------------------------------|
--| INCLUDE FILES
--|----------------------------------------------------------------------------|
*/

#include "Common_Typedefs.h"
#include "PSP_Peripherals_Memory_Map.h"

/*
--|----------------------------------------------------------------------------|
--| PUBLIC DEFINES
--|----------------------------------------------------------------------------|
*/

/*
--| NAME: NVIC
--| DESCRIPTION: Pointer to the NVIC
--| TYPE: NVIC_t*
*/
#define NVIC ((volatile NVIC_t *)PSP_CORE_PERIPHERAL_NVIC_BASE)

/*
--|----------------------------------------------------------------------------|
--| PUBLIC TYPES
--|----------------------------------------------------------------------------|
*/

/*
--| NAME: NVIC_t
--| DESCRIPTION: Nested Vector Interrupt Controller
*/
typedef struct NVIC_Type
{
    vuint32_t ISER[8u];         // Interrupt set-enable registers [32 bits per, rs]
     uint32_t RESERVED_0[24u];  // 
    vuint32_t ICER[8u];         // Interrupt clear-enable registers [32 bits per, rc_w1]
     uint32_t RESERVED_1[24u];  // 
    vuint32_t ISPR[8u];         // Interrupt set-pending registers [32 bits per, rs]
     uint32_t RESERVED_2[24u];  // 
    vuint32_t ICPR[8u];         // Interrupt clear-pending registers [32 bits per, rc_w1]
     uint32_t RESERVED_3[24u];  // 
    vuint32_t IABR[8u];         // Interrupt active bit registers [32 bits per, r]
     uint16_t RESERVED_4[56u];  // 
    vuint8_t  IP[240u];         // Interrupt priority registers [8 bits per, ?]
     uint32_t RESERVED_5[644u]; // 
    vuint16_t STIR;             // Software trigger interrupt register [9 bits, w]
} NVIC_t;

/*
--| NAME: IRQn_t
--| DESCRIPTION: Enumeration for Interrupt numbers
*/
typedef enum IRQn_Type
{
    /* Cortex-M3 processor exceptions */
    NMI_IRQn           = -14, // Non maskable interrupt
    HardFault_IRQn     = -13, // All class of fault
    MemManage_IRQn     = -12, // Memory management
    BusFault_IRQn      = -11, // Pre-fetch fault, memory access fault
    UsageFault_IRQn    = -10, // Undefined instruction or illegal state
    SVCall_IRQn        = -5,  // System service call via SWI instruction
    DebugMonitor_IRQn  = -4,  // Debug Monitor
    PendSV_IRQn        = -2,  // Pendable request for system service
    SysTick_IRQn       = -1,  // System tick timer
    
    /* STM32 specific interrupts */
    WWDG_IRQn          = 0,  // Window Watchdog interrupt
    PVD_IRQn           = 1,  // PVD through EXTI Line detection interrupt
    TAMPER_IRQn        = 2,  // Tamper interrupt
    RTC_IRQn           = 3,  // RTC global interrupt
    FLASH_IRQn         = 4,  // Flash global interrupt
    RCC_IRQn           = 5,  // RCC global interrupt
    EXTI0_IRQn         = 6,  // EXTI Line0 interrupt
    EXTI1_IRQn         = 7,  // EXTI Line1 interrupt
    EXTI2_IRQn         = 8,  // EXTI Line2 interrupt
    EXTI3_IRQn         = 9,  // EXTI Line3 interrupt
    EXTI4_IRQn         = 10, // EXTI Line4 interrupt
    DMA1_Channel1_IRQn = 11, // DMA1 Channel1 global interrupt
    DMA1_Channel2_IRQn = 12, // DMA1 Channel2 global interrupt
    DMA1_Channel3_IRQn = 13, // DMA1 Channel3 global interrupt
    DMA1_Channel4_IRQn = 14, // DMA1 Channel4 global interrupt
    DMA1_Channel5_IRQn = 15, // DMA1 Channel5 global interrupt
    DMA1_Channel6_IRQn = 16, // DMA1 Channel6 global interrupt
    DMA1_Channel7_IRQn = 17, // DMA1 Channel7 global interrupt
    ADC1_2_IRQn        = 18, // ADC1 and ADC2 global interrupt
    CAN1_TX_IRQn       = 19, // CAN1 TX interrupts
    CAN1_RX0_IRQn      = 20, // CAN1 RX0 interrupts
    CAN1_RX1_IRQn      = 21, // CAN1 RX1 interrupt
    CAN1_SCE_IRQn      = 22, // CAN1 SCE interrupt
    EXTI9_5_IRQn       = 23, // EXTI Line[9:5] interrupts
    TIM1_BRK_IRQn      = 24, // TIM1 Break interrupt
    TIM1_UP_IRQn       = 25, // TIM1 Update interrupt
    TIM1_TRG_COM_IRQn  = 26, // TIM1 Trigger and Commutation interrupts
    TIM1_CC_IRQn       = 27, // TIM1 Capture Compare interrupt
    TIM2_IRQn          = 28, // TIM2 global interrupt
    TIM3_IRQn          = 29, // TIM3 global interrupt
    TIM4_IRQn          = 30, // TIM4 global interrupt
    I2C1_EV_IRQn       = 31, // I2C1 event interrupt
    I2C1_ER_IRQn       = 32, // I2C1 error interrupt
    I2C2_EV_IRQn       = 33, // I2C2 event interrupt
    I2C2_ER_IRQn       = 34, // I2C2 error interrupt
    SPI1_IRQn          = 35, // SPI1 global interrupt
    SPI2_IRQn          = 36, // SPI2 global interrupt
    USART1_IRQn        = 37, // USART1 global interrupt
    USART2_IRQn        = 38, // USART2 global interrupt
    USART3_IRQn        = 39, // USART3 global interrupt
    EXTI15_10_IRQn     = 40, // EXTI Line[15:10] interrupts
    RTCAlarm_IRQn      = 41, // RTC alarm through EXTI line interrupt
    OTG_FS_WKUP_IRQn   = 42, // USB On-The-Go FS Wakeup through EXTI line interrupt
} IRQn_t;

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
