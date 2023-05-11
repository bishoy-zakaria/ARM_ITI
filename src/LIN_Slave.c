#include "Std_Types.h"
#include "UART.h"
#include "LIN_Slave.h"
#include "LIN_Slave_Cfg.h"


typedef enum
{
	Break=0,
	SyncCheck,
	IDCheck,
	Data,
	CheckSum,
	End
}Header_Status_t;


extern LIN_Slave_Frame_t	LIN_Slave_Frame[Frame_Number];

LIN_Slave_Status_t LIN_Slave_Status = LIN_Slave_Ready;

u8 ID_Found=0;
u8 Required_Frame_Index;
LIN_Slave_Response_t Required_Response;


void LIN_Slave_Handeler(void);

void LIN_Slave_Task(void)
{
	if(LIN_Slave_Status == LIN_Slave_Ready)
	{
		UART_LIN_Init(UART_9600);
		UART_LIN_Notify(LIN_Slave_Handeler);
	}
}


void LIN_Slave_Handeler(void)
{
	UART_RXStatus_t UART_RXStatus = UART_RXREADY;
	static Header_Status_t Header_Status = Break;
	static u8 HeaderRX_Buffer=0;

	UART_RXStatus = UART_GetStatusRX();

	if(UART_RXStatus == UART_RXBreak)
	{
		Header_Status = Break;
	}

	switch(Header_Status)
	{
		case Break:
				LIN_Slave_Status = LIN_Slave_Bussy;
				UART_DMA_Recieve(&HeaderRX_Buffer, 1); //recieve the sync byte to check
				Header_Status = SyncCheck;
				break;

		case SyncCheck:
			if(UART_RXStatus == UART_RXREADY)
			{
				if(HeaderRX_Buffer == 0x55)
				{
					UART_DMA_Recieve(&HeaderRX_Buffer, 1); //recieve Frame ID
					Header_Status = IDCheck;
				}
			}
			break;
		case IDCheck:
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
			LIN_Slave_Status = LIN_Slave_Ready; //till now will modify when checksum
			break;
		case CheckSum:
			break;
		case End:
			LIN_Slave_Status = LIN_Slave_Ready;
			break;
	}

}


void LIN_Slave_Check_ID(u8 Slave_RX_ID)
{
	u8 iter=0;

	for(iter=0 ; iter< Frame_Number ; iter++)
	{
		if(LIN_Slave_Frame[iter].LIN_Frame->ID == Slave_RX_ID)
		{
			ID_Found = 1;
			Required_Frame_Index = iter;
			Required_Response	 = LIN_Slave_Frame[iter].LIN_Slave_Response;
			break;
		}
		else
		{
			ID_Found=0;
		}

	}
}

void LIN_Slave_Response(void)
{
	u8 frame_size = LIN_Slave_Frame[Required_Frame_Index].LIN_Frame->Byte_Num;
	if(Required_Response == LIN_Slave_TX)
	{
		UART_DMA_Transmit(LIN_Slave_Frame[Required_Frame_Index].LIN_Frame->Signals , frame_size);
	}

	else
	{
		UART_DMA_Recieve(LIN_Slave_Frame[Required_Frame_Index].LIN_Frame->Signals , frame_size);
	}

}

void LIN_Slave_CheckSum(void)
{

}

LIN_Slave_Status_t LIN_Slave_GetStatus(void)
{
	return LIN_Slave_Status;
}
