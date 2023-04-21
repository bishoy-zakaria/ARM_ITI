#ifndef DMA_H
#define DMA_H

#include "Std_Types.h"


typedef void(*DMA_Call_Ptr)(void);

typedef enum
{
	DMA1=0,
	DMA2
}DMA_Num_t;

typedef enum
{
	Pripheral_To_Memory=0,
	Memory_To_Pripheral,
	Memory_To_Memory
}DMA_Dir_Mode_t;

typedef enum
{
	Stream0=0,
	Stream1,
	Stream2,
	Stream3,
	Stream4,
	Stream5,
	Stream6,
	Stream7
}Stream_Num_t;


typedef enum
{
	Fixed=0,
	Auto_Increament
}Increament_Mode_t;

typedef enum
{
	Byte=0,
	Half_Word,
	Word
}Data_Size_t;

typedef enum
{
	Channel0=0,
	Channel1,
	Channel2,
	Channel3,
	Channel4,
	Channel5,
	Channel6,
	Channel7
}Channel_Num_t;

typedef enum
{
	Normal=0,
	Circular_Buffer,
	Double_Buffer
}DMA_Mode_t;

typedef enum
{
	Ready=0,
	Buzzy,
	Half_Complete
}DMA_Status;


typedef struct
{
	DMA_Num_t			DMA_Num;
	u32* 				Pri_Add;
	u32* 				Mem_Add;
	u32* 				Mem2_Add;
	u32  				Count;
	Data_Size_t 		Size;
	Increament_Mode_t	Memory_Increament_Mode;
	Increament_Mode_t	Pripheral_Increament_Mode;
	DMA_Dir_Mode_t 		DMA_Dir_Mode;
	DMA_Mode_t			DMA_Mode;
	Channel_Num_t		Channel_Num;
	Stream_Num_t		Stream_Num;
	DMA_Call_Ptr		DMA_TC_Notify_ptr;
	DMA_Call_Ptr		DMA_HIF_Notify_ptr;
}DMA_Stream_t;


void DMA_SendData(DMA_Stream_t* DMA_Stream);
void DMA_Start_Stream(DMA_Stream_t* DMA_Stream);
void DMA_Stop_Stream(DMA_Stream_t* DMA_Stream);
DMA_Status DMA_GetStatus(DMA_Stream_t* DMA_Stream);
#endif
