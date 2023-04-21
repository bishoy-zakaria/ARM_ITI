#include "LED.h"

extern LED_strCFG_t LED_CfgArray[LED_Count];

void LED_init(void)
{
	GPIO_cfg_t local_GPIO_Pin;
	u8 iterrator=0;

	for(iterrator=0 ; iterrator<LED_Count ; iterrator++)
	{
		local_GPIO_Pin.Port 	=	LED_CfgArray[iterrator].port;
		local_GPIO_Pin.Pin		=	LED_CfgArray[iterrator].pin;
		local_GPIO_Pin.Mode		=	LED_CfgArray[iterrator].PinMode;
		local_GPIO_Pin.Speed	=	LED_CfgArray[iterrator].speed;
		GPIO_InitPin(&local_GPIO_Pin);
	}
}


LED_Error_t LED_WriteValue(LED_enuCfg_t LED_enuNum , LED_enuValue_t LED_enuValue)
{
	LED_Error_t status = LED_enuOK;
	if(LED_enuNum < LED_Count)
	{
		switch(LED_CfgArray[LED_enuNum].LedMode)
		{
			case LED_ActiveHigh:
				GPIO_WritePinValue(LED_CfgArray[LED_enuNum].port , LED_CfgArray[LED_enuNum].pin ,LED_enuValue);
				break;
			case LED_ActiveLow:
				switch(LED_enuValue)
				{
				case LED_enuLow:
					GPIO_WritePinValue(LED_CfgArray[LED_enuNum].port , LED_CfgArray[LED_enuNum].pin ,GPIO_VALUE_HIGH);
					break;
				case LED_enuHigh:
					GPIO_WritePinValue(LED_CfgArray[LED_enuNum].port , LED_CfgArray[LED_enuNum].pin ,GPIO_VALUE_LOW);
					break;
				}
				break;
			default:
				status = LED_enuNotOK;
		}
	}
	else
	{
		status = LED_enuNotOK;
	}
	return status;
}
