
#include "PushButton.h"

extern PushButton_strCFG_t PushButton_CfgArray[PushButton_Count];

void PushButton_init(void)
{
	GPIO_cfg_t local_GPIO_Pin;
	u8 iterrator=0;

	for(iterrator=0 ; iterrator<PushButton_Count ; iterrator++)
	{
		local_GPIO_Pin.Port 	=	PushButton_CfgArray[iterrator].port;
		local_GPIO_Pin.Pin		=	PushButton_CfgArray[iterrator].pin;
		local_GPIO_Pin.Mode		=	PushButton_CfgArray[iterrator].PinMode;
		local_GPIO_Pin.Speed	=	PushButton_CfgArray[iterrator].speed;
		GPIO_InitPin(&local_GPIO_Pin);
	}
}

PushButton_Error_t PushButton_WriteValue(PushButton_enuCfg_t LED_enuNum , u8* buffer_add)
{
	PushButton_Error_t status = PushButton_enuOK;
	u8 PinState;
	if(buffer_add == Null_Ptr)
	{
		status = PushButton_enuNullPtr;
	}

	if (LED_enuNum >= PushButton_Count)
	{
		status = PushButton_enuNotOK;
	}

	else
	{
		GPIO_ReadPinValue(PushButton_CfgArray[LED_enuNum].port ,PushButton_CfgArray[LED_enuNum].pin , &PinState);

		switch(PushButton_CfgArray[LED_enuNum].PinMode)
		{
			case PushButton_PD:
				switch(PinState)
				{
					case GPIO_VALUE_LOW:
						*buffer_add = PushButton_NotPressed;
						break;
					case GPIO_VALUE_HIGH:
						*buffer_add = PushButton_Pressed;
						break;
				}
				break;
			case PushButton_PU:
				switch(PinState)
				{
					case GPIO_VALUE_LOW:
						*buffer_add = PushButton_Pressed;
						break;
					case GPIO_VALUE_HIGH:
						*buffer_add = PushButton_NotPressed;
						break;
				}
				break;
			default:
				status = PushButton_enuNotOK;
		}
	}
	return status;
}
