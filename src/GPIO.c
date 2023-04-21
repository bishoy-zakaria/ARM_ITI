#include"GPIO.h"


typedef struct
{
	volatile u32 GPIO_MODER;
	volatile u32 GPIO_OTYPER;
	volatile u32 GPIO_OSPEEDR;
	volatile u32 GPIO_PUPDR;
	volatile u32 GPIO_IDR;
	volatile u32 GPIO_ODR;
	volatile u32 GPIO_BSRR;
	volatile u32 GPIO_LCKR;
	volatile u32 GPIO_AFRL;
	volatile u32 GPIO_AFRH;
}GPIO_t;


#define GPIO_OUTPUT_MASK  		0x01
#define GPIO_AF_MASK	  		0x02
#define GPIO_INPUT_MASK			0x00
#define GPIO_MODE_CLEAR_MASK 	0x03

#define GPIO_OD_MASK			0x01

#define GPIO_FLOAT_MASK        	0x00
#define GPIO_PU_MASK        	0x01
#define GPIO_PD_MASK        	0x02
#define GPIO_PULL_CLEAR_MASK    0x03

#define GPIO_LOW_S_MASK			0x00
#define GPIO_MEDIUM_S_MASK		0x01
#define GPIO_HIGH_S_MASK		0x02
#define GPIO_S_CLEAR_MASK		0x03

#define GPIO_SET_PIN_MASK      	0x01

void GPIO_InitPin(GPIO_cfg_t* pin)
{
	u32 mode_buffer 	= ((volatile GPIO_t* const)pin->Port)->GPIO_MODER ;
	u32 outype_buffer 	= ((volatile GPIO_t* const)pin->Port)->GPIO_OTYPER;
	u32 pud_buffer 		= ((volatile GPIO_t* const)pin->Port)->GPIO_PUPDR;
	u32 speed_buffer 	= ((volatile GPIO_t* const)pin->Port)->GPIO_OSPEEDR;

	switch(pin->Mode)
	{
		case GPIO_MODE_OUTPUT_PP_FLOAT:
			mode_buffer &= ~(GPIO_MODE_CLEAR_MASK << (pin->Pin + pin->Pin ));
			mode_buffer |=   GPIO_OUTPUT_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_MODER  = mode_buffer;

			outype_buffer &= ~(GPIO_OD_MASK << pin->Pin);
			((volatile GPIO_t* const)pin->Port)->GPIO_OTYPER = outype_buffer;

			pud_buffer &= ~(GPIO_PULL_CLEAR_MASK << (pin->Pin + pin->Pin ));
			pud_buffer |=   GPIO_FLOAT_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_PUPDR  = pud_buffer;

			break;
		case GPIO_MODE_OUTPUT_PP_PU:
			mode_buffer &= ~(GPIO_MODE_CLEAR_MASK << (pin->Pin + pin->Pin ));
			mode_buffer |=   GPIO_OUTPUT_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_MODER  = mode_buffer;

			outype_buffer &= ~(GPIO_OD_MASK << pin->Pin);
			((volatile GPIO_t* const)pin->Port)->GPIO_OTYPER = outype_buffer;

			pud_buffer &= ~(GPIO_PULL_CLEAR_MASK << (pin->Pin + pin->Pin ));
			pud_buffer |=   GPIO_PU_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_PUPDR  = pud_buffer;

			break;
		case GPIO_MODE_OUTPUT_PP_PD:
			mode_buffer &= ~(GPIO_MODE_CLEAR_MASK << (pin->Pin + pin->Pin ));
			mode_buffer |=   GPIO_OUTPUT_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_MODER  = mode_buffer;

			outype_buffer &= ~(GPIO_OD_MASK << pin->Pin);
			((volatile GPIO_t* const)pin->Port)->GPIO_OTYPER = outype_buffer;

			pud_buffer &= ~(GPIO_PULL_CLEAR_MASK << (pin->Pin + pin->Pin ));
			pud_buffer |=   GPIO_PD_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_PUPDR  = pud_buffer;

			break;
		case GPIO_MODE_OUTPUT_OD_FLOAT:
			mode_buffer &= ~(GPIO_MODE_CLEAR_MASK << (pin->Pin + pin->Pin ));
			mode_buffer |=   GPIO_OUTPUT_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_MODER  = mode_buffer;

			outype_buffer |= GPIO_OD_MASK << pin->Pin;
			((volatile GPIO_t* const)pin->Port)->GPIO_OTYPER = outype_buffer;

			pud_buffer &= ~(GPIO_PULL_CLEAR_MASK << (pin->Pin + pin->Pin ));
			pud_buffer |=   GPIO_FLOAT_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_PUPDR  = pud_buffer;

			break;
		case GPIO_MODE_OUTPUT_OD_PU:
			mode_buffer &= ~(GPIO_MODE_CLEAR_MASK << (pin->Pin + pin->Pin ));
			mode_buffer |=   GPIO_OUTPUT_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_MODER  = mode_buffer;

			outype_buffer |= GPIO_OD_MASK << pin->Pin;
			((volatile GPIO_t* const)pin->Port)->GPIO_OTYPER = outype_buffer;

			pud_buffer &= ~(GPIO_PULL_CLEAR_MASK << (pin->Pin + pin->Pin ));
			pud_buffer |=   GPIO_PU_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_PUPDR  = pud_buffer;

			break;
		case GPIO_MODE_OUTPUT_OD_PD:
			mode_buffer &= ~(GPIO_MODE_CLEAR_MASK << (pin->Pin + pin->Pin ));
			mode_buffer |=   GPIO_OUTPUT_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_MODER  = mode_buffer;

			outype_buffer |= GPIO_OD_MASK << pin->Pin;
			((volatile GPIO_t* const)pin->Port)->GPIO_OTYPER = outype_buffer;

			pud_buffer &= ~(GPIO_PULL_CLEAR_MASK << (pin->Pin + pin->Pin ));
			pud_buffer |=   GPIO_PD_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_PUPDR  = pud_buffer;

			break;
		case GPIO_MODE_AF_PP_FLOAT:
			mode_buffer &= ~(GPIO_MODE_CLEAR_MASK << (pin->Pin + pin->Pin ));
			mode_buffer |=   GPIO_AF_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_MODER  = mode_buffer;

			outype_buffer &= ~(GPIO_OD_MASK << pin->Pin);
			((volatile GPIO_t* const)pin->Port)->GPIO_OTYPER = outype_buffer;

			pud_buffer &= ~(GPIO_PULL_CLEAR_MASK << (pin->Pin + pin->Pin ));
			pud_buffer |=   GPIO_FLOAT_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_PUPDR  = pud_buffer;

			break;
		case GPIO_MODE_AF_PP_PU:
			mode_buffer &= ~(GPIO_MODE_CLEAR_MASK << (pin->Pin + pin->Pin ));
			mode_buffer |=   GPIO_AF_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_MODER  = mode_buffer;

			outype_buffer &= ~(GPIO_OD_MASK << pin->Pin);
			((volatile GPIO_t* const)pin->Port)->GPIO_OTYPER = outype_buffer;

			pud_buffer &= ~(GPIO_PULL_CLEAR_MASK << (pin->Pin + pin->Pin ));
			pud_buffer |=   GPIO_PU_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_PUPDR  = pud_buffer;

			break;
		case GPIO_MODE_AF_PP_PD:
			mode_buffer &= ~(GPIO_MODE_CLEAR_MASK << (pin->Pin + pin->Pin ));
			mode_buffer |=   GPIO_AF_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_MODER  = mode_buffer;

			outype_buffer &= ~(GPIO_OD_MASK << pin->Pin);
			((volatile GPIO_t* const)pin->Port)->GPIO_OTYPER = outype_buffer;

			pud_buffer &= ~(GPIO_PULL_CLEAR_MASK << (pin->Pin + pin->Pin ));
			pud_buffer |=   GPIO_PD_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_PUPDR  = pud_buffer;

			break;
		case GPIO_MODE_AF_OD_FLOAT:
			mode_buffer &= ~(GPIO_MODE_CLEAR_MASK << (pin->Pin + pin->Pin ));
			mode_buffer |=   GPIO_AF_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_MODER  = mode_buffer;

			outype_buffer |= GPIO_OD_MASK << pin->Pin;
			((volatile GPIO_t* const)pin->Port)->GPIO_OTYPER = outype_buffer;

			pud_buffer &= ~(GPIO_PULL_CLEAR_MASK << (pin->Pin + pin->Pin ));
			pud_buffer |=   GPIO_FLOAT_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_PUPDR  = pud_buffer;

			break;
		case GPIO_MODE_AF_OD_PU:
			mode_buffer &= ~(GPIO_MODE_CLEAR_MASK << (pin->Pin + pin->Pin ));
			mode_buffer |=   GPIO_AF_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_MODER  = mode_buffer;

			outype_buffer |= GPIO_OD_MASK << pin->Pin;
			((volatile GPIO_t* const)pin->Port)->GPIO_OTYPER = outype_buffer;

			pud_buffer &= ~(GPIO_PULL_CLEAR_MASK << (pin->Pin + pin->Pin ));
			pud_buffer |=   GPIO_PU_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_PUPDR  = pud_buffer;

			break;
		case GPIO_MODE_AF_OD_PD:
			mode_buffer &= ~(GPIO_MODE_CLEAR_MASK << (pin->Pin + pin->Pin ));
			mode_buffer |=   GPIO_AF_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_MODER  = mode_buffer;

			outype_buffer |= GPIO_OD_MASK << pin->Pin;
			((volatile GPIO_t* const)pin->Port)->GPIO_OTYPER = outype_buffer;

			pud_buffer &= ~(GPIO_PULL_CLEAR_MASK << (pin->Pin + pin->Pin ));
			pud_buffer |=   GPIO_PD_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_PUPDR  = pud_buffer;

			break;
		case GPIO_MODE_INPUT_FLOAT:
			mode_buffer &= ~(GPIO_MODE_CLEAR_MASK << (pin->Pin + pin->Pin ));
			mode_buffer |=   GPIO_INPUT_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_MODER  = mode_buffer;

			break;
		case GPIO_MODE_INPUT_PU:
			mode_buffer &= ~(GPIO_MODE_CLEAR_MASK << (pin->Pin + pin->Pin ));
			mode_buffer |=   GPIO_INPUT_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_MODER  = mode_buffer;

			pud_buffer &= ~(GPIO_PULL_CLEAR_MASK << (pin->Pin + pin->Pin ));
			pud_buffer |=   GPIO_PU_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_PUPDR  = pud_buffer;

			break;
		case GPIO_MODE_INPUT_PD:
			mode_buffer &= ~(GPIO_MODE_CLEAR_MASK << (pin->Pin + pin->Pin ));
			mode_buffer |=   GPIO_INPUT_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_MODER  = mode_buffer;

			pud_buffer &= ~(GPIO_PULL_CLEAR_MASK << (pin->Pin + pin->Pin ));
			pud_buffer |=   GPIO_PD_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_PUPDR  = pud_buffer;

			break;
		case GPIO_MODE_ANALOG:
			mode_buffer |=   GPIO_MODE_CLEAR_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_MODER  = mode_buffer;

			break;
	}

	switch(pin->Speed)
	{
		case GPIO_SPEED_LOW:
			speed_buffer &= ~(GPIO_S_CLEAR_MASK << (pin->Pin + pin->Pin ));
			speed_buffer |=   GPIO_LOW_S_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_OSPEEDR  = speed_buffer;
			break;
		case GPIO_SPEED_MEDIUM:
			speed_buffer &= ~(GPIO_S_CLEAR_MASK << (pin->Pin + pin->Pin ));
			speed_buffer |=   GPIO_MEDIUM_S_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_OSPEEDR  = speed_buffer;
			break;
		case GPIO_SPEED_HIGH:
			speed_buffer &= ~(GPIO_S_CLEAR_MASK << (pin->Pin + pin->Pin ));
			speed_buffer |=   GPIO_HIGH_S_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_OSPEEDR  = speed_buffer;
			break;
		case GPIO_SPEED_VeryHigh:
			speed_buffer |=   GPIO_S_CLEAR_MASK << (pin->Pin + pin->Pin );
			((volatile GPIO_t* const)pin->Port)->GPIO_OSPEEDR  = speed_buffer;
			break;
	}

}


void GPIO_WritePinValue(void* GPIO_Port ,u32 GPIO_Pin ,u8 GPIO_Value)
{
	switch(GPIO_Value)
	{
		case GPIO_VALUE_HIGH:
			((volatile GPIO_t* const)GPIO_Port)->GPIO_BSRR |=  GPIO_SET_PIN_MASK<<GPIO_Pin;
			break;
		case GPIO_VALUE_LOW:
			((volatile GPIO_t* const)GPIO_Port)->GPIO_BSRR |=  GPIO_SET_PIN_MASK<<(GPIO_Pin+16);
			break;
	}
}

void GPIO_ReadPinValue(void* GPIO_Port ,u32 GPIO_Pin ,u8* GPIO_Buffer)
{
	*GPIO_Buffer = ((((volatile GPIO_t* const)GPIO_Port)->GPIO_IDR >> GPIO_Pin) & (0x01));

}

void GPIO_Select_AF(void* GPIO_Port ,u32 GPIO_Pin ,u32 GPIO_AF)
{
	u32 pin_num=0;
	pin_num = GPIO_Pin%8;
	if(GPIO_Pin <8)
	{
		((volatile GPIO_t* const)GPIO_Port)->GPIO_AFRL |=  (GPIO_AF <<(pin_num*4));
	}
	else
	{
		((volatile GPIO_t* const)GPIO_Port)->GPIO_AFRH |=  (GPIO_AF <<(pin_num*4));
	}

}
void GPIO_WritePortValue(void* GPIO_Port , u32 GPIO_Value)
{

}
