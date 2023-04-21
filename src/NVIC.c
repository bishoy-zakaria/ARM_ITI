#include "NVIC.h"

/***************************************************************************/

typedef struct
{
	u16 AIRSCR_low;
	u16 VECTKEY;
}AIRSCR_t;

typedef struct
{
	volatile u32 NVIC_ISER0;
	volatile u32 NVIC_ISER1;
	volatile u32 NVIC_ISER2;
	volatile u32 NVIC_ISER3;
	volatile u32 NVIC_ISER4;
	volatile u32 NVIC_ISER5;
	volatile u32 NVIC_ISER6;
	volatile u32 NVIC_ISER7;

	const u32 Reserved_1[24];

	volatile u32 NVIC_ICER0;
	volatile u32 NVIC_ICER1;
	volatile u32 NVIC_ICER2;
	volatile u32 NVIC_ICER3;
	volatile u32 NVIC_ICER4;
	volatile u32 NVIC_ICER5;
	volatile u32 NVIC_ICER6;
	volatile u32 NVIC_ICER7;

	const u32 Reserved_2[24];

	volatile u32 NVIC_ISPR0;
	volatile u32 NVIC_ISPR1;
	volatile u32 NVIC_ISPR2;
	volatile u32 NVIC_ISPR3;
	volatile u32 NVIC_ISPR4;
	volatile u32 NVIC_ISPR5;
	volatile u32 NVIC_ISPR6;
	volatile u32 NVIC_ISPR7;

	const u32 Reserved_3[24];

	volatile u32 NVIC_ICPR0;
	volatile u32 NVIC_ICPR1;
	volatile u32 NVIC_ICPR2;
	volatile u32 NVIC_ICPR3;
	volatile u32 NVIC_ICPR4;
	volatile u32 NVIC_ICPR5;
	volatile u32 NVIC_ICPR6;
	volatile u32 NVIC_ICPR7;

	const u32 Reserved_4[24];

	volatile u32 NVIC_IABR0;
	volatile u32 NVIC_IABR1;
	volatile u32 NVIC_IABR2;
	volatile u32 NVIC_IABR3;
	volatile u32 NVIC_IABR4;
	volatile u32 NVIC_IABR5;
	volatile u32 NVIC_IABR6;
	volatile u32 NVIC_IABR7;

	const u32 Reserved_5[56];

	volatile u32 NVIC_IPRx[60];

}NVIC_REG_t;

#define NVIC  		((volatile NVIC_REG_t*) 0xE000E100)
#define NVIC_STIR	((volatile u32*) 0xE000EF00)
#define AIRCR 		((volatile AIRSCR_t*) 0xE000ED0C)
/***************************************************************************/

#define NVIC_ISCERx_Bits_Num 		32
#define NVIC_REG_NUM0				0
#define NVIC_REG_NUM1				1
#define NVIC_REG_NUM2				2
#define NVIC_REG_NUM3				3
#define NVIC_REG_NUM4				4
#define NVIC_REG_NUM5				5
#define NVIC_REG_NUM6				6
#define NVIC_REG_NUM7				7


void NVIC_EnableIRQ(IRQn_Type IRQn)
{
	u8 irq_reg_num =0;
	u8 irq_bit_num=0;
	irq_reg_num = IRQn / NVIC_ISCERx_Bits_Num;
	irq_bit_num = IRQn % NVIC_ISCERx_Bits_Num;

	switch(irq_reg_num)
	{
		case NVIC_REG_NUM0	:
			NVIC->NVIC_ISER0 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM1	:
			NVIC->NVIC_ISER1 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM2	:
			NVIC->NVIC_ISER2 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM3	:
			NVIC->NVIC_ISER3 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM4	:
			NVIC->NVIC_ISER4 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM5	:
			NVIC->NVIC_ISER5 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM6	:
			NVIC->NVIC_ISER6 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM7	:
			if(irq_bit_num<16)
				NVIC->NVIC_ISER7 |= ((0X01)<<irq_bit_num);
			break;
	}
}

void NVIC_DisableIRQ(IRQn_Type IRQn)
{
	u8 irq_reg_num =0;
	u8 irq_bit_num=0;
	irq_reg_num = IRQn / NVIC_ISCERx_Bits_Num;
	irq_bit_num = IRQn % NVIC_ISCERx_Bits_Num;

	switch(irq_reg_num)
	{
		case NVIC_REG_NUM0:
			NVIC->NVIC_ICER0 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM1:
			NVIC->NVIC_ICER1 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM2:
			NVIC->NVIC_ICER2 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM3:
			NVIC->NVIC_ICER3 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM4:
			NVIC->NVIC_ICER4 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM5:
			NVIC->NVIC_ICER5 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM6:
			NVIC->NVIC_ICER6 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM7:
			if(irq_bit_num<16)
				NVIC->NVIC_ICER7 |= ((0X01)<<irq_bit_num);
			break;
	}
}

void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
	u8 irq_reg_num =0;
	u8 irq_bit_num=0;
	irq_reg_num = IRQn / NVIC_ISCERx_Bits_Num;
	irq_bit_num = IRQn % NVIC_ISCERx_Bits_Num;

	switch(irq_reg_num)
	{
		case NVIC_REG_NUM0:
			NVIC->NVIC_ISPR0 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM1:
			NVIC->NVIC_ISPR1 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM2:
			NVIC->NVIC_ISPR2 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM3:
			NVIC->NVIC_ISPR3 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM4:
			NVIC->NVIC_ISPR4 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM5:
			NVIC->NVIC_ISPR5 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM6:
			NVIC->NVIC_ISPR6 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM7:
			if(irq_bit_num<16)
				NVIC->NVIC_ISPR7 |= ((0X01)<<irq_bit_num);
			break;
	}
}

void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
	u8 irq_reg_num =0;
	u8 irq_bit_num=0;
	irq_reg_num = IRQn / NVIC_ISCERx_Bits_Num;
	irq_bit_num = IRQn % NVIC_ISCERx_Bits_Num;

	switch(irq_reg_num)
	{
		case NVIC_REG_NUM0:
			NVIC->NVIC_ICPR0 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM1:
			NVIC->NVIC_ICPR1 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM2:
			NVIC->NVIC_ICPR2 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM3:
			NVIC->NVIC_ICPR3 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM4:
			NVIC->NVIC_ICPR4 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM5:
			NVIC->NVIC_ICPR5 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM6:
			NVIC->NVIC_ICPR6 |= ((0X01)<<irq_bit_num);
			break;
		case NVIC_REG_NUM7:
			if(irq_bit_num<16)
				NVIC->NVIC_ICPR7 |= ((0X01)<<irq_bit_num);
			break;
	}
}



void NVIC_SetPriority(IRQn_Type IRQn, u32 priority)
{
	u8 irq_reg_num =0;
	u8 irq_bit_num=0;
	irq_reg_num = IRQn / 4;
	irq_bit_num = IRQn % 4;
	u32 buffer = NVIC->NVIC_IPRx[irq_reg_num];
	buffer &=  ~(0xF) << ((8*irq_bit_num)+4);
	buffer |= priority << ((8*irq_bit_num)+4);
	NVIC->NVIC_IPRx[irq_reg_num] = buffer;
}


