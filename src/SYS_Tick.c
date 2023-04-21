#include "SYS_Tick.h"

typedef struct
{
	volatile u32 STK_CTRL;
	volatile u32 STK_LOAD;
	volatile u32 STK_VAL;
	volatile u32 STK_CALIB;
}SysTick_t;


#define SysTick ((volatile SysTick_t*) 0xE000E010)

cbf CallBack_Ptr;


void SysTick_Start(void)
{
	SysTick->STK_CTRL |= 0x01;
}

void SysTick_Stop(void)
{
	SysTick->STK_CTRL &= ~(0x01);
}

void SysTick_ClearValue(void)
{
	SysTick->STK_VAL = 0;
}

SysTick_tenuErrorStatus SysTick_SelectClkSource(SysTick_enuClock_t source)
{
	SysTick_tenuErrorStatus status =SysTick_enuOk;
	switch(source)
	{
		case SysTick_enuAHB_CLK:
			SysTick->STK_CTRL |= 0x04;
			break;
		case SysTick_enuAHB_DIV_8_CLK:
			SysTick->STK_CTRL &= ~(0x04);
			break;
		default:
			status =SysTick_enuNotOk;
	}
	return status;
}

void SysTick_EnableExeption(void)
{
	SysTick->STK_CTRL |= 0x02;
}

SysTick_tenuErrorStatus SysTick_SetPeriodms(u64 time_ms)
{
	SysTick_tenuErrorStatus status =SysTick_enuOk;
	u8 pre_status=0;
	u32 timer_frq=0;
	u32 desired_frq=0;
	u32 reload_val=0;
	pre_status = SysTick->STK_CTRL & 0x04; //get the timer clock
	if(pre_status == 0) // (AHB/8)
	{
		timer_frq   = AHB_CLK/8;
	}
	else	//AHB
	{
		timer_frq = AHB_CLK;
	}

	desired_frq = 1000/time_ms;
	reload_val = timer_frq/desired_frq;
	SysTick->STK_LOAD = reload_val+1;

	return status;

}

SysTick_tenuErrorStatus SysTick_SetCallBack(cbf Add_Function)
{
	SysTick_tenuErrorStatus status =SysTick_enuOk;
	if (Add_Function == Null_Ptr)
	{
		status = SysTick_enuNullPtr;
	}

	else
	{
		CallBack_Ptr = Add_Function;
	}
		return status;
}

void SysTick_Handler(void)
{
	if (CallBack_Ptr != Null_Ptr)
		{
			CallBack_Ptr();

		}
}
