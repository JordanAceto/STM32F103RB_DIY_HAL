/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   PSP_FLASH.h provides types and interfaces for the Flash memory.
--|   
--|----------------------------------------------------------------------------|
--| REFERENCES:
--|   stm32f10x reference manual, page 54
--|
--|----------------------------------------------------------------------------|
*/

#ifndef PSP_FLASH_H_INCLUDED
#define PSP_FLASH_H_INCLUDED

/*
--|----------------------------------------------------------------------------|
--| INCLUDE FILES
--|----------------------------------------------------------------------------|
*/

#include "Common_Typedefs.h"

/*
--|----------------------------------------------------------------------------|
--| PUBLIC DEFINES
--|----------------------------------------------------------------------------|
*/

/*
--| NAME: FLASH 
--| DESCRIPTION: pointer to the FLASH 
--| TYPE: FLASH*
*/
#define FLASH ((volatile FLASH_t *)PSP_PERIPHERAL_FLASH_INT_BASE)

/*
--|----------------------------------------------------------------------------|
--| PUBLIC TYPES
--|----------------------------------------------------------------------------|
*/

/*
--| NAME: FLASH
--| DESCRIPTION: Flash memory structure
*/
typedef struct FLASH_Type
{
    vuint32_t ACR;  // Flash access control register
} FLASH_t;

/*
--| NAME: FLASH_ACR_FLAGS_enum
--| DESCRIPTION: Flash access control register flags
*/
typedef enum FLASH_ACR_FLAGS_Enumeration
{
    FLASH_ACR_PRFTBS_FLAG = (1u << 5u), // Prefetch buffer status [r]
    FLASH_ACR_PRFTBE_FLAG = (1u << 4u), // Prefetch buffer enable [rw]
    FLASH_ACR_HLFCYA_FLAG = (1u << 3u), // Flash half cycle access enable [rw]
} FLASH_ACR_FLAGS_enum;

/*
--| NAME: FLASH_ACR_Latency_enum
--| DESCRIPTION: Flash ACR latency configuration [3 bits, rw]
*/
typedef enum FLASH_ACR_Latency_Enumeration
{
    FLASH_ACR_LATENCY_ZERO_WAIT_STATES = 0b000u, // Zero wait state, if 0 < SYSCLK≤ 24 MHz
    FLASH_ACR_LATENCY_ONE_WAIT_STATE   = 0b001u, // One wait state, if 24 MHz < SYSCLK ≤ 48 MHz
    FLASH_ACR_LATENCY_TWO_WAIT_STATES  = 0b010u, // Two wait states, if 48 MHz < SYSCLK ≤ 72 MHz
    FLASH_ACR_LATENCY_SHIFT_AMT        = 0u,     // position of LATENCY in FLASH ACR
} FLASH_ACR_Latency_enum;

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
