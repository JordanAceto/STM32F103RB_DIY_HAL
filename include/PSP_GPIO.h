/*
--|----------------------------------------------------------------------------|
--| FILE DESCRIPTION:
--|   PSP_GPIO.h provides types and interfaces for using the GPIO pins.
--|   
--|----------------------------------------------------------------------------|
--| REFERENCES:
--|   stm32f10x reference manual, page 159
--|
--|----------------------------------------------------------------------------|
*/

#ifndef PSP_GPIO_H_INCLUDED
#define PSP_GPIO_H_INCLUDED

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
--| NAME: GPIO_Port_A 
--| DESCRIPTION: pointer to GPIO PORTA 
--| TYPE: GPIO_Port_t*
*/
#define GPIO_Port_A ((volatile GPIO_Port_t *)PSP_PERIPHERAL_PORTA_BASE)

/*
--| NAME: GPIO_Port_B
--| DESCRIPTION: pointer to GPIO PORTB 
--| TYPE: GPIO_Port_t*
*/
#define GPIO_Port_B ((volatile GPIO_Port_t *)PSP_PERIPHERAL_PORTB_BASE)

/*
--| NAME: GPIO_Port_C
--| DESCRIPTION: pointer to GPIO PORTC 
--| TYPE: GPIO_Port_t*
*/
#define GPIO_Port_C ((volatile GPIO_Port_t *)PSP_PERIPHERAL_PORTC_BASE)

/*
--| NAME: GPIO_Port_D
--| DESCRIPTION: pointer to GPIO PORTD 
--| TYPE: GPIO_Port_t*
*/
#define GPIO_Port_D ((volatile GPIO_Port_t *)PSP_PERIPHERAL_PORTD_BASE)

/*
--|----------------------------------------------------------------------------|
--| PUBLIC TYPES
--|----------------------------------------------------------------------------|
*/

/*
--| NAME: GPIO_Port_t
--| DESCRIPTION: GPIOx port structure
*/
typedef struct GPIO_Port_Type
{
    vuint32_t CRL;  // port configuration register low
    vuint32_t CRH;  // port configuration register high
    vuint32_t IDR;  // input data register
    vuint32_t ODR;  // output data register
    vuint32_t BSRR; // bit set/reset register
    vuint32_t BRR;  // bit reset register
    vuint32_t LCKR; // configuration lock register
} GPIO_Port_t;

/*
--| NAME: GPIO_Pin_CNFy_Configuration_enum
--| DESCRIPTION: pin configuration for a given GPIO CRL/H CNFy field
*/
typedef enum GPIO_Pin_CNFy_Output_Configuration_Enumeration
{
    GPIO_PIN_CNFy_ANALOG_MODE                         = 0b00u,
    GPIO_PIN_CNFy_FLOATING_INPUT                      = 0b01u,
    GPIO_PIN_CNFy_INPUT_WITH_PULL_UP_DOWN             = 0b10u,
    GPIO_PIN_CNFy_INPUT_RESERVED                      = 0b11u,

    GPIO_PIN_CNFy_GENERAL_PURPOSE_OUTPUT_PUSH_PULL    = 0b00u,
    GPIO_PIN_CNFy_GENERAL_PURPOSE_OUTPUT_OPEN_DRAIN   = 0b01u,
    GPIO_PIN_CNFy_ALTERNATE_FUNCTION_OUTPUT_PUSH_PULL = 0b10u,
    GPIO_PIN_CNFy_ALTERNATE_FUNCTION_OPEN_DRAIN       = 0b11u
} GPIO_Pin_CNFy_Configuration_enum;

/*
--| NAME: GPIO_Pin_MODEy_Configuration_enum
--| DESCRIPTION: pin configuration for a given GPIO CRL/H MODEy field
*/
typedef enum GPIO_Pin_MODEy_Configuration_Enumeration
{
    GPIO_PIN_MODEy_INPUT_MODE       = 0b00u,
    GPIO_PIN_MODEy_OUTPUT_10MHz_MAX = 0b01u,
    GPIO_PIN_MODEy_OUTPUT_2MHz_MAX  = 0b10u,
    GPIO_PIN_MODEy_OUTPUT_50MHz_MAX = 0b11u,
} GPIO_Pin_MODEy_Configuration_enum;

/*
--| NAME: GPIO_Pin_Input_Pull_Up_Down_enum
--| DESCRIPTION: pull up/down configuration for a given GPIO PxODR field in input mode
*/
typedef enum GPIO_Pin_Input_Pull_Up_Down_Enumeration
{
    GPIO_PIN_ENABLE_INPUT_PULLDOWN = 0u,
    GPIO_PIN_ENABLE_INPUT_PULLUP   = 1u,
    GPIO_PIN_NO_PULL_UP_OR_DOWN    = 2u
} GPIO_Pin_Input_Pull_Up_Down_enum;

/*
--| NAME: GPIO_Pin_Initialization_Data_t
--| DESCRIPTION: initialization struct for a GPIO pin
*/
typedef struct GPIO_Pin_Initialization_Data_Type
{
    GPIO_Pin_CNFy_Configuration_enum  CNFy;
    GPIO_Pin_MODEy_Configuration_enum MODEy;
    GPIO_Pin_Input_Pull_Up_Down_enum  pull_up_down;
} GPIO_Pin_Initialization_Data_t;

/*
--| NAME: GPIO_Pin_t
--| DESCRIPTION: storage for a GPIO pin
*/
typedef struct GPIO_Pin_Type
{
    volatile GPIO_Port_t * port;
    uint32_t number;
} GPIO_Pin_t;

/*
--| NAME: GPIO_Pin_Output_Write_enum
--| DESCRIPTION: set/clear signal for a given GPIO pin
*/
typedef enum GPIO_Pin_Output_Write_Enumeration
{
    GPIO_PIN_OUTPUT_WRITE_LOW  = 0u,
    GPIO_PIN_OUTPUT_WRITE_HIGH = 1u
} GPIO_Pin_Output_Write_enum;

/*
--| NAME: GPIO_Pin_Input_Read_enum
--| DESCRIPTION: value of a given GPIO pin reading
*/
typedef enum GPIO_Pin_Input_Read_Enumeration
{
    GPIO_PIN_INPUT_READ_LOW  = 0u,
    GPIO_PIN_INPUT_READ_HIGH = 1u
} GPIO_Pin_Input_Read_enum;

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
    PSP_GPIO_Set_Pin_Mode

Function Description:
    Initialize a given GPIO pin to the given pin mode. 

Parameters:
    p_GPIO_pin:  pointer to the GPIO pin to initialize.
    p_init_data: pointer to the initialization data. The init data contains
        the pin mode, and optional pull up/down control.

Returns:
    None

Assumptions/Limitations:
    Assumes that the pin number and pin mode are valid. If either is invalid,
    the result is undefined.
------------------------------------------------------------------------------*/
void PSP_GPIO_Set_Pin_Mode(GPIO_Pin_t * p_GPIO_pin, 
                           GPIO_Pin_Initialization_Data_t * p_init_data);

/*------------------------------------------------------------------------------
Function Name:
    PSP_GPIO_Write_Pin

Function Description:
    Write a given GPIO pin high or low. 

Parameters:
    p_GPIO_pin: pointer to the GPIO pin to write.
    pin_direction: the direction to write.

Returns:
    None

Assumptions/Limitations:
    Assumes that the pin number and pin mode are valid. If either is invalid,
    the result is undefined.

    Assumes that the pin in question is set to output mode.
------------------------------------------------------------------------------*/
void PSP_GPIO_Write_Pin(GPIO_Pin_t * p_GPIO_pin, 
                        GPIO_Pin_Output_Write_enum pin_direction);

/*------------------------------------------------------------------------------
Function Name:
    PSP_GPIO_Toggle_Pin

Function Description:
    Toggle a given GPIO pin. If it is low, make it high, if it is high,
        make it low. 

Parameters:
    p_GPIO_pin: pointer to the GPIO pin to toggle.

Returns:
    None

Assumptions/Limitations:
    Assumes that the pin number is valid. If it is invalid, the result 
    is undefined.

    Assumes that the pin in question is set to output mode.
------------------------------------------------------------------------------*/
void PSP_GPIO_Toggle_Pin(GPIO_Pin_t * p_GPIO_pin);

/*------------------------------------------------------------------------------
Function Name:
    PSP_GPIO_Read_Pin

Function Description:
    Read a given GPIO pin and return its value. 

Parameters:
    p_GPIO_pin: pointer to the GPIO pin to read.

Returns:
    GPIO_Pin_Input_Read_enum: GPIO_PIN_INPUT_READ_LOW if the pins value is 
        low, else GPIO_PIN_INPUT_READ_HIGH.

Assumptions/Limitations:
    Assumes that the pin number and pin mode are valid. If either is invalid,
    the result is undefined.
------------------------------------------------------------------------------*/
GPIO_Pin_Input_Read_enum PSP_GPIO_Read_Pin(GPIO_Pin_t * p_GPIO_pin);

#endif
