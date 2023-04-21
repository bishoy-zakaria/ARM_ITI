#ifndef GPIO_H
#define GPIO_H
#include"Std_Types.h"
/*************************************************************************/
#define GPIOA_BaseAddress    0x40020000
#define GPIOB_BaseAddress    0x40020400
#define GPIOC_BaseAddress    0x40020800
#define GPIOD_BaseAddress    0x40020C00
#define GPIOE_BaseAddress    0x40021000
#define GPIOH_BaseAddress    0x40021C00

#define GPIO_PORT_A   ((void*) GPIOA_BaseAddress)
#define GPIO_PORT_B   ((void*) GPIOB_BaseAddress)
#define GPIO_PORT_C   ((void*) GPIOC_BaseAddress)
#define GPIO_PORT_D   ((void*) GPIOD_BaseAddress)
#define GPIO_PORT_E   ((void*) GPIOE_BaseAddress)
#define GPIO_PORT_H   ((void*) GPIOH_BaseAddress)
/*************************************************************************/

#define GPIO_PIN_0      		0
#define GPIO_PIN_1      		1
#define GPIO_PIN_2      		2
#define GPIO_PIN_3      		3
#define GPIO_PIN_4      		4
#define GPIO_PIN_5      		5
#define GPIO_PIN_6      		6
#define GPIO_PIN_7      		7
#define GPIO_PIN_8      		8
#define GPIO_PIN_9     	 		9
#define GPIO_PIN_10     		10
#define GPIO_PIN_11     		11
#define GPIO_PIN_12     		12
#define GPIO_PIN_13     		13
#define GPIO_PIN_14     		14
#define GPIO_PIN_15     		15

#define GPIO_VALUE_LOW   		0
#define GPIO_VALUE_HIGH  		1

#define GPIO_SPEED_LOW   	 	0
#define GPIO_SPEED_MEDIUM 	 	1
#define GPIO_SPEED_HIGH   	 	2
#define GPIO_SPEED_VeryHigh  	3


#define GPIO_MODE_OUTPUT_PP_FLOAT		0
#define GPIO_MODE_OUTPUT_PP_PU			1
#define GPIO_MODE_OUTPUT_PP_PD			2
#define GPIO_MODE_OUTPUT_OD_FLOAT		3
#define GPIO_MODE_OUTPUT_OD_PU			4
#define GPIO_MODE_OUTPUT_OD_PD			5

#define GPIO_MODE_AF_PP_FLOAT			6
#define GPIO_MODE_AF_PP_PU				7
#define GPIO_MODE_AF_PP_PD				8
#define GPIO_MODE_AF_OD_FLOAT			9
#define GPIO_MODE_AF_OD_PU				10
#define GPIO_MODE_AF_OD_PD				11

#define GPIO_MODE_INPUT_FLOAT			12
#define GPIO_MODE_INPUT_PU				13
#define GPIO_MODE_INPUT_PD				14

#define GPIO_MODE_ANALOG				15

#define GPIO_AF0						0
#define GPIO_AF1						1
#define GPIO_AF2						2
#define GPIO_AF3						3
#define GPIO_AF4						4
#define GPIO_AF5						5
#define GPIO_AF6						6
#define GPIO_AF7						7
#define GPIO_AF8						8
#define GPIO_AF9						9
#define GPIO_AF10						10
#define GPIO_AF11						11
#define GPIO_AF12						12
#define GPIO_AF13						13
#define GPIO_AF14						14
#define GPIO_AF15						15



typedef struct
{
	void* Port;
	u32 Pin;
	u32 Speed;
	u32 Mode;
}GPIO_cfg_t;

void GPIO_InitPin(GPIO_cfg_t* pin);
void GPIO_WritePinValue(void* GPIO_Port ,u32 GPIO_Pin ,u8 GPIO_Value);
void GPIO_ReadPinValue(void* GPIO_Port ,u32 GPIO_Pin ,u8* GPIO_Buffer);
void GPIO_Select_AF(void* GPIO_Port ,u32 GPIO_Pin ,u32 GPIO_AF);
void GPIO_WritePortValue(void* GPIO_Port , u32 GPIO_Value);
#endif
