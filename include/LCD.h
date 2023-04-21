#ifndef LCD_H
#define LCD_H

#include "GPIO.h"


typedef enum
{
	IDLE_State=0,
	Ready_State,
	Buzy_State,
}LCD_Status_t;


void LCD_Init(void);
void LCD_Write(const char* data,u8 size, u8 pos_x, u8 pos_y);
void LCD_Clear(void);
LCD_Status_t LCD_GetStatus(void);

extern void LCD_Task(void);



#endif
