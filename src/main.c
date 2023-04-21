#include "RCC.h"
#include "LCD.h"
#include "UART.h"
#include "Scheduler.h"

char buffer;

void APP_1(void)
{
	static u8 i=0;
	if(i == 0 && (LCD_GetStatus() == Ready_State))
	{
		LCD_Write("Bishoy Zakaria",14, 0, 1);
		i++;
	}

	if(i == 1 && (LCD_GetStatus() == Ready_State))
	{
		LCD_Write("ITI",3, 1, 5);
		i++;
	}

	else if(i == 2 && (LCD_GetStatus() == Ready_State))
	{
		LCD_Clear();
		i=0;
	}
}

void LCD_Function(void)
{
	static u8 counter=0;
	if(counter <16)
	{
		LCD_Write(&buffer,1, 0, counter);
		counter++;
	}
	else
	{
		LCD_Clear();
		counter=0;
	}
}

int main(void)
{
	RCC_enuSystemClockInit();
	UART_DMA_Init(UART_9600);
	UART_RX_Notify(LCD_Function);
	UART_DMA_Recieve(&buffer, 1);
	Sched_Init();
	Sched_Start();


return 0;
}
