#include "UART.h"
#include "Bit_Math.h"
#include "GPIO.h"
#include "NVIC.h"
#include "DMA.h"

#define UART1_TX_GPIO_PORT		GPIO_PORT_A
#define UART1_RX_GPIO_PORT		GPIO_PORT_A
#define UART1_TX_GPIO_PIN		GPIO_PIN_9
#define UART1_RX_GPIO_PIN		GPIO_PIN_10
#define UART1_TX_GPIO_AF		GPIO_AF7
#define UART1_RX_GPIO_AF		GPIO_AF7
#define UART1_NVIC_IRQ			IRQ37
#define DMA_Stream5_NVIC_IRQ	IRQ68
#define DMA_Stream7_NVIC_IRQ	IRQ70


typedef struct
{
	volatile u32 USART_SR;
	volatile u32 USART_DR;
	volatile u32 USART_BRR;
	volatile u32 USART_CR1;
	volatile u32 USART_CR2;
	volatile u32 USART_CR3;
	volatile u32 USART_GTPR;
}UART_REG_t;

#define UART1_REG	((volatile UART_REG_t*)0x40011000)

u8 UART_DMA;
UART_CallBack_ptr_t UART_TX_CallBack_ptr;
UART_CallBack_ptr_t UART_RX_CallBack_ptr;
UART_CallBack_ptr_t UART_LIN_CallBack_ptr;


struct UART_TXBuffer_t
{
	u8* data_ptr;
	u8  lenth;
	u8 	index;
}UART_TXBuffer;

struct UART_RXBuffer_t
{
	u8* data_ptr;
	u8  lenth;
	u8 	index;
}UART_RXBuffer;


UART_TXStatus_t UART_TXStatus = UART_TXIDLE;
UART_RXStatus_t UART_RXStatus = UART_RXIDLE;


void UART_DMA_RX_Notify(void);

void UART_Init(UART_PaudRate_t UART_PaudRate)
{
	u32 paudrate_reg_buffer=0;
	GPIO_cfg_t TX_pin = {
							.Port 	= UART1_TX_GPIO_PORT,
							.Pin	= UART1_TX_GPIO_PIN,
							.Speed	= GPIO_SPEED_HIGH,
							.Mode	= GPIO_MODE_AF_PP_FLOAT
						};

	GPIO_cfg_t RX_pin = {
								.Port 	= UART1_RX_GPIO_PORT,
								.Pin	= UART1_RX_GPIO_PIN,
								.Speed	= GPIO_SPEED_HIGH,
								.Mode	= GPIO_MODE_AF_PP_FLOAT
							};

	GPIO_InitPin(&TX_pin);				//initialize GPIO TX,RX pins
	GPIO_InitPin(&RX_pin);
	GPIO_Select_AF(UART1_TX_GPIO_PORT, UART1_TX_GPIO_PIN ,UART1_TX_GPIO_AF);
	GPIO_Select_AF(UART1_RX_GPIO_PORT, UART1_RX_GPIO_PIN ,UART1_RX_GPIO_AF);

	NVIC_EnableIRQ(UART1_NVIC_IRQ);		//initialize NVIC enable IRQ

	SET_BIT(UART1_REG->USART_CR1,2); 	//reciever enable
	SET_BIT(UART1_REG->USART_CR1,3); 	//transmitter enable
	SET_BIT(UART1_REG->USART_CR1,13);	//enable UART
	switch (UART_PaudRate)
	{
		case UART_9600:
			paudrate_reg_buffer  |= 0x3; 			//DIV_FARCTION
			paudrate_reg_buffer  |= ((0x68)<<4);		//DIV_Mantissa
			UART1_REG->USART_BRR |= paudrate_reg_buffer;
			break;
		case UART_115200:
			paudrate_reg_buffer  |= 0xB;			//DIV_FARCTION
			paudrate_reg_buffer  |= ((0x8)<<4);	//DIV_Mantissa
			UART1_REG->USART_BRR |= paudrate_reg_buffer;
			break;
	}

	UART_TXStatus = UART_TXREADY;
	UART_RXStatus = UART_RXREADY;
}

void UART_Transmit(u8* str , u8 size)
{
	if(UART_TXStatus == UART_TXREADY)
	{
		if(str != Null_Ptr)
		{
			UART_TXBuffer.data_ptr 	= str;
			UART_TXBuffer.lenth		= size;
			UART_TXBuffer.index		= 0;
			UART1_REG->USART_DR = UART_TXBuffer.data_ptr[UART_TXBuffer.index];
			UART_TXStatus = UART_TXBUZZY;
			SET_BIT(UART1_REG->USART_CR1,6); //transmit complete interrupt enable
		}
	}
}

void UART_Recieve(u8* data, u8 size)
{
	if(UART_RXStatus == UART_RXREADY)
		{
			if(data != Null_Ptr)
			{
				UART_RXBuffer.data_ptr 	= data;
				UART_RXBuffer.lenth		= size;
				UART_RXBuffer.index		= 0;
				UART_RXStatus = UART_RXBUZZY;
				SET_BIT(UART1_REG->USART_CR1,5); //recieve complete interrupt enable

			}
		}
}


void UART_DMA_Init(UART_PaudRate_t UART_PaudRate)
{
	u32 paudrate_reg_buffer=0;
	GPIO_cfg_t TX_pin = {
							.Port 	= UART1_TX_GPIO_PORT,
							.Pin	= UART1_TX_GPIO_PIN,
							.Speed	= GPIO_SPEED_HIGH,
							.Mode	= GPIO_MODE_AF_PP_FLOAT
						};

	GPIO_cfg_t RX_pin = {
								.Port 	= UART1_RX_GPIO_PORT,
								.Pin	= UART1_RX_GPIO_PIN,
								.Speed	= GPIO_SPEED_HIGH,
								.Mode	= GPIO_MODE_AF_PP_FLOAT
							};

	GPIO_InitPin(&TX_pin);				//initialize GPIO TX,RX pins
	GPIO_InitPin(&RX_pin);
	GPIO_Select_AF(UART1_TX_GPIO_PORT, UART1_TX_GPIO_PIN ,UART1_TX_GPIO_AF);
	GPIO_Select_AF(UART1_RX_GPIO_PORT, UART1_RX_GPIO_PIN ,UART1_RX_GPIO_AF);

	NVIC_EnableIRQ(UART1_NVIC_IRQ);		//initialize NVIC enable IRQ
	NVIC_EnableIRQ(DMA_Stream5_NVIC_IRQ);		//initialize NVIC enable IRQ
	NVIC_EnableIRQ(DMA_Stream7_NVIC_IRQ);		//initialize NVIC enable IRQ

	SET_BIT(UART1_REG->USART_CR1,2); 	//reciever enable
	SET_BIT(UART1_REG->USART_CR1,3); 	//transmitter enable
	SET_BIT(UART1_REG->USART_CR1,13);	//enable UART
	switch (UART_PaudRate)
	{
		case UART_9600:
			paudrate_reg_buffer  |= 0x3; 			//DIV_FARCTION
			paudrate_reg_buffer  |= ((0x68)<<4);		//DIV_Mantissa
			UART1_REG->USART_BRR |= paudrate_reg_buffer;
			break;
		case UART_115200:
			paudrate_reg_buffer  |= 0xB;			//DIV_FARCTION
			paudrate_reg_buffer  |= ((0x8)<<4);	//DIV_Mantissa
			UART1_REG->USART_BRR |= paudrate_reg_buffer;
			break;
	}

	UART_TXStatus = UART_TXREADY;
	UART_RXStatus = UART_RXREADY;
}

void UART_DMA_Transmit(u8* str , u8 size)
{
	DMA_Stream_t TX_Stream;
	if(UART_TXStatus == UART_TXREADY)
		{
			if(str != Null_Ptr)
			{

				TX_Stream.DMA_Num  					= DMA2;
				TX_Stream.Pri_Add  					= (u32*)0x40011004;
				TX_Stream.Mem_Add  					= (u32*)str;
				TX_Stream.Mem2_Add 					= Null_Ptr;
				TX_Stream.Count	  					= size;
				TX_Stream.Size	  					= Byte;
				TX_Stream.Memory_Increament_Mode	= Auto_Increament;
				TX_Stream.Pripheral_Increament_Mode = Fixed;
				TX_Stream.DMA_Dir_Mode				= Memory_To_Pripheral;
				TX_Stream.DMA_Mode					= Normal;
				TX_Stream.Channel_Num				= Channel4;
				TX_Stream.Stream_Num				= Stream7;
				TX_Stream.DMA_TC_Notify_ptr			= Null_Ptr;
				TX_Stream.DMA_HIF_Notify_ptr		= Null_Ptr;

				SET_BIT(UART1_REG->USART_CR3,7);
				DMA_SendData(&TX_Stream);
				UART_DMA=1;
				UART_TXStatus = UART_TXBUZZY;
				DMA_Start_Stream(&TX_Stream);
				SET_BIT(UART1_REG->USART_CR1,6); //transmit complete interrupt enable
			}
		}
}
void UART_DMA_Recieve(u8* data, u8 size)
{
	DMA_Stream_t RX_Stream;
	if(UART_RXStatus == UART_RXREADY)
		{
			if(data != Null_Ptr)
			{

				RX_Stream.DMA_Num  					= DMA2;
				RX_Stream.Pri_Add  					= (u32*)0x40011004;
				RX_Stream.Mem_Add  					= (u32*)data;
				RX_Stream.Mem2_Add 					= Null_Ptr;
				RX_Stream.Count	  					= size;
				RX_Stream.Size	  					= Byte;
				RX_Stream.Memory_Increament_Mode	= Auto_Increament;
				RX_Stream.Pripheral_Increament_Mode = Fixed;
				RX_Stream.DMA_Dir_Mode				= Pripheral_To_Memory;
				RX_Stream.DMA_Mode					= Normal;
				RX_Stream.Channel_Num				= Channel4;
				RX_Stream.Stream_Num				= Stream5;
				RX_Stream.DMA_TC_Notify_ptr			= UART_DMA_RX_Notify;
				RX_Stream.DMA_HIF_Notify_ptr		= Null_Ptr;

				SET_BIT(UART1_REG->USART_CR3,6);
				DMA_SendData(&RX_Stream);
				DMA_Start_Stream(&RX_Stream);
				UART_RXStatus = UART_RXBUZZY;
			}
		}
}


UART_TXStatus_t UART_GetStatusTX(void)
{
	return UART_TXStatus;
}

UART_RXStatus_t UART_GetStatusRX(void)
{
	return UART_RXStatus;
}


void UART_TX_Notify(UART_CallBack_ptr_t UART_CallBack_ptr)
{
	UART_TX_CallBack_ptr = UART_CallBack_ptr;
}
void UART_RX_Notify(UART_CallBack_ptr_t UART_CallBack_ptr)
{
	UART_RX_CallBack_ptr = UART_CallBack_ptr;
}

void UART_DMA_RX_Notify(void)
{
	UART_RXStatus = UART_RXREADY;
	UART_RX_CallBack_ptr();
}


void UART_LIN_Init(UART_PaudRate_t UART_PaudRate)
{
		u32 paudrate_reg_buffer=0;
		GPIO_cfg_t TX_pin = {
								.Port 	= UART1_TX_GPIO_PORT,
								.Pin	= UART1_TX_GPIO_PIN,
								.Speed	= GPIO_SPEED_HIGH,
								.Mode	= GPIO_MODE_AF_PP_FLOAT
							};

		GPIO_cfg_t RX_pin = {
									.Port 	= UART1_RX_GPIO_PORT,
									.Pin	= UART1_RX_GPIO_PIN,
									.Speed	= GPIO_SPEED_HIGH,
									.Mode	= GPIO_MODE_AF_PP_FLOAT
								};

		GPIO_InitPin(&TX_pin);				//initialize GPIO TX,RX pins
		GPIO_InitPin(&RX_pin);
		GPIO_Select_AF(UART1_TX_GPIO_PORT, UART1_TX_GPIO_PIN ,UART1_TX_GPIO_AF);
		GPIO_Select_AF(UART1_RX_GPIO_PORT, UART1_RX_GPIO_PIN ,UART1_RX_GPIO_AF);

		NVIC_EnableIRQ(UART1_NVIC_IRQ);		//initialize NVIC enable IRQ
		NVIC_EnableIRQ(DMA_Stream5_NVIC_IRQ);		//initialize NVIC enable IRQ
		NVIC_EnableIRQ(DMA_Stream7_NVIC_IRQ);		//initialize NVIC enable IRQ

		SET_BIT(UART1_REG->USART_CR1,2); 	//reciever enable
		SET_BIT(UART1_REG->USART_CR1,3); 	//transmitter enable

		CLR_BIT(UART1_REG->USART_CR1,12);
		CLR_BIT(UART1_REG->USART_CR2,11);
		CLR_BIT(UART1_REG->USART_CR2,12);
		CLR_BIT(UART1_REG->USART_CR2,13);
		CLR_BIT(UART1_REG->USART_CR3,1);
		CLR_BIT(UART1_REG->USART_CR3,3);
		CLR_BIT(UART1_REG->USART_CR3,5);

		SET_BIT(UART1_REG->USART_CR2,14); 	//LIN Mode enable
		SET_BIT(UART1_REG->USART_CR2,6); 	//Break flag enable

		SET_BIT(UART1_REG->USART_CR1,13);	//enable UART
		switch (UART_PaudRate)
		{
			case UART_9600:
				paudrate_reg_buffer  |= 0x3; 			//DIV_FARCTION
				paudrate_reg_buffer  |= ((0x68)<<4);		//DIV_Mantissa
				UART1_REG->USART_BRR |= paudrate_reg_buffer;
				break;
			case UART_115200:
				paudrate_reg_buffer  |= 0xB;			//DIV_FARCTION
				paudrate_reg_buffer  |= ((0x8)<<4);	//DIV_Mantissa
				UART1_REG->USART_BRR |= paudrate_reg_buffer;
				break;
		}

		UART_TXStatus = UART_TXREADY;
		UART_RXStatus = UART_RXREADY;

}

void UART_LIN_SendBreak(void)
{
	SET_BIT(UART1_REG->USART_CR1,0); //send break
}

void UART_LIN_Notify(UART_CallBack_ptr_t UART_CallBack_ptr)
{
	UART_LIN_CallBack_ptr 	= UART_CallBack_ptr;
	UART_RX_CallBack_ptr	= UART_CallBack_ptr; //for DMA notify
}


void USART1_IRQHandler(void)
{

	if(GET_BIT(UART1_REG->USART_SR,8))
	{
		UART_TXStatus = UART_TXBreak;
		UART_RXStatus = UART_RXBreak;
	}

	if((GET_BIT(UART1_REG->USART_SR,6)) && (UART_TXStatus == UART_TXBUZZY)) //Transmit complete
	{
		if(UART_DMA==1)
		{
			if(UART_TX_CallBack_ptr != Null_Ptr)
				UART_TX_CallBack_ptr();
			UART_DMA=0;
			UART_TXStatus =UART_TXREADY;
			CLR_BIT(UART1_REG->USART_CR1,6); //transmit complete interrupt disable
		}

		else{

		if(UART_TXBuffer.index <= UART_TXBuffer.lenth)
		{
			if((UART_TXBuffer.data_ptr+UART_TXBuffer.index) != Null_Ptr)
			{
				UART1_REG->USART_DR = UART_TXBuffer.data_ptr[UART_TXBuffer.index];
				UART_TXBuffer.index++;
			}
		}
		else
		{
			UART_TXStatus =UART_TXREADY;
			UART_TXBuffer.index=0;
			if(UART_TX_CallBack_ptr != Null_Ptr)
				UART_TX_CallBack_ptr();
			CLR_BIT(UART1_REG->USART_CR1,6); //transmit complete interrupt disable
		}
		}
	}

	if((GET_BIT(UART1_REG->USART_SR,5)) && (UART_RXStatus == UART_RXBUZZY)) //Recieve complete
	{
		if(UART_RXBuffer.index <= UART_RXBuffer.lenth)
		{
			if((UART_RXBuffer.data_ptr+UART_RXBuffer.index) != Null_Ptr)
			{
				UART_RXBuffer.data_ptr[UART_RXBuffer.index] = UART1_REG->USART_DR;
				UART_RXBuffer.index++;
			}
		}

		else
		{
			UART_RXStatus =UART_RXREADY;
			UART_RXBuffer.index=0;
			if(UART_RX_CallBack_ptr != Null_Ptr)
				UART_RX_CallBack_ptr();
			CLR_BIT(UART1_REG->USART_CR1,5); //recieve complete interrupt disable
		}
	}


	if (UART_LIN_CallBack_ptr != Null_Ptr)
	{
		UART_LIN_CallBack_ptr();
	}


}
