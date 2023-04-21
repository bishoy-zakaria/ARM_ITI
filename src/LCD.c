#include "LCD.h"
#include "LCD_cfg.h"
#include "Bit_Math.h"

typedef enum
{
	LCD_IDLE_Req=0,
	LCD_Write_Req,
	LCD_Clear_Req
}LCD_Req_t;

struct LCD_Buffer_Req_t
{
	const char* data;
	u8 size;
	u8 pos_x;
	u8 pos_y;
	LCD_Req_t LCD_Req;
}LCD_Buffer_Req;

extern GPIO_cfg_t LCD_CFG_Array[LCD_Pin_Num];
LCD_Status_t LCD_Status = IDLE_State;


LCD_Status_t LCD_GetStatus(void)
{
	return LCD_Status;
}




static u8 LCD_SendData(u8 Copy_u8Data);
static u8 LCD_SendCommand(u8 Copy_u8Data);
static u8 LCD_GotoXY(u8 Copy_u8XPos, u8 Copy_u8YPos);

void LCD_Init(void)
{
	static u8 local_status=1;
	u8 iter=0;
	static u8 counter=0;
	switch(local_status)
	{
	case 1:
		for(iter=0 ; iter<LCD_Pin_Num ; iter++)	//GPIO initialization
		{
			GPIO_InitPin(&LCD_CFG_Array[iter]);
		}
		local_status++;
		break;
	case 2:					//delay 100 ms
		if(counter <50)
		{
			counter++;
		}
		else
		{
			counter=0;
			local_status++;
		}
		break;
	case 3:
		if(LCD_SendCommand(0x38)) /* Initialization of 16X2 LCD in 8bit mode */
		{
			local_status++;
		}
		break;
	case 4:
		if(LCD_SendCommand(0x0C))		/* Display ON Cursor OFF */
		{
			local_status++;
		}
		break;
	case 5:
		if(LCD_SendCommand(0x06))		/* Auto Increment cursor */
		{
			local_status++;
		}
		break;
	case 6:
		if(LCD_SendCommand(0x01))	/* clear display */
		{
			local_status++;
		}
		break;
	case 7:					//delay 100 ms
		if(counter <50)
		{
			counter++;
		}
		else
		{
			counter=0;
			local_status++;
		}
		break;
	case 8:
		local_status=0;
		LCD_Status = Ready_State;
		break;
	}
}

void LCD_Write(const char* data,u8 size, u8 pos_x, u8 pos_y)
{
	if(LCD_Status == Ready_State)
	{
		LCD_Buffer_Req.data  	= data;
		LCD_Buffer_Req.size  	= size;
		LCD_Buffer_Req.pos_x 	= pos_x;
		LCD_Buffer_Req.pos_y 	= pos_y;
		LCD_Buffer_Req.LCD_Req 	= LCD_Write_Req;
		LCD_Status = Buzy_State;
	}
}

void LCD_Clear(void)
{
	if(LCD_Status == Ready_State)
	{
		LCD_Buffer_Req.LCD_Req 	= LCD_Clear_Req;
		LCD_Status = Buzy_State;
	}
}


extern void LCD_Task(void)
{
	static u8 index=0;
	static u8 idecator=0;
	switch(LCD_Status)
	{
		case IDLE_State:
			LCD_Init();
			break;
		case Buzy_State:
			switch(LCD_Buffer_Req.LCD_Req)
			{
				case LCD_Write_Req:
					if(idecator == 0)
					{
						if(LCD_GotoXY(LCD_Buffer_Req.pos_x, LCD_Buffer_Req.pos_y))
						{
							idecator=1;
						}
					}
					else
					{
						if(index < LCD_Buffer_Req.size)
						{
							if(LCD_SendData(LCD_Buffer_Req.data[index]))
							{
								index++;
							}
						}

						else
						{
							LCD_Status = Ready_State;
							index=0;
							idecator=0;
						}
					}
					break;
				case LCD_Clear_Req:
					if(idecator == 0)
					{
						if(LCD_SendCommand(0x01))
						{
							idecator=1;
						}
					}

					else
					{
						if(index <50) //delay 100 ms
						{
							index++;
						}
						else
						{
							LCD_Status = Ready_State;
							index=0;
							idecator=0;
						}
					}

					break;
				}
				break;
			default:
				break;
		}

}



static u8 LCD_SendData(u8 Copy_u8Data)
{
	static u8 flage =1 ;
	if(flage == 1)
	{
		GPIO_WritePinValue(LCD_CFG_Array[LCD_RSPin].Port , LCD_CFG_Array[LCD_RSPin].Pin , GPIO_VALUE_HIGH);
		GPIO_WritePinValue(LCD_CFG_Array[LCD_RWPin].Port , LCD_CFG_Array[LCD_RWPin].Pin , GPIO_VALUE_LOW);

		switch(GET_BIT(Copy_u8Data,7))
			{
				case GPIO_VALUE_LOW:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB7Pin].Port  , LCD_CFG_Array[LCD_DB7Pin].Pin , GPIO_VALUE_LOW);
				break;
				case GPIO_VALUE_HIGH:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB7Pin].Port , LCD_CFG_Array[LCD_DB7Pin].Pin , GPIO_VALUE_HIGH);
				break;
			}

			switch(GET_BIT(Copy_u8Data,6))
			{
				case GPIO_VALUE_LOW:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB6Pin].Port , LCD_CFG_Array[LCD_DB6Pin].Pin , GPIO_VALUE_LOW);
				break;
				case GPIO_VALUE_HIGH:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB6Pin].Port , LCD_CFG_Array[LCD_DB6Pin].Pin , GPIO_VALUE_HIGH);

				break;
			}

			switch(GET_BIT(Copy_u8Data,5))
			{
				case GPIO_VALUE_LOW:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB5Pin].Port , LCD_CFG_Array[LCD_DB5Pin].Pin , GPIO_VALUE_LOW);
				break;
				case GPIO_VALUE_HIGH:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB5Pin].Port , LCD_CFG_Array[LCD_DB5Pin].Pin , GPIO_VALUE_HIGH);
				break;
			}

			switch(GET_BIT(Copy_u8Data,4))
			{
				case GPIO_VALUE_LOW:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB4Pin].Port , LCD_CFG_Array[LCD_DB4Pin].Pin , GPIO_VALUE_LOW);
				break;
				case GPIO_VALUE_HIGH:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB4Pin].Port , LCD_CFG_Array[LCD_DB4Pin].Pin , GPIO_VALUE_HIGH);
				break;
			}

			switch(GET_BIT(Copy_u8Data,3))
			{
				case GPIO_VALUE_LOW:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB3Pin].Port , LCD_CFG_Array[LCD_DB3Pin].Pin , GPIO_VALUE_LOW);
				break;
				case GPIO_VALUE_HIGH:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB3Pin].Port , LCD_CFG_Array[LCD_DB3Pin].Pin , GPIO_VALUE_HIGH);
				break;
			}

			switch(GET_BIT(Copy_u8Data,2))
			{
				case GPIO_VALUE_LOW:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB2Pin].Port , LCD_CFG_Array[LCD_DB2Pin].Pin , GPIO_VALUE_LOW);
				break;
				case GPIO_VALUE_HIGH:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB2Pin].Port , LCD_CFG_Array[LCD_DB2Pin].Pin , GPIO_VALUE_HIGH);
				break;
			}

			switch(GET_BIT(Copy_u8Data,1))
			{
				case GPIO_VALUE_LOW:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB1Pin].Port , LCD_CFG_Array[LCD_DB1Pin].Pin , GPIO_VALUE_LOW);
				break;
				case GPIO_VALUE_HIGH:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB1Pin].Port , LCD_CFG_Array[LCD_DB1Pin].Pin , GPIO_VALUE_HIGH);
				break;
			}

			switch(GET_BIT(Copy_u8Data,0))
			{
				case GPIO_VALUE_LOW:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB0Pin].Port , LCD_CFG_Array[LCD_DB0Pin].Pin , GPIO_VALUE_LOW);
				break;
				case GPIO_VALUE_HIGH:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB0Pin].Port , LCD_CFG_Array[LCD_DB0Pin].Pin , GPIO_VALUE_HIGH);
				break;
			}

			GPIO_WritePinValue(LCD_CFG_Array[LCD_EPin].Port , LCD_CFG_Array[LCD_EPin].Pin , GPIO_VALUE_HIGH);
			flage=0;
	}

	else if(flage == 0)
	{
		GPIO_WritePinValue(LCD_CFG_Array[LCD_EPin].Port , LCD_CFG_Array[LCD_EPin].Pin , GPIO_VALUE_LOW);
		flage=1;
	}

	return flage;
}


static u8 LCD_SendCommand(u8 Copy_u8Data)
{
	static u8 flage =1 ;
	if(flage == 1)
	{
		GPIO_WritePinValue(LCD_CFG_Array[LCD_RSPin].Port , LCD_CFG_Array[LCD_RSPin].Pin , GPIO_VALUE_LOW);
		GPIO_WritePinValue(LCD_CFG_Array[LCD_RWPin].Port , LCD_CFG_Array[LCD_RWPin].Pin , GPIO_VALUE_LOW);

		switch(GET_BIT(Copy_u8Data,7))
			{
				case GPIO_VALUE_LOW:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB7Pin].Port , LCD_CFG_Array[LCD_DB7Pin].Pin , GPIO_VALUE_LOW);
				break;
				case GPIO_VALUE_HIGH:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB7Pin].Port , LCD_CFG_Array[LCD_DB7Pin].Pin , GPIO_VALUE_HIGH);
				break;
			}

			switch(GET_BIT(Copy_u8Data,6))
			{
				case GPIO_VALUE_LOW:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB6Pin].Port , LCD_CFG_Array[LCD_DB6Pin].Pin , GPIO_VALUE_LOW);
				break;
				case GPIO_VALUE_HIGH:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB6Pin].Port , LCD_CFG_Array[LCD_DB6Pin].Pin , GPIO_VALUE_HIGH);

				break;
			}

			switch(GET_BIT(Copy_u8Data,5))
			{
				case GPIO_VALUE_LOW:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB5Pin].Port , LCD_CFG_Array[LCD_DB5Pin].Pin , GPIO_VALUE_LOW);
				break;
				case GPIO_VALUE_HIGH:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB5Pin].Port , LCD_CFG_Array[LCD_DB5Pin].Pin , GPIO_VALUE_HIGH);
				break;
			}

			switch(GET_BIT(Copy_u8Data,4))
			{
				case GPIO_VALUE_LOW:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB4Pin].Port , LCD_CFG_Array[LCD_DB4Pin].Pin , GPIO_VALUE_LOW);
				break;
				case GPIO_VALUE_HIGH:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB4Pin].Port , LCD_CFG_Array[LCD_DB4Pin].Pin , GPIO_VALUE_HIGH);
				break;
			}

			switch(GET_BIT(Copy_u8Data,3))
			{
				case GPIO_VALUE_LOW:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB3Pin].Port , LCD_CFG_Array[LCD_DB3Pin].Pin , GPIO_VALUE_LOW);
				break;
				case GPIO_VALUE_HIGH:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB3Pin].Port , LCD_CFG_Array[LCD_DB3Pin].Pin , GPIO_VALUE_HIGH);
				break;
			}

			switch(GET_BIT(Copy_u8Data,2))
			{
				case GPIO_VALUE_LOW:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB2Pin].Port , LCD_CFG_Array[LCD_DB2Pin].Pin , GPIO_VALUE_LOW);
				break;
				case GPIO_VALUE_HIGH:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB2Pin].Port , LCD_CFG_Array[LCD_DB2Pin].Pin , GPIO_VALUE_HIGH);
				break;
			}

			switch(GET_BIT(Copy_u8Data,1))
			{
				case GPIO_VALUE_LOW:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB1Pin].Port , LCD_CFG_Array[LCD_DB1Pin].Pin , GPIO_VALUE_LOW);
				break;
				case GPIO_VALUE_HIGH:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB1Pin].Port , LCD_CFG_Array[LCD_DB1Pin].Pin , GPIO_VALUE_HIGH);
				break;
			}

			switch(GET_BIT(Copy_u8Data,0))
			{
				case GPIO_VALUE_LOW:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB0Pin].Port , LCD_CFG_Array[LCD_DB0Pin].Pin , GPIO_VALUE_LOW);
				break;
				case GPIO_VALUE_HIGH:
					GPIO_WritePinValue(LCD_CFG_Array[LCD_DB0Pin].Port , LCD_CFG_Array[LCD_DB0Pin].Pin , GPIO_VALUE_HIGH);
				break;
			}

			GPIO_WritePinValue(LCD_CFG_Array[LCD_EPin].Port , LCD_CFG_Array[LCD_EPin].Pin , GPIO_VALUE_HIGH);
			flage=0;
	}

	else if(flage == 0)
	{
		GPIO_WritePinValue(LCD_CFG_Array[LCD_EPin].Port , LCD_CFG_Array[LCD_EPin].Pin , GPIO_VALUE_LOW);
		flage=1;
	}

	return flage;
}


static u8 LCD_GotoXY(u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	static u8 flage=0;
	u8 pos[2] = {0x80 , 0xC0};
	if(flage == 0)
	{
		if(LCD_SendCommand(pos[Copy_u8XPos]+Copy_u8YPos))
		{
			flage =1;
		}
	}

	else
	{
		flage =0;
	}

	return flage;
}

