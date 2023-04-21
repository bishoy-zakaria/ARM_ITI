#include "LED_cfg.h"
#include "LED.h"

LED_strCFG_t LED_CfgArray[LED_Count] =
{
		[APP1_LED] =
		{
				.port		= GPIO_PORT_B,
				.pin  		= GPIO_PIN_0,
				.PinMode	= GPIO_MODE_OUTPUT_PP_PD,
				.speed		= GPIO_SPEED_HIGH,
				.LedMode	= LED_ActiveHigh,
				.name 		= "APP1 LED",
				.color		= "Red"
		},

		[APP2_LED] =
		{
				.port		= GPIO_PORT_B,
				.pin  		= GPIO_PIN_1,
				.PinMode	= GPIO_MODE_OUTPUT_PP_PD,
				.speed		= GPIO_SPEED_HIGH,
				.LedMode	= LED_ActiveHigh,
				.name 		= "APP2 LED",
				.color		= "Green"
		},

		[APP3_LED] =
		{
				.port		= GPIO_PORT_B,
				.pin  		= GPIO_PIN_2,
				.PinMode	= GPIO_MODE_OUTPUT_PP_PD,
				.speed		= GPIO_SPEED_HIGH,
				.LedMode	= LED_ActiveHigh,
				.name 		= "APP3 LED",
				.color		= "Green"
		}
};
