#include "LCD.h"
#include "LCD_cfg.h"

GPIO_cfg_t LCD_CFG_Array[LCD_Pin_Num] =
{
		[LCD_RSPin] =
		{
				.Port	=	GPIO_PORT_B,
				.Pin 	=	GPIO_PIN_0,
				.Speed	=	GPIO_SPEED_HIGH,
				.Mode	=	GPIO_MODE_OUTPUT_PP_PD
		},

		[LCD_RWPin] =
		{
				.Port	=	GPIO_PORT_B,
				.Pin 	=	GPIO_PIN_1,
				.Speed	=	GPIO_SPEED_HIGH,
				.Mode	=	GPIO_MODE_OUTPUT_PP_PD
		},

		[LCD_EPin] =
		{
				.Port	=	GPIO_PORT_B,
				.Pin 	=	GPIO_PIN_2,
				.Speed	=	GPIO_SPEED_HIGH,
				.Mode	=	GPIO_MODE_OUTPUT_PP_PD
		},

		[LCD_DB0Pin] =
		{
				.Port	=	GPIO_PORT_A,
				.Pin 	=	GPIO_PIN_0,
				.Speed	=	GPIO_SPEED_HIGH,
				.Mode	=	GPIO_MODE_OUTPUT_PP_PD
		},

		[LCD_DB1Pin] =
		{
				.Port	=	GPIO_PORT_A,
				.Pin 	=	GPIO_PIN_1,
				.Speed	=	GPIO_SPEED_HIGH,
				.Mode	=	GPIO_MODE_OUTPUT_PP_PD
		},

		[LCD_DB2Pin] =
		{
				.Port	=	GPIO_PORT_A,
				.Pin 	=	GPIO_PIN_2,
				.Speed	=	GPIO_SPEED_HIGH,
				.Mode	=	GPIO_MODE_OUTPUT_PP_PD
		},

		[LCD_DB3Pin] =
		{
				.Port	=	GPIO_PORT_A,
				.Pin 	=	GPIO_PIN_3,
				.Speed	=	GPIO_SPEED_HIGH,
				.Mode	=	GPIO_MODE_OUTPUT_PP_PD
		},

		[LCD_DB4Pin] =
		{
				.Port	=	GPIO_PORT_A,
				.Pin 	=	GPIO_PIN_4,
				.Speed	=	GPIO_SPEED_HIGH,
				.Mode	=	GPIO_MODE_OUTPUT_PP_PD
		},

		[LCD_DB5Pin] =
		{
				.Port	=	GPIO_PORT_A,
				.Pin 	=	GPIO_PIN_5,
				.Speed	=	GPIO_SPEED_HIGH,
				.Mode	=	GPIO_MODE_OUTPUT_PP_PD
		},

		[LCD_DB6Pin] =
		{
				.Port	=	GPIO_PORT_A,
				.Pin 	=	GPIO_PIN_6,
				.Speed	=	GPIO_SPEED_HIGH,
				.Mode	=	GPIO_MODE_OUTPUT_PP_PD
		},

		[LCD_DB7Pin] =
		{
				.Port	=	GPIO_PORT_A,
				.Pin 	=	GPIO_PIN_7,
				.Speed	=	GPIO_SPEED_HIGH,
				.Mode	=	GPIO_MODE_OUTPUT_PP_PD
		}
};
