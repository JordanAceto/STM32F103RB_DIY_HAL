/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   PSP_TIMx.h provides types and interfaces for the general-purpose timers.
--|
--|----------------------------------------------------------------------------|
--| REFERENCES:
--|   stm32f10x reference manual, page 365
--|
--|----------------------------------------------------------------------------|
*/

#ifndef PSP_TIMX_H_INCLUDED
#define PSP_TIMX_H_INCLUDED

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
--| NAME: TIM1
--| DESCRIPTION: pointer to general purpose timer 1
--| TYPE: TIMx_t*
*/
#define TIM1 ((volatile TIMx_t *)PSP_PERIPHERAL_TIM1_BASE)

/*
--| NAME: TIM2
--| DESCRIPTION: pointer to general purpose timer 2
--| TYPE: TIMx_t*
*/
#define TIM2 ((volatile TIMx_t *)PSP_PERIPHERAL_TIM2_BASE)

/*
--| NAME: TIM3
--| DESCRIPTION: pointer to general purpose timer 3
--| TYPE: TIMx_t*
*/
#define TIM3 ((volatile TIMx_t *)PSP_PERIPHERAL_TIM3_BASE)

/*
--| NAME: TIM4
--| DESCRIPTION: pointer to general purpose timer 4
--| TYPE: TIMx_t*
*/
#define TIM4 ((volatile TIMx_t *)PSP_PERIPHERAL_TIM4_BASE)

/*
--|----------------------------------------------------------------------------|
--| PUBLIC TYPES
--|----------------------------------------------------------------------------|
*/

/*
--| NAME: TIMx_t
--| DESCRIPTION: General-purpose timer structure
*/
typedef struct TIMx_Type
{
    vuint32_t CR1;   // TIMx control register 1                
    vuint32_t CR2;   // TIMx control register 2                 
    vuint32_t SMCR;  // TIMx slave Mode Control register       
    vuint32_t DIER;  // TIMx DMA/interrupt enable register    
    vuint32_t SR;    // TIMx status register              
    vuint32_t EGR;   // TIMx event generation register         
    vuint32_t CCMR1; // TIMx capture/compare mode register 1 
    vuint32_t CCMR2; // TIMx capture/compare mode register 2
    vuint32_t CCER;  // TIMx capture/compare enable register
    vuint32_t CNT;   // TIMx counter register               
    vuint32_t PSC;   // TIMx prescaler register          
    vuint32_t ARR;   // TIMx auto-reload register 
    vuint32_t RCR;   // TIMx repetition counter register [is this supported on the stm32f103?]    
    vuint32_t CCR1;  // TIMx capture/compare register 1     
    vuint32_t CCR2;  // TIMx capture/compare register 2   
    vuint32_t CCR3;  // TIMx capture/compare register 3
    vuint32_t CCR4;  // TIMx capture/compare register 4
    vuint32_t BDTR;  // TIMx break and dead-time register
    vuint32_t DCR;   // TIMx DMA control register 
    vuint32_t DMAR;  // TIMx DMA address for full transfer register
    vuint32_t OR;    // TIMx option register [is this supported on the stm32f103?]
} TIMx_t;

/*
--| NAME: TIMx_CR1_FLAGS_enum
--| DESCRIPTION: TIMx control register 1 flags
*/
typedef enum TIMx_CR1_FLAGS_Enumeration
{
    TIMx_CR1_ARPE_FLAG = (1u << 7u), // Auto-reload preload enable [rw]
    TIMx_CR1_DIR_FLAG  = (1u << 4u), // Direction [rw]
    TIMx_CR1_OPM_FLAG  = (1u << 3u), // One-pulse mode [rw]
    TIMx_CR1_URS_FLAG  = (1u << 2u), // Update request source [rw]
    TIMx_CR1_UDIS_FLAG = (1u << 1u), // Update disable [rw]
    TIMx_CR1_CEN_FLAG  = (1u << 0u), // Counter enable [rw]
} TIMx_CR1_FLAGS_enum;

/*
--| NAME: TIMx_CR1_CKD_MASKS_enum
--| DESCRIPTION: TIMx CR1 Clock division masks [2 bits, rw]
*/
typedef enum TIMx_CR1_CKD_MASKS_Enumeration
{
    TIMx_CR1_CKD_Tdts_EQUALS_Tck_int     = 0b00u, // t_DTS = t_CK_INT
    TIMx_CR1_CKD_Tdts_EQUALS_2_x_Tck_int = 0b01u, // t_DTS = 2 x t_CK_INT
    TIMx_CR1_CKD_Tdts_EQUALS_4x_Tck_int  = 0b10u, // t_DTS = 4 x t_CK_INT
    TIMx_CR1_CKD_RESERVED                = 0b11u, // reserved
    TIMx_CR1_CKD_SHIFT_AMT               = 8u,    // position of CKD in TIMx CR1
} TIMx_CR1_CKD_MASKS_enum;

/*
--| NAME: TIMx_CR1_CMS_MASKS_enum
--| DESCRIPTION: TIMx CR1 Center-aligned mode selection masks [2 bits, rw]
*/
typedef enum TIMx_CR1_CMS_MASKS_Enumeration
{
    TIMx_CR1_CMS_EDGE_ALIGNED_MODE     = 0b00u, // Edge-aligned mode
    TIMx_CR1_CMS_CENTER_ALIGNED_MODE_1 = 0b01u, // Center-aligned mode 1
    TIMx_CR1_CMS_CENTER_ALIGNED_MODE_2 = 0b10u, // Center-aligned mode 2
    TIMx_CR1_CMS_CENTER_ALIGNED_MODE_3 = 0b11u, // Center-aligned mode 3
    TIMx_CR1_CMS_SHIFT_AMT             = 5u,    // position of CMS in TIMx CR1
} TIMx_CR1_CMS_MASKS_enum;

/*
--| NAME: TIMx_CR2_FLAGS_enum
--| DESCRIPTION: TIMx control register 2 flags
*/
typedef enum TIMx_CR2_FLAGS_Enumeration
{
    TIMx_CR2_TI1S_FLAGS = (1u << 7u), // TI1 selection [rw]
    TIMx_CR2_CCDS_FLAGS = (1u << 3u), // Capture/compare DMA selection [rw]
} TIMx_CR2_FLAGS_enum;

/*
--| NAME: TIMx_CR2_MMS_MASKS_enum
--| DESCRIPTION: TIMx CR2 Master mode selection masks [3 bits, rw]
*/
typedef enum TIMx_CR2_MMS_MASKS_Enumeration
{
    TIMx_CR2_MMS_RESET          = 0b000u, // UG bit from TIMx_EGR register used as trigger output
    TIMx_CR2_MMS_ENABLE         = 0b001u, // Counter enable signal, CNT_EN, used as trigger output
    TIMx_CR2_MMS_UPDATE         = 0b010u, // update event is selected as trigger output
    TIMx_CR2_MMS_COMPARE_PULSE  = 0b011u, // positive pulse when the CC1IF flag is to be set
    TIMx_CR2_MMS_COMPARE_OC1REF = 0b100u, // OC1REF signal is used as trigger output
    TIMx_CR2_MMS_COMPARE_OC2REF = 0b101u, // OC2REF signal is used as trigger output
    TIMx_CR2_MMS_COMPARE_OC3REF = 0b110u, // OC3REF signal is used as trigger output
    TIMx_CR2_MMS_COMPARE_OC4REF = 0b111u, // OC4REF signal is used as trigger output
    TIMx_CR2_MMS_SHIFT_AMT      = 4u,     // position of MMS in TIMx CR2
} TIMx_CR2_MMS_MASKS_enum;

/*
--| NAME: TIMx_SMCR_FLAGS_enum
--| DESCRIPTION: TIMx slave mode control register flags
*/
typedef enum TIMx_SMCR_FLAGS_Enumeration
{
    TIMx_SMCR_ETP_FLAG = (1u << 15u), // External trigger polarity [rw]
    TIMx_SMCR_EXE_FLAG = (1u << 14u), // External clock enable [rw]
    TIMx_SMCR_MSM_FLAG = (1u << 7u),  // Master/Slave mode [rw]
} TIMx_SMCR_FLAGS_enum;

/*
--| NAME: TIMx_SCMR_ETPS_MASKS_enum
--| DESCRIPTION: TIMx SMCR External trigger prescaler masks [2 bits, rw]
*/
typedef enum TIMx_SMCR_ETPS_MASKS_Enumeration
{
    TIMx_CR2_SMCR_ETPS_PRESCALER_OFF = 0b00u, // Prescaler OFF
    TIMx_CR2_SMCR_ETPS_ETRP_DIV_2    = 0b01u, // ETRP frequency divided by 2
    TIMx_CR2_SMCR_ETPS_ETRP_DIV_4    = 0b10u, // ETRP frequency divided by 4
    TIMx_CR2_SMCR_ETPS_ETRP_DIV_8    = 0b11u, // ETRP frequency divided by 8
    TIMx_CR2_SMCR_ETPS_SHIFT_AMT     = 12u,   // position of ETPS in TIMx SMCR
} TIMx_SMCR_ETPS_MASKS_enum;

/*
--| NAME: TIMx_SCMR_ETF_MASKS_enum
--| DESCRIPTION: TIMx SMCR External trigger prescaler masks [4 bits, rw]
*/
typedef enum TIMx_SMCR_ETF_MASKS_Enumeration
{
    TIMx_CR2_SMCR_ETF_NO_FILTER      = 0b0000u, // Prescaler OFF
    TIMx_CR2_SMCR_ETF_FILTER_MODE_1  = 0b0001u, // f SAMPLING =f CK_INT , N=2
    TIMx_CR2_SMCR_ETF_FILTER_MODE_2  = 0b0010u, // f SAMPLING =f CK_INT , N=4
    TIMx_CR2_SMCR_ETF_FILTER_MODE_3  = 0b0011u, // f SAMPLING =f CK_INT , N=8^2
    TIMx_CR2_SMCR_ETF_FILTER_MODE_4  = 0b0100u, // f SAMPLING =f DTS /2, N=6
    TIMx_CR2_SMCR_ETF_FILTER_MODE_5  = 0b0101u, // f SAMPLING =f DTS /2, N=8
    TIMx_CR2_SMCR_ETF_FILTER_MODE_6  = 0b0110u, // f SAMPLING =f DTS /4, N=6^2
    TIMx_CR2_SMCR_ETF_FILTER_MODE_7  = 0b0111u, // f SAMPLING =f DTS /4, N=8
    TIMx_CR2_SMCR_ETF_FILTER_MODE_8  = 0b1000u, // f SAMPLING =f DTS /8, N=6
    TIMx_CR2_SMCR_ETF_FILTER_MODE_9  = 0b1001u, // f SAMPLING =f DTS /8, N=8
    TIMx_CR2_SMCR_ETF_FILTER_MODE_10 = 0b1010u, // f SAMPLING =f DTS /16, N=5
    TIMx_CR2_SMCR_ETF_FILTER_MODE_11 = 0b1011u, // f SAMPLING =f DTS /16, N=6
    TIMx_CR2_SMCR_ETF_FILTER_MODE_12 = 0b1100u, // f SAMPLING =f DTS /16, N=8
    TIMx_CR2_SMCR_ETF_FILTER_MODE_13 = 0b1101u, // f SAMPLING =f DTS /32, N=5
    TIMx_CR2_SMCR_ETF_FILTER_MODE_14 = 0b1110u, // f SAMPLING =f DTS /32, N=6
    TIMx_CR2_SMCR_ETF_FILTER_MODE_15 = 0b1111u, // f SAMPLING =f DTS /32, N=8
    TIMx_CR2_SMCR_ETF_SHIFT_AMT      = 8u,      // position of ETF in TIMx SMCR
} TIMx_SMCR_ETF_MASKS_enum;

/*
--| NAME: TIMx_SCMR_TS_MASKS_enum
--| DESCRIPTION: TIMx SMCR Trigger selection masks [3 bits, rw]
*/
typedef enum TIMx_SMCR_TS_MASKS_Enumeration
{
    TIMx_CR2_SMCR_TS_INT_TRIG_0             = 0b000u, // Internal Trigger 0 (ITR0)
    TIMx_CR2_SMCR_TS_INT_TRIG_1             = 0b001u, // Internal Trigger 1 (ITR1)
    TIMx_CR2_SMCR_TS_INT_TRIG_2             = 0b010u, // Internal Trigger 2 (ITR2)
    TIMx_CR2_SMCR_TS_INT_TRIG_3             = 0b011u, // Internal Trigger 3 (ITR3)
    TIMx_CR2_SMCR_TS_TI1_EDGE_DETECT        = 0b100u, // TI1 Edge Detector (TI1F_ED)
    TIMx_CR2_SMCR_TS_FILTERED_TIMER_INPUT_1 = 0b101u, // Filtered Timer Input 1 (TI1FP1)
    TIMx_CR2_SMCR_TS_FILTERED_TIMER_INPUT_1 = 0b110u, // Filtered Timer Input 2 (TI2FP2)
    TIMx_CR2_SMCR_TS_EXTERNAL_TRIGGER_INPUT = 0b111u, // External Trigger input (ETRF)
    TIMx_CR2_SMCR_TS_SHIFT_AMT              = 4u,     // position of TS in TIMx SMCR
} TIMx_SMCR_TS_MASKS_enum;

/*
--| NAME: TIMx_SMCR_SMS_MASKS_enum
--| DESCRIPTION: TIMx SMCR Slave mode selection masks [3 bits, rw]
*/
typedef enum TIMx_SMCR_SMS_MASKS_Enumeration
{
    TIMx_CR2_SMCR_SMS_SLAVE_MODE_DISABLED = 0b000u, // Slave mode disabled
    TIMx_CR2_SMCR_SMS_ENCODER_MODE_1      = 0b001u, // Encoder mode 1
    TIMx_CR2_SMCR_SMS_ENCODER_MODE_2      = 0b010u, // Encoder mode 2
    TIMx_CR2_SMCR_SMS_ENCODER_MODE_3      = 0b011u, // Encoder mode 3
    TIMx_CR2_SMCR_SMS_RESET_MODE          = 0b100u, // Reset Mode
    TIMx_CR2_SMCR_SMS_GATED_MODE          = 0b101u, // Gated Mode
    TIMx_CR2_SMCR_SMS_TRIGGER_MODE        = 0b110u, // Trigger Mode
    TIMx_CR2_SMCR_SMS_EXT_CLOCK_MODE_1    = 0b111u, // External Clock Mode 1
    TIMx_CR2_SMCR_SMS_SHIFT_AMT           = 0u,     // position of SMS in TIMx SMCR
} TIMx_SMCR_SMS_MASKS_enum;

/*
--| NAME: TIMx_DIER_FLAGS_enum
--| DESCRIPTION: TIMx DMA/Interrupt enable register flags
*/
typedef enum TIMx_DIER_FLAGS_Enumeration
{
    TIMx_DIER_TDE_FLAG   = (1u << 14u), // Trigger DMA request enable [rw]
    TIMx_DIER_CC4DE_FLAG = (1u << 12u), // Capture/Compare 4 DMA request enable [rw]
    TIMx_DIER_CC3DE_FLAG = (1u << 11u), // Capture/Compare 3 DMA request enable [rw]
    TIMx_DIER_CC2DE_FLAG = (1u << 10u), // Capture/Compare 2 DMA request enable [rw]
    TIMx_DIER_CC1DE_FLAG = (1u << 9u),  // Capture/Compare 1 DMA request enable [rw]
    TIMx_DIER_UDE_FLAG   = (1u << 8u),  // Update DMA request enable [rw]
    TIMx_DIER_TIE_FLAG   = (1u << 6u),  // Trigger interrupt enable [rw]
    TIMx_DIER_CC4IE_FLAG = (1u << 4u),  // Capture/Compare 4 interrupt enable [rw]
    TIMx_DIER_CC3IE_FLAG = (1u << 3u),  // Capture/Compare 3 interrupt enable [rw]
    TIMx_DIER_CC2IE_FLAG = (1u << 2u),  // Capture/Compare 2 interrupt enable [rw]
    TIMx_DIER_CC1IE_FLAG = (1u << 1u),  // Capture/Compare 1 interrupt enable [rw]
    TIMx_DIER_UIE_FLAG   = (1u << 0u),  // Update interrupt enable [rw]
} TIMx_DIER_FLAGS_enum;

/*
--| NAME: TIMx_SR_FLAGS_enum
--| DESCRIPTION: TIMx status register flags
*/
typedef enum TIMx_SR_FLAGS_Enumeration
{
    TIMx_SR_CC4OF_FLAG = (1u << 12u), // Capture/Compare 4 overcapture flag [rc_w0]
    TIMx_SR_CC3OF_FLAG = (1u << 11u), // Capture/Compare 3 overcapture flag [rc_w0]
    TIMx_SR_CC2OF_FLAG = (1u << 10u), // Capture/Compare 2 overcapture flag [rc_w0]
    TIMx_SR_CC1OF_FLAG = (1u << 9u),  // Capture/Compare 1 overcapture flag [rc_w0]
    TIMx_SR_TIF_FLAG   = (1u << 6u),  // Trigger interrupt flag [rc_w0]
    TIMx_SR_CC4IF_FLAG = (1u << 4u),  // Capture/Compare 4 interrupt flag [rc_w0]
    TIMx_SR_CC3IF_FLAG = (1u << 3u),  // Capture/Compare 3 interrupt flag [rc_w0]
    TIMx_SR_CC2IF_FLAG = (1u << 2u),  // Capture/Compare 2 interrupt flag [rc_w0]
    TIMx_SR_CC1IF_FLAG = (1u << 1u),  // Capture/Compare 1 interrupt flag [rc_w0]
    TIMx_SR_UIF_FLAG   = (1u << 0u),  // Update interrupt flag [rc_w0]
} TIMx_SR_FLAGS_enum;

/*
--| NAME: TIMx_EGR_FLAGS_enum
--| DESCRIPTION: TIMx event generation register flags
*/
typedef enum TIMx_EGR_FLAGS_Enumeration
{
    TIMx_EGR_TG_FLAG   = (1u << 6u), // Trigger generation [w]
    TIMx_EGR_CC4G_FLAG = (1u << 4u), // Capture/compare 4 generation [w]
    TIMx_EGR_CC3G_FLAG = (1u << 3u), // Capture/compare 3 generation [w]
    TIMx_EGR_CC2G_FLAG = (1u << 2u), // Capture/compare 2 generation [w]
    TIMx_EGR_CC1G_FLAG = (1u << 1u), // Capture/compare 1 generation [w]
    TIMx_EGR_UG_FLAG   = (1u << 0u), // Update generation [w]
} TIMx_EGR_FLAGS_enum;

/*
--| NAME: TIMx_CCMR1_FLAGS_enum
--| DESCRIPTION: TIMx capture/compare mode register 1 flags
*/
typedef enum TIMx_CCMR1_FLAGS_Enumeration
{
    TIMx_CCMR1_OC2CE_FLAG = (1u << 15u), // Output compare 2 clear enable [rw]
    TIMx_CCMR1_OC2PE_FLAG = (1u << 11u), // Output compare 2 preload enable [rw]
    TIMx_CCMR1_OC2FE_FLAG = (1u << 10u), // Output compare 2 fast enable [rw]
    TIMx_CCMR1_OC1CE_FLAG = (1u << 7u),  // Output compare 1 clear enable [rw]
    TIMx_CCMR1_OC1PE_FLAG = (1u << 3u),  // Output compare 1 preload enable [rw]
    TIMx_CCMR1_OC1FE_FLAG = (1u << 2u),  // Output compare 1 fast enable [rw]
} TIMx_CCMR1_FLAGS_enum;

/*
--| NAME: TIMx_CCMR1_OC2M_MASKS_enum
--| DESCRIPTION: TIMx CCMR1 Output compare 2 mode masks [3 bits, rw]
*/
typedef enum TIMx_CCMR1_OC2M_MASKS_Enumeration
{
    TIMx_CCMR1_OC2M_FROZEN                  = 0b000u, // Frozen
    TIMx_CCMR1_OC2M_ACTIVE_LEVEL_ON_MATCH   = 0b001u, // Set channel 2 to active level on match
    TIMx_CCMR1_OC2M_INACTIVE_LEVEL_ON_MATCH = 0b010u, // Set channel 2 to inactive level on match
    TIMx_CCMR1_OC2M_TOGGLE                  = 0b011u, // OC2REF toggles when TIMx_CNT=TIMx_CCR2
    TIMx_CCMR1_OC2M_FORCE_INACTIVE_LEVEL    = 0b100u, // Force inactive level - OC2REF is forced low
    TIMx_CCMR1_OC2M_FORCE_ACTIVE_LEVEL      = 0b101u, // Force active level - OC2REF is forced high
    TIMx_CCMR1_OC2M_PWM_MODE_1              = 0b110u, // PWM mode 1
    TIMx_CCMR1_OC2M_PWM_MODE_2              = 0b111u, // PWM mode 2
    TIMx_CCMR1_OC2M_SHIFT_AMT               = 12u,    // position of OC2M in TIMx CCMR1
} TIMx_CCMR1_OC2M_MASKS_enum;

/*
--| NAME: TIMx_CCMR1_CC2S_MASKS_enum
--| DESCRIPTION: TIMx CCMR1 Capture/Compare 2 selection masks [2 bits, rw]
*/
typedef enum TIMx_CCMR1_CC2S_MASKS_Enumeration
{
    TIMx_CCMR1_CC2S_OUTPUT        = 0b00u, // CC2 channel is configured as output
    TIMx_CCMR1_CC2S_INPUT_MAP_TI2 = 0b01u, // CC2 channel is configured as input, IC2 is mapped on TI2
    TIMx_CCMR1_CC2S_INPUT_MAP_TI1 = 0b10u, // CC2 channel is configured as input, IC2 is mapped on TI1
    TIMx_CCMR1_CC2S_INPUT_MAP_TRC = 0b11u, // CC2 channel is configured as input, IC2 is mapped on TRC
    TIMx_CCMR1_CC2S_SHIFT_AMT     = 8u,    // position of CC2S in TIMx CCMR1
} TIMx_CCMR1_CC2S_MASKS_enum;

/*
--| NAME: TIMx_CCMR1_OC1M_MASKS_enum
--| DESCRIPTION: TIMx CCMR1 Output compare 1 mode masks [3 bits, rw]
*/
typedef enum TIMx_CCMR1_OC1M_MASKS_Enumeration
{
    TIMx_CCMR1_OC1M_FROZEN                  = 0b000u, // Frozen
    TIMx_CCMR1_OC1M_ACTIVE_LEVEL_ON_MATCH   = 0b001u, // Set channel 1 to active level on match
    TIMx_CCMR1_OC1M_INACTIVE_LEVEL_ON_MATCH = 0b010u, // Set channel 1 to inactive level on match
    TIMx_CCMR1_OC1M_TOGGLE                  = 0b011u, // OC1REF toggles when TIMx_CNT=TIMx_CCR1
    TIMx_CCMR1_OC1M_FORCE_INACTIVE_LEVEL    = 0b100u, // Force inactive level - OC1REF is forced low
    TIMx_CCMR1_OC1M_FORCE_ACTIVE_LEVEL      = 0b101u, // Force active level - OC1REF is forced high
    TIMx_CCMR1_OC1M_PWM_MODE_1              = 0b110u, // PWM mode 1
    TIMx_CCMR1_OC1M_PWM_MODE_2              = 0b111u, // PWM mode 2
    TIMx_CCMR1_OC1M_SHIFT_AMT               = 4u,     // position of OC1M in TIMx CCMR1
} TIMx_CCMR1_OC1M_MASKS_enum;

/*
--| NAME: TIMx_CCMR1_CC1S_MASKS_enum
--| DESCRIPTION: TIMx CCMR1 Capture/Compare 1 selection masks [2 bits, rw]
*/
typedef enum TIMx_CCMR1_CC1S_MASKS_Enumeration
{
    TIMx_CCMR1_CC1S_OUTPUT        = 0b00u, // CC1 channel is configured as output
    TIMx_CCMR1_CC1S_INPUT_MAP_TI1 = 0b01u, // CC1 channel is configured as input, IC1 is mapped on TI1
    TIMx_CCMR1_CC1S_INPUT_MAP_TI2 = 0b10u, // CC1 channel is configured as input, IC1 is mapped on TI2
    TIMx_CCMR1_CC1S_INPUT_MAP_TRC = 0b11u, // CC1 channel is configured as input, IC1 is mapped on TRC
    TIMx_CCMR1_CC1S_SHIFT_AMT     = 0u,    // position of CC1S in TIMx CCMR1
} TIMx_CCMR1_CC1S_MASKS_enum;

/*
--| NAME: TIMx_CCMR1_IC2F_MASKS_enum
--| DESCRIPTION: TIMx CCMR1 Input capture 2 filter masks [4 bits, rw]
*/
typedef enum TIMx_CCMR1_IC2F_MASKS_Enumeration
{
    TIMx_CCMR1_IC2F_NO_FILTER      = 0b0000u, // Prescaler OFF
    TIMx_CCMR1_IC2F_FILTER_MODE_1  = 0b0001u, // f SAMPLING =f CK_INT , N=2
    TIMx_CCMR1_IC2F_FILTER_MODE_2  = 0b0010u, // f SAMPLING =f CK_INT , N=4
    TIMx_CCMR1_IC2F_FILTER_MODE_3  = 0b0011u, // f SAMPLING =f CK_INT , N=8^2
    TIMx_CCMR1_IC2F_FILTER_MODE_4  = 0b0100u, // f SAMPLING =f DTS /2, N=6
    TIMx_CCMR1_IC2F_FILTER_MODE_5  = 0b0101u, // f SAMPLING =f DTS /2, N=8
    TIMx_CCMR1_IC2F_FILTER_MODE_6  = 0b0110u, // f SAMPLING =f DTS /4, N=6^2
    TIMx_CCMR1_IC2F_FILTER_MODE_7  = 0b0111u, // f SAMPLING =f DTS /4, N=8
    TIMx_CCMR1_IC2F_FILTER_MODE_8  = 0b1000u, // f SAMPLING =f DTS /8, N=6
    TIMx_CCMR1_IC2F_FILTER_MODE_9  = 0b1001u, // f SAMPLING =f DTS /8, N=8
    TIMx_CCMR1_IC2F_FILTER_MODE_10 = 0b1010u, // f SAMPLING =f DTS /16, N=5
    TIMx_CCMR1_IC2F_FILTER_MODE_11 = 0b1011u, // f SAMPLING =f DTS /16, N=6
    TIMx_CCMR1_IC2F_FILTER_MODE_12 = 0b1100u, // f SAMPLING =f DTS /16, N=8
    TIMx_CCMR1_IC2F_FILTER_MODE_13 = 0b1101u, // f SAMPLING =f DTS /32, N=5
    TIMx_CCMR1_IC2F_FILTER_MODE_14 = 0b1110u, // f SAMPLING =f DTS /32, N=6
    TIMx_CCMR1_IC2F_FILTER_MODE_15 = 0b1111u, // f SAMPLING =f DTS /32, N=8
    TIMx_CCMR1_IC2F_SHIFT_AMT      = 12u,     // position of IC2F in TIMx CCMR1
} TIMx_CCMR1_IC2F_MASKS_enum;

/*
--| NAME: TIMx_CCMR1_IC2PSC_MASKS_enum
--| DESCRIPTION: TIMx CCMR1 Input capture 2 prescaler masks [2 bits, rw]
*/
typedef enum TIMx_CCMR1_IC2PSC_MASKS_Enumeration
{
    TIMx_CCMR1_IC2PSC_NO_PRESCALER           = 0b00u, // no prescaler
    TIMx_CCMR1_IC2PSC_CAPTURE_EVERY_2_EVENTS = 0b01u, // capture is done once every 2 events
    TIMx_CCMR1_IC2PSC_CAPTURE_EVERY_4_EVENTS = 0b10u, // capture is done once every 4 events
    TIMx_CCMR1_IC2PSC_CAPTURE_EVERY_8_EVENTS = 0b11u, // capture is done once every 8 events
    TIMx_CCMR1_IC2PSC_SHIFT_AMT              = 10u    // position of IC2PSC in TIMx CCMR1
} TIMx_CCMR1_IC2PSC_MASKS_enum;

/*
--| NAME: TIMx_CCMR1_IC1F_MASKS_enum
--| DESCRIPTION: TIMx CCMR1 Input capture 1 filter masks [4 bits, rw]
*/
typedef enum TIMx_CCMR1_IC1F_MASKS_Enumeration
{
    TIMx_CCMR1_IC1F_NO_FILTER      = 0b0000u, // Prescaler OFF
    TIMx_CCMR1_IC1F_FILTER_MODE_1  = 0b0001u, // f SAMPLING =f CK_INT , N=2
    TIMx_CCMR1_IC1F_FILTER_MODE_2  = 0b0010u, // f SAMPLING =f CK_INT , N=4
    TIMx_CCMR1_IC1F_FILTER_MODE_3  = 0b0011u, // f SAMPLING =f CK_INT , N=8^2
    TIMx_CCMR1_IC1F_FILTER_MODE_4  = 0b0100u, // f SAMPLING =f DTS /2, N=6
    TIMx_CCMR1_IC1F_FILTER_MODE_5  = 0b0101u, // f SAMPLING =f DTS /2, N=8
    TIMx_CCMR1_IC1F_FILTER_MODE_6  = 0b0110u, // f SAMPLING =f DTS /4, N=6^2
    TIMx_CCMR1_IC1F_FILTER_MODE_7  = 0b0111u, // f SAMPLING =f DTS /4, N=8
    TIMx_CCMR1_IC1F_FILTER_MODE_8  = 0b1000u, // f SAMPLING =f DTS /8, N=6
    TIMx_CCMR1_IC1F_FILTER_MODE_9  = 0b1001u, // f SAMPLING =f DTS /8, N=8
    TIMx_CCMR1_IC1F_FILTER_MODE_10 = 0b1010u, // f SAMPLING =f DTS /16, N=5
    TIMx_CCMR1_IC1F_FILTER_MODE_11 = 0b1011u, // f SAMPLING =f DTS /16, N=6
    TIMx_CCMR1_IC1F_FILTER_MODE_12 = 0b1100u, // f SAMPLING =f DTS /16, N=8
    TIMx_CCMR1_IC1F_FILTER_MODE_13 = 0b1101u, // f SAMPLING =f DTS /32, N=5
    TIMx_CCMR1_IC1F_FILTER_MODE_14 = 0b1110u, // f SAMPLING =f DTS /32, N=6
    TIMx_CCMR1_IC1F_FILTER_MODE_15 = 0b1111u, // f SAMPLING =f DTS /32, N=8
    TIMx_CCMR1_IC1F_SHIFT_AMT      = 4u,      // position of IC1F in TIMx CCMR1
} TIMx_CCMR1_IC1F_MASKS_enum;

/*
--| NAME: TIMx_CCMR1_IC1PSC_MASKS_enum
--| DESCRIPTION: TIMx CCMR1 Input capture 1 prescaler masks [2 bits, rw]
*/
typedef enum TIMx_CCMR1_IC1PSC_MASKS_Enumeration
{
    TIMx_CCMR1_IC1PSC_NO_PRESCALER           = 0b00u, // no prescaler
    TIMx_CCMR1_IC1PSC_CAPTURE_EVERY_2_EVENTS = 0b01u, // capture is done once every 2 events
    TIMx_CCMR1_IC1PSC_CAPTURE_EVERY_4_EVENTS = 0b10u, // capture is done once every 4 events
    TIMx_CCMR1_IC1PSC_CAPTURE_EVERY_8_EVENTS = 0b11u, // capture is done once every 8 events
    TIMx_CCMR1_IC1PSC_SHIFT_AMT              = 2u     // position of IC1PSC in TIMx CCMR1
} TIMx_CCMR1_IC1PSC_MASKS_enum;

/*
--| NAME: TIMx_CCMR2_FLAGS_enum
--| DESCRIPTION: TIMx capture/compare mode register 2 flags
*/
typedef enum TIMx_CCMR2_FLAGS_Enumeration
{
    TIMx_CCMR2_OC4CE_FLAG = (1u << 15u), // Output compare 4 clear enable [rw]
    TIMx_CCMR2_OC4PE_FLAG = (1u << 11u), // Output compare 4 preload enable [rw]
    TIMx_CCMR2_OC4FE_FLAG = (1u << 10u), // Output compare 4 fast enable [rw]
    TIMx_CCMR2_OC3CE_FLAG = (1u << 7u),  // Output compare 3 clear enable [rw]
    TIMx_CCMR2_OC3PE_FLAG = (1u << 3u),  // Output compare 3 preload enable [rw]
    TIMx_CCMR2_OC3FE_FLAG = (1u << 2u),  // Output compare 3 fast enable [rw]
} TIMx_CCMR2_FLAGS_enum;

/*
--| NAME: TIMx_CCMR2_OC4M_MASKS_enum
--| DESCRIPTION: TIMx CCMR2 Output compare 4 mode masks [3 bits, rw]
*/
typedef enum TIMx_CCMR2_OC4M_MASKS_Enumeration
{
    TIMx_CCMR2_OC4M_FROZEN                  = 0b000u, // Frozen
    TIMx_CCMR2_OC4M_ACTIVE_LEVEL_ON_MATCH   = 0b001u, // Set channel 4 to active level on match
    TIMx_CCMR2_OC4M_INACTIVE_LEVEL_ON_MATCH = 0b010u, // Set channel 4 to inactive level on match
    TIMx_CCMR2_OC4M_TOGGLE                  = 0b011u, // OC4REF toggles when TIMx_CNT=TIMx_CCR4
    TIMx_CCMR2_OC4M_FORCE_INACTIVE_LEVEL    = 0b100u, // Force inactive level - OC4REF is forced low
    TIMx_CCMR2_OC4M_FORCE_ACTIVE_LEVEL      = 0b101u, // Force active level - OC4REF is forced high
    TIMx_CCMR2_OC4M_PWM_MODE_1              = 0b110u, // PWM mode 1
    TIMx_CCMR2_OC4M_PWM_MODE_2              = 0b111u, // PWM mode 2
    TIMx_CCMR2_OC4M_SHIFT_AMT               = 12u,    // position of OC4M in TIMx CCMR2
} TIMx_CCMR2_OC4M_MASKS_enum;

/*
--| NAME: TIMx_CCMR2_CC4S_MASKS_enum
--| DESCRIPTION: TIMx CCMR2 Capture/Compare 4 selection masks [2 bits, rw]
*/
typedef enum TIMx_CCMR2_CC4S_MASKS_Enumeration
{
    TIMx_CCMR2_CC4S_OUTPUT        = 0b00u, // CC4 channel is configured as output
    TIMx_CCMR2_CC4S_INPUT_MAP_TI4 = 0b01u, // CC4 channel is configured as input, IC4 is mapped on TI4
    TIMx_CCMR2_CC4S_INPUT_MAP_TI3 = 0b10u, // CC4 channel is configured as input, IC4 is mapped on TI3
    TIMx_CCMR2_CC4S_INPUT_MAP_TRC = 0b11u, // CC4 channel is configured as input, IC4 is mapped on TRC
    TIMx_CCMR2_CC4S_SHIFT_AMT     = 8u,    // position of CC4S in TIMx CCMR2
} TIMx_CCMR2_CC4S_MASKS_enum;

/*
--| NAME: TIMx_CCMR2_OC3M_MASKS_enum
--| DESCRIPTION: TIMx CCMR2 Output compare 3 mode masks [3 bits, rw]
*/
typedef enum TIMx_CCMR1_OC1M_MASKS_Enumeration
{
    TIMx_CCMR2_OC3M_FROZEN                  = 0b000u, // Frozen
    TIMx_CCMR2_OC3M_ACTIVE_LEVEL_ON_MATCH   = 0b001u, // Set channel 3 to active level on match
    TIMx_CCMR2_OC3M_INACTIVE_LEVEL_ON_MATCH = 0b010u, // Set channel 3 to inactive level on match
    TIMx_CCMR2_OC3M_TOGGLE                  = 0b011u, // OC3REF toggles when TIMx_CNT=TIMx_CCR3
    TIMx_CCMR2_OC3M_FORCE_INACTIVE_LEVEL    = 0b100u, // Force inactive level - OC3REF is forced low
    TIMx_CCMR2_OC3M_FORCE_ACTIVE_LEVEL      = 0b101u, // Force active level - OC3REF is forced high
    TIMx_CCMR2_OC3M_PWM_MODE_1              = 0b110u, // PWM mode 1
    TIMx_CCMR2_OC3M_PWM_MODE_2              = 0b111u, // PWM mode 2
    TIMx_CCMR2_OC3M_SHIFT_AMT               = 4u,     // position of OC3M in TIMx CCMR2
} TIMx_CCMR2_OC3M_MASKS_enum;

/*
--| NAME: TIMx_CCMR2_CC3S_MASKS_enum
--| DESCRIPTION: TIMx CCMR2 Capture/Compare 3 selection masks [2 bits, rw]
*/
typedef enum TIMx_CCMR2_CC3S_MASKS_Enumeration
{
    TIMx_CCMR2_CC3S_OUTPUT        = 0b00u, // CC3 channel is configured as output
    TIMx_CCMR2_CC3S_INPUT_MAP_TI3 = 0b01u, // CC3 channel is configured as input, IC3 is mapped on TI3
    TIMx_CCMR2_CC3S_INPUT_MAP_TI4 = 0b10u, // CC3 channel is configured as input, IC3 is mapped on TI4
    TIMx_CCMR2_CC3S_INPUT_MAP_TRC = 0b11u, // CC3 channel is configured as input, IC3 is mapped on TRC
    TIMx_CCMR2_CC3S_SHIFT_AMT     = 0u,    // position of CC3S in TIMx CCMR2
} TIMx_CCMR2_CC3S_MASKS_enum;

/*
--| NAME: TIMx_CCMR2_IC4F_MASKS_enum
--| DESCRIPTION: TIMx CCMR2 Input capture 4 filter masks [4 bits, rw]
*/
typedef enum TIMx_CCMR2_IC4F_MASKS_Enumeration
{
    TIMx_CCMR2_IC4F_NO_FILTER      = 0b0000u, // Prescaler OFF
    TIMx_CCMR2_IC4F_FILTER_MODE_1  = 0b0001u, // f SAMPLING =f CK_INT , N=2
    TIMx_CCMR2_IC4F_FILTER_MODE_2  = 0b0010u, // f SAMPLING =f CK_INT , N=4
    TIMx_CCMR2_IC4F_FILTER_MODE_3  = 0b0011u, // f SAMPLING =f CK_INT , N=8^2
    TIMx_CCMR2_IC4F_FILTER_MODE_4  = 0b0100u, // f SAMPLING =f DTS /2, N=6
    TIMx_CCMR2_IC4F_FILTER_MODE_5  = 0b0101u, // f SAMPLING =f DTS /2, N=8
    TIMx_CCMR2_IC4F_FILTER_MODE_6  = 0b0110u, // f SAMPLING =f DTS /4, N=6^2
    TIMx_CCMR2_IC4F_FILTER_MODE_7  = 0b0111u, // f SAMPLING =f DTS /4, N=8
    TIMx_CCMR2_IC4F_FILTER_MODE_8  = 0b1000u, // f SAMPLING =f DTS /8, N=6
    TIMx_CCMR2_IC4F_FILTER_MODE_9  = 0b1001u, // f SAMPLING =f DTS /8, N=8
    TIMx_CCMR2_IC4F_FILTER_MODE_10 = 0b1010u, // f SAMPLING =f DTS /16, N=5
    TIMx_CCMR2_IC4F_FILTER_MODE_11 = 0b1011u, // f SAMPLING =f DTS /16, N=6
    TIMx_CCMR2_IC4F_FILTER_MODE_12 = 0b1100u, // f SAMPLING =f DTS /16, N=8
    TIMx_CCMR2_IC4F_FILTER_MODE_13 = 0b1101u, // f SAMPLING =f DTS /32, N=5
    TIMx_CCMR2_IC4F_FILTER_MODE_14 = 0b1110u, // f SAMPLING =f DTS /32, N=6
    TIMx_CCMR2_IC4F_FILTER_MODE_15 = 0b1111u, // f SAMPLING =f DTS /32, N=8
    TIMx_CCMR2_IC4F_SHIFT_AMT      = 12u,     // position of IC4F in TIMx CCMR2
} TIMx_CCMR2_IC4F_MASKS_enum;

/*
--| NAME: TIMx_CCMR2_IC4PSC_MASKS_enum
--| DESCRIPTION: TIMx CCMR2 Input capture 4 prescaler masks [2 bits, rw]
*/
typedef enum TIMx_CCMR2_IC4PSC_MASKS_Enumeration
{
    TIMx_CCMR2_IC4PSC_NO_PRESCALER           = 0b00u, // no prescaler
    TIMx_CCMR2_IC4PSC_CAPTURE_EVERY_2_EVENTS = 0b01u, // capture is done once every 2 events
    TIMx_CCMR2_IC4PSC_CAPTURE_EVERY_4_EVENTS = 0b10u, // capture is done once every 4 events
    TIMx_CCMR2_IC4PSC_CAPTURE_EVERY_8_EVENTS = 0b11u, // capture is done once every 8 events
    TIMx_CCMR2_IC4PSC_SHIFT_AMT              = 10u    // position of IC4PSC in TIMx CCMR2
} TIMx_CCMR2_IC4PSC_MASKS_enum;

/*
--| NAME: TIMx_CCMR2_IC3F_MASKS_enum
--| DESCRIPTION: TIMx CCMR2 Input capture 3 filter masks [4 bits, rw]
*/
typedef enum TIMx_CCMR2_IC3F_MASKS_Enumeration
{
    TIMx_CCMR2_IC3F_NO_FILTER      = 0b0000u, // Prescaler OFF
    TIMx_CCMR2_IC3F_FILTER_MODE_1  = 0b0001u, // f SAMPLING =f CK_INT , N=2
    TIMx_CCMR2_IC3F_FILTER_MODE_2  = 0b0010u, // f SAMPLING =f CK_INT , N=4
    TIMx_CCMR2_IC3F_FILTER_MODE_3  = 0b0011u, // f SAMPLING =f CK_INT , N=8^2
    TIMx_CCMR2_IC3F_FILTER_MODE_4  = 0b0100u, // f SAMPLING =f DTS /2, N=6
    TIMx_CCMR2_IC3F_FILTER_MODE_5  = 0b0101u, // f SAMPLING =f DTS /2, N=8
    TIMx_CCMR2_IC3F_FILTER_MODE_6  = 0b0110u, // f SAMPLING =f DTS /4, N=6^2
    TIMx_CCMR2_IC3F_FILTER_MODE_7  = 0b0111u, // f SAMPLING =f DTS /4, N=8
    TIMx_CCMR2_IC3F_FILTER_MODE_8  = 0b1000u, // f SAMPLING =f DTS /8, N=6
    TIMx_CCMR2_IC3F_FILTER_MODE_9  = 0b1001u, // f SAMPLING =f DTS /8, N=8
    TIMx_CCMR2_IC3F_FILTER_MODE_10 = 0b1010u, // f SAMPLING =f DTS /16, N=5
    TIMx_CCMR2_IC3F_FILTER_MODE_11 = 0b1011u, // f SAMPLING =f DTS /16, N=6
    TIMx_CCMR2_IC3F_FILTER_MODE_12 = 0b1100u, // f SAMPLING =f DTS /16, N=8
    TIMx_CCMR2_IC3F_FILTER_MODE_13 = 0b1101u, // f SAMPLING =f DTS /32, N=5
    TIMx_CCMR2_IC3F_FILTER_MODE_14 = 0b1110u, // f SAMPLING =f DTS /32, N=6
    TIMx_CCMR2_IC3F_FILTER_MODE_15 = 0b1111u, // f SAMPLING =f DTS /32, N=8
    TIMx_CCMR2_IC3F_SHIFT_AMT      = 4u,      // position of IC3F in TIMx CCMR2
} TIMx_CCMR2_IC3F_MASKS_enum;

/*
--| NAME: TIMx_CCMR2_IC3PSC_MASKS_enum
--| DESCRIPTION: TIMx CCMR2 Input capture 3 prescaler masks [2 bits, rw]
*/
typedef enum TIMx_CCMR2_IC3PSC_MASKS_Enumeration
{
    TIMx_CCMR2_IC3PSC_NO_PRESCALER           = 0b00u, // no prescaler
    TIMx_CCMR2_IC3PSC_CAPTURE_EVERY_2_EVENTS = 0b01u, // capture is done once every 2 events
    TIMx_CCMR2_IC3PSC_CAPTURE_EVERY_4_EVENTS = 0b10u, // capture is done once every 4 events
    TIMx_CCMR2_IC3PSC_CAPTURE_EVERY_8_EVENTS = 0b11u, // capture is done once every 8 events
    TIMx_CCMR2_IC3PSC_SHIFT_AMT              = 2u     // position of IC3PSC in TIMx CCMR2
} TIMx_CCMR2_IC3PSC_MASKS_enum;

/*
--| NAME: TIMx_CCER_FLAGS_enum
--| DESCRIPTION: TIMx capture/compare enable register flags
*/
typedef enum TIMx_CCER_FLAGS_Enumeration
{
    TIMx_CCER_CC4P_FLAG = (1u << 13u), // Capture/Compare 4 output polarity [rw]
    TIMx_CCER_CC4E_FLAG = (1u << 12u), // Capture/Compare 4 output enable [rw]
    TIMx_CCER_CC3P_FLAG = (1u << 9u),  // Capture/Compare 3 output polarity [rw]
    TIMx_CCER_CC3E_FLAG = (1u << 8u),  // Capture/Compare 3 output enable [rw]
    TIMx_CCER_CC2P_FLAG = (1u << 5u),  // Capture/Compare 2 output polarity [rw]
    TIMx_CCER_CC2E_FLAG = (1u << 4u),  // Capture/Compare 2 output enable [rw]
    TIMx_CCER_CC1P_FLAG = (1u << 1u),  // Capture/Compare 1 output polarity [rw]
    TIMx_CCER_CC1E_FLAG = (1u << 0u),  // Capture/Compare 1 output enable [rw]
} TIMx_CCER_FLAGS_enum;

/*
--| NAME: TIMx_DCR_DBL_MASKS_enum
--| DESCRIPTION: TIMx DMA control register DMA burst length masks [5 bits, rw]
*/
typedef enum TIMx_DCR_DBL_MASKS_MASKS_Enumeration
{
    TIMx_DCR_DBL_MASK      = FIVE_BIT_MASK, // 5-bit vector defines the number of DMA transfers
    TIMx_DCR_DBL_SHIFT_AMT = 8u             // position of DBL in TIMx DCR
} TIMx_DCR_DBL_MASKS_enum;

/*
--| NAME: TIMx_DCR_DBA_MASKS_enum
--| DESCRIPTION: TIMx DMA control register DMA base address masks [5 bits, rw]
*/
typedef enum TIMx_DCR_DBA_MASKS_MASKS_Enumeration
{
    TIMx_DCR_DBA_MASK      = FIVE_BIT_MASK, // 5-bit vector defines the base-address for DMA transfers
    TIMx_DCR_DBA_SHIFT_AMT = 0u             // position of DBA in TIMx DCR
} TIMx_DCR_DBA_MASKS_enum;

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
