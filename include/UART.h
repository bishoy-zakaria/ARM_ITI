#ifndef UART_H
#define UART_H
#include "Std_Types.h"

typedef void(*UART_CallBack_ptr_t)(void);

typedef enum
{
	UART_9600,
	UART_115200
}UART_PaudRate_t;

typedef enum
{
	UART_TXIDLE=0,
	UART_TXREADY,
	UART_TXBUZZY,
	UART_TXBreak
}UART_TXStatus_t;

typedef enum
{
	UART_RXIDLE=0,
	UART_RXREADY,
	UART_RXBUZZY,
	UART_RXBreak
}UART_RXStatus_t;


void UART_Init(UART_PaudRate_t UART_PaudRate);

void UART_Transmit(u8* str , u8 size);
void UART_Recieve(u8* data, u8 size);

void UART_DMA_Init(UART_PaudRate_t UART_PaudRate);
void UART_DMA_Transmit(u8* str , u8 size);
void UART_DMA_Recieve(u8* data, u8 size);

UART_TXStatus_t UART_GetStatusTX(void);
UART_RXStatus_t UART_GetStatusRX(void);

void UART_TX_Notify(UART_CallBack_ptr_t UART_CallBack_ptr);
void UART_RX_Notify(UART_CallBack_ptr_t UART_CallBack_ptr);

void UART_LIN_Init(UART_PaudRate_t UART_PaudRate);
void UART_LIN_SendBreak(void);
void UART_LIN_Notify(UART_CallBack_ptr_t UART_CallBack_ptr);

#endif
