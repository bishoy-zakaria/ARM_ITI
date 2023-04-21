#include "PushButton_cfg.h"
#include "PushButton.h"

PushButton_strCFG_t PushButton_CfgArray[PushButton_Count] =
{
		[START_PushButton] =
		{
				.port		= GPIO_PORT_D,
				.pin  		= GPIO_PIN_13,
				.PinMode	= GPIO_MODE_INPUT_PD,
				.speed		= GPIO_SPEED_HIGH,
				.ButtonMode	= PushButton_PD,
				.name 		= "Start push button",
		},

		[STOP_PushButton] =
		{
				.port		= GPIO_PORT_C,
				.pin  		= GPIO_PIN_13,
				.PinMode	= GPIO_MODE_INPUT_PU,
				.speed		= GPIO_SPEED_HIGH,
				.ButtonMode	= PushButton_PU,
				.name 		= "Stop push button",
		}
};
