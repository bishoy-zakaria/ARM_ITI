#include "Std_Types.h"

#ifndef SYS_TICK_H
#define SYS_TICK_H

#define AHB_CLK		16000000

typedef void(*cbf)(void);

typedef enum
{
	SysTick_enuAHB_CLK=0,
	SysTick_enuAHB_DIV_8_CLK
}SysTick_enuClock_t;


typedef enum
{
	SysTick_enuOk=0,
	SysTick_enuNotOk,
	SysTick_enuNullPtr
}SysTick_tenuErrorStatus;


void SysTick_Start(void);
void SysTick_Stop(void);
void SysTick_ClearValue(void);
SysTick_tenuErrorStatus SysTick_SelectClkSource(SysTick_enuClock_t);
void SysTick_EnableExeption(void);
SysTick_tenuErrorStatus SysTick_SetPeriodms(u64);
SysTick_tenuErrorStatus SysTick_SetCallBack(cbf Add_Function);

#endif
