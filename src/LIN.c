#include"LIN.h"
#include "UART.h"
#include "LIN_Slave.h"
#include "LIN_Cfg.h"

typedef enum
{
	BreakDetect=0,
	RecieveSync,
	CheckID,
	Data,
	CheckSum,
	End
}Header_Status_t;

extern LIN_Scheduler_Table_t	LIN_Scheduler_Table[Frame_Num];
extern u8 Frame_Index;
extern u8 ID_Found; //from slave module

LIN_Mode_t   LIN_Mode	= LIN_Master;
LIN_Status_t LIN_Status	= LIN_Ready;


void LIN_Send_Header(void);

void LIN_Master_Task(void)
{
	static u8 counter=0;
	static u8 init=0;

	if(init==0) //initialize LIN
	{
		UART_LIN_Init(UART_9600);
		init=1;
	}

	if(LIN_Status == LIN_Ready)
	{
		UART_LIN_Notify(LIN_Send_Header);
		UART_LIN_SendBreak();
		LIN_Status =LIN_Bussy;
	}

	else if(counter >= LIN_Scheduler_Table[Frame_Index].Slot_Time)
	{
		if(Frame_Index < Frame_Num)
			Frame_Index++;
		else
			Frame_Index=0;

		LIN_Status = LIN_Ready;
		counter=0;
	}
	counter++;
}


LIN_Status_t LIN_Get_Status(void)
{
	return LIN_Status;
}


void LIN_Send_Header(void)
{
	UART_RXStatus_t UART_RXStatus = UART_RXREADY;
	UART_TXStatus_t UART_TXStatus = UART_TXREADY;
	static Header_Status_t Header_Status = BreakDetect;
	static u8 HeaderTX_Buffer=0;
	static u8 HeaderRX_Buffer=0;

	UART_RXStatus = UART_GetStatusRX();
	UART_TXStatus = UART_GetStatusTX();

	if((UART_RXStatus == UART_RXBreak) || (UART_TXStatus == UART_TXBreak))
	{
		Header_Status = BreakDetect;
	}

	switch(Header_Status)
	{
		case BreakDetect:
			HeaderTX_Buffer = 0x55; //sync byte
			UART_DMA_Recieve(&HeaderRX_Buffer, 1); //recieve the sync byte to check
			UART_DMA_Transmit(&HeaderTX_Buffer , 1);
			Header_Status = RecieveSync;
			break;

		case RecieveSync:
			if((UART_RXStatus == UART_RXREADY) && (UART_TXStatus == UART_TXREADY))
			{
				if(HeaderRX_Buffer == 0x55)
				{
					HeaderTX_Buffer = LIN_Scheduler_Table[Frame_Index].Frame_ID;
					UART_DMA_Transmit(&HeaderTX_Buffer , 1);
					Header_Status = CheckID;
				}
			}
			break;

		case CheckID:
			if(UART_RXStatus == UART_RXREADY)
			{
				LIN_Slave_Check_ID(HeaderRX_Buffer);
				if(ID_Found)
				{
					LIN_Slave_Response();
					Header_Status = Data;
				}
				else
				{
					Header_Status = End;
				}
			}
			break;
		case Data:
			Header_Status = End;
			//Header_Status = CheckSum;
			//recieve checksum
			LIN_Status = LIN_Slave_Ready; //till now will modify when checksum
			break;
		case CheckSum:
			break;
		case End:
			LIN_Status = LIN_Slave_Ready;
			break;
	}
}

