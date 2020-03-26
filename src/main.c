
#include <stdint.h>

#include "PSP_GPIO.h"
#include "PSP_SysTick.h"
#include "PSP_Hardware_Init.h"

int main(void)
{
    Hardware_Init();

    SysTick_Periodic_Timer_t periodic_timer;

    periodic_timer.timeout_period_mSec = 1000u;

    SysTick_Initialize_Periodic_Timer(&periodic_timer);

    GPIO_Pin_t LED_pin;
    LED_pin.number = 5u;
    LED_pin.port = GPIO_Port_A;

    PSP_GPIO_Write_Pin(&LED_pin, GPIO_PIN_OUTPUT_WRITE_HIGH);

    while (1)
    {
        if (SysTick_Periodic_Timer_Timeout_Occured(&periodic_timer))
		{
			PSP_GPIO_Toggle_Pin(&LED_pin);
		}
    }
}

