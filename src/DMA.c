#include "DMA.h"

typedef struct
{
	volatile u32 DMA_CR;
	volatile u32 DMA_NDTR;
	volatile u32 DMA_PAR;
	volatile u32 DMA_M0AR;
	volatile u32 DMA_M1AR;
	volatile u32 DMA_FRC;
}Stream_reg_t;

typedef struct
{
	volatile u32 DMA_LISR;
	volatile u32 DMA_HISR;
	volatile u32 DMA_LIFCR;
	volatile u32 DMA_HIFCR;
	volatile Stream_reg_t stream[8];
}DMA_t;

#define DMA1_REG ((volatile DMA_t*)	0x40026000)
#define DMA2_REG ((volatile DMA_t*)	0x40026400)

void (*DMA_TC_Notify_arr[8])(void);
void (*DMA_HIF_Notify_arr[8])(void);
u8 DMA_Stream_Status_arr[8];
void (*DMA2_TC_Notify_arr[8])(void);
void (*DMA2_HIF_Notify_arr[8])(void);
u8 DMA2_Stream_Status_arr[8];

void DMA_SendData(DMA_Stream_t* DMA_Stream)
{
	u32 Register_buffer=0;
	switch(DMA_Stream->DMA_Num)
	{
		case DMA1:
			switch(DMA_Stream->DMA_Mode)
			{
				case Normal:
					if(DMA_Stream_Status_arr[DMA_Stream->Stream_Num] == Ready){

					Register_buffer |= (DMA_Stream->Channel_Num <<25);
					Register_buffer |= (DMA_Stream->Size <<13); // memory size
					Register_buffer |= (DMA_Stream->Size <<11); // peripheral size
					Register_buffer |= (DMA_Stream->Memory_Increament_Mode <<10);
					Register_buffer |= (DMA_Stream->Pripheral_Increament_Mode <<9);
					Register_buffer |= (DMA_Stream->DMA_Dir_Mode <<6);

					Register_buffer |= (1<<4); //TC interrupt enable

					DMA_HIF_Notify_arr[DMA_Stream->Stream_Num] 		= DMA_Stream->DMA_HIF_Notify_ptr;
					DMA_TC_Notify_arr[DMA_Stream->Stream_Num] 		= DMA_Stream->DMA_TC_Notify_ptr;
					DMA_Stream_Status_arr[DMA_Stream->Stream_Num] 	= Buzzy;

					DMA1_REG->stream[DMA_Stream->Stream_Num].DMA_CR 	= Register_buffer; 		// control register
					DMA1_REG->stream[DMA_Stream->Stream_Num].DMA_NDTR	= DMA_Stream->Count; 	// number of data
					DMA1_REG->stream[DMA_Stream->Stream_Num].DMA_PAR	= (u32)DMA_Stream->Pri_Add; 	// peripheral address
					DMA1_REG->stream[DMA_Stream->Stream_Num].DMA_M0AR	= (u32)DMA_Stream->Mem_Add; 	// memory address
					}
					break;

				case Circular_Buffer:
					if(DMA_Stream_Status_arr[DMA_Stream->Stream_Num] == Ready){

					Register_buffer |= (DMA_Stream->Channel_Num <<25);
					Register_buffer |= (DMA_Stream->Size <<13); // memory size
					Register_buffer |= (DMA_Stream->Size <<11); // peripheral size
					Register_buffer |= (DMA_Stream->Memory_Increament_Mode <<10);
					Register_buffer |= (DMA_Stream->Pripheral_Increament_Mode <<9);
					Register_buffer |= (DMA_Stream->DMA_Dir_Mode <<6);

					Register_buffer |= (1<<8); //circular mode on
					Register_buffer |= (1<<4); //TC interrupt enable
					Register_buffer |= (1<<3); //HIF interrupt enable

					DMA_HIF_Notify_arr[DMA_Stream->Stream_Num] 		= DMA_Stream->DMA_HIF_Notify_ptr;
					DMA_TC_Notify_arr[DMA_Stream->Stream_Num] 		= DMA_Stream->DMA_TC_Notify_ptr;
					DMA_Stream_Status_arr[DMA_Stream->Stream_Num] 	= Buzzy;

					DMA1_REG->stream[DMA_Stream->Stream_Num].DMA_CR 	= Register_buffer; 		// control register
					DMA1_REG->stream[DMA_Stream->Stream_Num].DMA_NDTR	= DMA_Stream->Count; 	// number of data
					DMA1_REG->stream[DMA_Stream->Stream_Num].DMA_PAR	= (u32)DMA_Stream->Pri_Add; 	// peripheral address
					DMA1_REG->stream[DMA_Stream->Stream_Num].DMA_M0AR	= (u32)DMA_Stream->Mem_Add; 	// memory address
					}
					break;

				case Double_Buffer:
					if(DMA_Stream_Status_arr[DMA_Stream->Stream_Num] == Ready){

					Register_buffer |= (DMA_Stream->Channel_Num <<25);
					Register_buffer |= (DMA_Stream->Size <<13); // memory size
					Register_buffer |= (DMA_Stream->Size <<11); // peripheral size
					Register_buffer |= (DMA_Stream->Memory_Increament_Mode <<10);
					Register_buffer |= (DMA_Stream->Pripheral_Increament_Mode <<9);
					Register_buffer |= (DMA_Stream->DMA_Dir_Mode <<6);

					Register_buffer |= (1<<18); //double buffer mode on
					Register_buffer |= (1<<4); //TC interrupt enable
					Register_buffer |= (1<<3); //HIF interrupt enable

					DMA_HIF_Notify_arr[DMA_Stream->Stream_Num] 		= DMA_Stream->DMA_HIF_Notify_ptr;
					DMA_TC_Notify_arr[DMA_Stream->Stream_Num] 		= DMA_Stream->DMA_TC_Notify_ptr;
					DMA_Stream_Status_arr[DMA_Stream->Stream_Num] 	= Buzzy;

					DMA1_REG->stream[DMA_Stream->Stream_Num].DMA_CR 	= Register_buffer; 		// control register
					DMA1_REG->stream[DMA_Stream->Stream_Num].DMA_NDTR	= DMA_Stream->Count; 	// number of data
					DMA1_REG->stream[DMA_Stream->Stream_Num].DMA_PAR	= (u32)DMA_Stream->Pri_Add; 	// peripheral address
					DMA1_REG->stream[DMA_Stream->Stream_Num].DMA_M0AR	= (u32)DMA_Stream->Mem_Add; 	// memory address1
					if(DMA_Stream->Mem2_Add != Null_Ptr)
						DMA1_REG->stream[DMA_Stream->Stream_Num].DMA_M1AR	= (u32)DMA_Stream->Mem2_Add; 	// memory2 address2
					}
					break;
			}
			break;

		case DMA2:
			switch(DMA_Stream->DMA_Mode)
			{
				case Normal:
					if(DMA_Stream_Status_arr[DMA_Stream->Stream_Num] == Ready){

					Register_buffer |= (DMA_Stream->Channel_Num <<25);
					Register_buffer |= (DMA_Stream->Size <<13); // memory size
					Register_buffer |= (DMA_Stream->Size <<11); // peripheral size
					Register_buffer |= (DMA_Stream->Memory_Increament_Mode <<10);
					Register_buffer |= (DMA_Stream->Pripheral_Increament_Mode <<9);
					Register_buffer |= (DMA_Stream->DMA_Dir_Mode <<6);

					Register_buffer |= (1<<4); //TC interrupt enable

					DMA2_HIF_Notify_arr[DMA_Stream->Stream_Num] 	= DMA_Stream->DMA_HIF_Notify_ptr;
					DMA2_TC_Notify_arr[DMA_Stream->Stream_Num] 		= DMA_Stream->DMA_TC_Notify_ptr;
					DMA2_Stream_Status_arr[DMA_Stream->Stream_Num] 	= Buzzy;

					DMA2_REG->stream[DMA_Stream->Stream_Num].DMA_CR 	= Register_buffer; 		// control register
					DMA2_REG->stream[DMA_Stream->Stream_Num].DMA_NDTR	= DMA_Stream->Count; 	// number of data
					DMA2_REG->stream[DMA_Stream->Stream_Num].DMA_PAR	= (u32)DMA_Stream->Pri_Add; 	// peripheral address
					DMA2_REG->stream[DMA_Stream->Stream_Num].DMA_M0AR	= (u32)DMA_Stream->Mem_Add; 	// memory address
					}
					break;

				case Circular_Buffer:
					if(DMA_Stream_Status_arr[DMA_Stream->Stream_Num] == Ready){

					Register_buffer |= (DMA_Stream->Channel_Num <<25);
					Register_buffer |= (DMA_Stream->Size <<13); // memory size
					Register_buffer |= (DMA_Stream->Size <<11); // peripheral size
					Register_buffer |= (DMA_Stream->Memory_Increament_Mode <<10);
					Register_buffer |= (DMA_Stream->Pripheral_Increament_Mode <<9);
					Register_buffer |= (DMA_Stream->DMA_Dir_Mode <<6);

					Register_buffer |= (1<<8); //circular mode on
					Register_buffer |= (1<<4); //TC interrupt enable
					Register_buffer |= (1<<3); //HIF interrupt enable

					DMA2_HIF_Notify_arr[DMA_Stream->Stream_Num] 	= DMA_Stream->DMA_HIF_Notify_ptr;
					DMA2_TC_Notify_arr[DMA_Stream->Stream_Num] 		= DMA_Stream->DMA_TC_Notify_ptr;
					DMA2_Stream_Status_arr[DMA_Stream->Stream_Num] 	= Buzzy;

					DMA2_REG->stream[DMA_Stream->Stream_Num].DMA_CR 	= Register_buffer; 		// control register
					DMA2_REG->stream[DMA_Stream->Stream_Num].DMA_NDTR	= DMA_Stream->Count; 	// number of data
					DMA2_REG->stream[DMA_Stream->Stream_Num].DMA_PAR	= (u32)DMA_Stream->Pri_Add; 	// peripheral address
					DMA2_REG->stream[DMA_Stream->Stream_Num].DMA_M0AR	= (u32)DMA_Stream->Mem_Add; 	// memory address
					}
					break;

				case Double_Buffer:
					if(DMA_Stream_Status_arr[DMA_Stream->Stream_Num] == Ready){

					Register_buffer |= (DMA_Stream->Channel_Num <<25);
					Register_buffer |= (DMA_Stream->Size <<13); // memory size
					Register_buffer |= (DMA_Stream->Size <<11); // peripheral size
					Register_buffer |= (DMA_Stream->Memory_Increament_Mode <<10);
					Register_buffer |= (DMA_Stream->Pripheral_Increament_Mode <<9);
					Register_buffer |= (DMA_Stream->DMA_Dir_Mode <<6);

					Register_buffer |= (1<<18); //double buffer mode on
					Register_buffer |= (1<<4); //TC interrupt enable
					Register_buffer |= (1<<3); //HIF interrupt enable

					DMA2_HIF_Notify_arr[DMA_Stream->Stream_Num] 	= DMA_Stream->DMA_HIF_Notify_ptr;
					DMA2_TC_Notify_arr[DMA_Stream->Stream_Num] 		= DMA_Stream->DMA_TC_Notify_ptr;
					DMA2_Stream_Status_arr[DMA_Stream->Stream_Num] 	= Buzzy;

					DMA2_REG->stream[DMA_Stream->Stream_Num].DMA_CR 	= Register_buffer; 		// control register
					DMA2_REG->stream[DMA_Stream->Stream_Num].DMA_NDTR	= DMA_Stream->Count; 	// number of data
					DMA2_REG->stream[DMA_Stream->Stream_Num].DMA_PAR	= (u32)DMA_Stream->Pri_Add; 	// peripheral address
					DMA2_REG->stream[DMA_Stream->Stream_Num].DMA_M0AR	= (u32)DMA_Stream->Mem_Add; 	// memory address1
					if(DMA_Stream->Mem2_Add != Null_Ptr)
						DMA2_REG->stream[DMA_Stream->Stream_Num].DMA_M1AR	= (u32)DMA_Stream->Mem2_Add; 	// memory2 address2 //aftaker de
					}
					break;
			}
			break;

	}
}


void DMA_Start_Stream(DMA_Stream_t* DMA_Stream)
{
	switch(DMA_Stream->DMA_Num)
	{
	case DMA1:
		DMA1_REG->stream[DMA_Stream->Stream_Num].DMA_CR    |= 1; 					// Enable stream
		break;
	case DMA2:
		DMA2_REG->stream[DMA_Stream->Stream_Num].DMA_CR    |= 1; 					// Enable stream
		break;
	}
}
void DMA_Stop_Stream(DMA_Stream_t* DMA_Stream)
{
	switch(DMA_Stream->DMA_Num)
	{
	case DMA1:
		DMA1_REG->stream[DMA_Stream->Stream_Num].DMA_CR    &=~ 1; 					// Disable stream
		break;
	case DMA2:
		DMA2_REG->stream[DMA_Stream->Stream_Num].DMA_CR    &=~ 1; 					// Disable stream
		break;
	}
}


DMA_Status DMA_GetStatus(DMA_Stream_t* DMA_Stream)
{
	DMA_Status status = Ready;
	switch(DMA_Stream->DMA_Num)
	{
	case DMA1:
		status = DMA_Stream_Status_arr[DMA_Stream->Stream_Num];
		break;
	case DMA2:
		status = DMA2_Stream_Status_arr[DMA_Stream->Stream_Num];
		break;
	}
	return status;
}



void DMA1_Stream0_IRQHandler(void)
{
	if ( (DMA1_REG->DMA_LISR >>4) & 1) //half complete stream 0
	{
		if(DMA_HIF_Notify_arr[Stream0] != Null_Ptr)
		{
			DMA_HIF_Notify_arr[Stream0]();
			DMA_Stream_Status_arr[Stream0] = Half_Complete;

		}
		DMA1_REG->DMA_LIFCR |= (1<<4);	//clear flag
	}

	if ( (DMA1_REG->DMA_LISR >>5) & 1) //complete stream 0
	{
		if(DMA_TC_Notify_arr[Stream0] != Null_Ptr)
		{
			DMA_TC_Notify_arr[Stream0]();
			DMA_Stream_Status_arr[Stream0] = Ready;

		}
		DMA1_REG->DMA_LIFCR |= (1<<5);	//clear flag
	}
}

void DMA1_Stream1_IRQHandler(void)
{
	if ( (DMA1_REG->DMA_LISR >>10) & 1) //half complete stream 1
	{
		if(DMA_HIF_Notify_arr[Stream1] != Null_Ptr)
		{
			DMA_HIF_Notify_arr[Stream1]();
			DMA_Stream_Status_arr[Stream1] = Half_Complete;

		}
		DMA1_REG->DMA_LIFCR |= (1<<10);	//clear flag
	}

	if ( (DMA1_REG->DMA_LISR >>11) & 1) //complete stream 1
	{
		if(DMA_TC_Notify_arr[Stream1] != Null_Ptr)
		{
			DMA_TC_Notify_arr[Stream1]();
			DMA_Stream_Status_arr[Stream1] = Ready;

		}
		DMA1_REG->DMA_LIFCR |= (1<<11);	//clear flag
	}
}

void DMA1_Stream2_IRQHandler(void)
{
	if ( (DMA1_REG->DMA_LISR >>20) & 1) //half complete stream 2
	{
		if(DMA_HIF_Notify_arr[Stream2] != Null_Ptr)
		{
			DMA_HIF_Notify_arr[Stream2]();
			DMA_Stream_Status_arr[Stream2] = Half_Complete;

		}
		DMA1_REG->DMA_LIFCR |= (1<<20);	//clear flag
	}

	if ( (DMA1_REG->DMA_LISR >>21) & 1) //complete stream 2
	{
		if(DMA_TC_Notify_arr[Stream2] != Null_Ptr)
		{
			DMA_TC_Notify_arr[Stream2]();
			DMA_Stream_Status_arr[Stream2] = Ready;

		}
		DMA1_REG->DMA_LIFCR |= (1<<21);	//clear flag
	}
}

void DMA1_Stream3_IRQHandler(void)
{
	if ( (DMA1_REG->DMA_LISR >>26) & 1) //half complete stream 3
	{
		if(DMA_HIF_Notify_arr[Stream3] != Null_Ptr)
		{
			DMA_HIF_Notify_arr[Stream3]();
			DMA_Stream_Status_arr[Stream3] = Half_Complete;

		}
		DMA1_REG->DMA_LIFCR |= (1<<26);	//clear flag
	}

	if ( (DMA1_REG->DMA_LISR >>27) & 1) //complete stream 3
	{
		if(DMA_TC_Notify_arr[Stream3] != Null_Ptr)
		{
			DMA_TC_Notify_arr[Stream3]();
			DMA_Stream_Status_arr[Stream3] = Ready;

		}
		DMA1_REG->DMA_LIFCR |= (1<<27);	//clear flag
	}
}

void DMA1_Stream4_IRQHandler(void)
{
	if ( (DMA1_REG->DMA_HISR >>4) & 1) //half complete stream 4
	{
		if(DMA_HIF_Notify_arr[Stream4] != Null_Ptr)
		{
			DMA_HIF_Notify_arr[Stream4]();
			DMA_Stream_Status_arr[Stream4] = Half_Complete;

		}
		DMA1_REG->DMA_HIFCR |= (1<<4);	//clear flag
	}

	if ( (DMA1_REG->DMA_HISR >>5) & 1) //complete stream 4
	{
		if(DMA_TC_Notify_arr[Stream4] != Null_Ptr)
		{
			DMA_TC_Notify_arr[Stream4]();
			DMA_Stream_Status_arr[Stream4] = Ready;

		}
		DMA1_REG->DMA_HIFCR |= (1<<5);	//clear flag
	}
}

void DMA1_Stream5_IRQHandler(void)
{
	if ( (DMA1_REG->DMA_HISR >>10) & 1) //half complete stream 5
	{
		if(DMA_HIF_Notify_arr[Stream5] != Null_Ptr)
		{
			DMA_HIF_Notify_arr[Stream5]();
			DMA_Stream_Status_arr[Stream5] = Half_Complete;

		}
		DMA1_REG->DMA_HIFCR |= (1<<10);	//clear flag
	}

	if ( (DMA1_REG->DMA_HISR >>11) & 1) //complete stream 5
	{
		if(DMA_TC_Notify_arr[Stream5] != Null_Ptr)
		{
			DMA_TC_Notify_arr[Stream5]();
			DMA_Stream_Status_arr[Stream5] = Ready;

		}
		DMA1_REG->DMA_HIFCR |= (1<<11);	//clear flag
	}
}

void DMA1_Stream6_IRQHandler(void)
{
	if ( (DMA1_REG->DMA_HISR >>20) & 1) //half complete stream 6
	{
		if(DMA_HIF_Notify_arr[Stream6] != Null_Ptr)
		{
			DMA_HIF_Notify_arr[Stream6]();
			DMA_Stream_Status_arr[Stream6] = Half_Complete;

		}
		DMA1_REG->DMA_HIFCR |= (1<<20);	//clear flag
	}

	if ( (DMA1_REG->DMA_HISR >>21) & 1) //complete stream 6
	{
		if(DMA_TC_Notify_arr[Stream6] != Null_Ptr)
		{
			DMA_TC_Notify_arr[Stream6]();
			DMA_Stream_Status_arr[Stream6] = Ready;

		}
		DMA1_REG->DMA_HIFCR |= (1<<21);	//clear flag
	}
}

void DMA1_Stream7_IRQHandler(void)
{
	if ( (DMA1_REG->DMA_HISR >>26) & 1) //half complete stream 7
	{
		if(DMA_HIF_Notify_arr[Stream7] != Null_Ptr)
		{
			DMA_HIF_Notify_arr[Stream7]();
			DMA_Stream_Status_arr[Stream7] = Half_Complete;

		}
		DMA1_REG->DMA_HIFCR |= (1<<26);	//clear flag
	}

	if ( (DMA1_REG->DMA_HISR >>27) & 1) //complete stream 7
	{
		if(DMA_TC_Notify_arr[Stream7] != Null_Ptr)
		{
			DMA_TC_Notify_arr[Stream7]();
			DMA_Stream_Status_arr[Stream7] = Ready;

		}
		DMA1_REG->DMA_HIFCR |= (1<<27);	//clear flag
	}
}


void DMA2_Stream0_IRQHandler(void)
{
	if ( (DMA2_REG->DMA_LISR >>4) & 1) //half complete stream 0
	{
		if(DMA2_HIF_Notify_arr[Stream0] != Null_Ptr)
		{
			DMA2_HIF_Notify_arr[Stream0]();
			DMA2_Stream_Status_arr[Stream0] = Half_Complete;

		}
		DMA2_REG->DMA_LIFCR |= (1<<4);	//clear flag
	}

	if ( (DMA2_REG->DMA_LISR >>5) & 1) //complete stream 0
	{
		if(DMA2_TC_Notify_arr[Stream0] != Null_Ptr)
		{
			DMA2_TC_Notify_arr[Stream0]();
			DMA2_Stream_Status_arr[Stream0] = Ready;

		}
		DMA2_REG->DMA_LIFCR |= (1<<5);	//clear flag
	}
}

void DMA2_Stream1_IRQHandler(void)
{
	if ( (DMA2_REG->DMA_LISR >>10) & 1) //half complete stream 1
	{
		if(DMA2_HIF_Notify_arr[Stream1] != Null_Ptr)
		{
			DMA2_HIF_Notify_arr[Stream1]();
			DMA2_Stream_Status_arr[Stream1] = Half_Complete;

		}
		DMA2_REG->DMA_LIFCR |= (1<<10);	//clear flag
	}

	if ( (DMA2_REG->DMA_LISR >>11) & 1) //complete stream 1
	{
		if(DMA2_TC_Notify_arr[Stream1] != Null_Ptr)
		{
			DMA2_TC_Notify_arr[Stream1]();
			DMA2_Stream_Status_arr[Stream1] = Ready;

		}
		DMA2_REG->DMA_LIFCR |= (1<<11);	//clear flag
	}
}

void DMA2_Stream2_IRQHandler(void)
{
	if ( (DMA2_REG->DMA_LISR >>20) & 1) //half complete stream 2
	{
		if(DMA2_HIF_Notify_arr[Stream2] != Null_Ptr)
		{
			DMA2_HIF_Notify_arr[Stream2]();
			DMA2_Stream_Status_arr[Stream2] = Half_Complete;

		}
		DMA2_REG->DMA_LIFCR |= (1<<20);	//clear flag
	}

	if ( (DMA2_REG->DMA_LISR >>21) & 1) //complete stream 2
	{
		if(DMA2_TC_Notify_arr[Stream2] != Null_Ptr)
		{
			DMA2_TC_Notify_arr[Stream2]();
			DMA2_Stream_Status_arr[Stream2] = Ready;

		}
		DMA2_REG->DMA_LIFCR |= (1<<21);	//clear flag
	}
}

void DMA2_Stream3_IRQHandler(void)
{
	if ( (DMA2_REG->DMA_LISR >>26) & 1) //half complete stream 3
	{
		if(DMA2_HIF_Notify_arr[Stream3] != Null_Ptr)
		{
			DMA2_HIF_Notify_arr[Stream3]();
			DMA2_Stream_Status_arr[Stream3] = Half_Complete;

		}
		DMA2_REG->DMA_LIFCR |= (1<<26);	//clear flag
	}

	if ( (DMA2_REG->DMA_LISR >>27) & 1) //complete stream 3
	{
		if(DMA2_TC_Notify_arr[Stream3] != Null_Ptr)
		{
			DMA2_TC_Notify_arr[Stream3]();
			DMA2_Stream_Status_arr[Stream3] = Ready;

		}
		DMA2_REG->DMA_LIFCR |= (1<<27);	//clear flag
	}
}

void DMA2_Stream4_IRQHandler(void)
{
	if ( (DMA2_REG->DMA_HISR >>4) & 1) //half complete stream 4
	{
		if(DMA2_HIF_Notify_arr[Stream4] != Null_Ptr)
		{
			DMA2_HIF_Notify_arr[Stream4]();
			DMA2_Stream_Status_arr[Stream4] = Half_Complete;

		}
		DMA2_REG->DMA_HIFCR |= (1<<4);	//clear flag
	}

	if ( (DMA2_REG->DMA_HISR >>5) & 1) //complete stream 4
	{
		if(DMA2_TC_Notify_arr[Stream4] != Null_Ptr)
		{
			DMA2_TC_Notify_arr[Stream4]();
			DMA2_Stream_Status_arr[Stream4] = Ready;

		}
		DMA2_REG->DMA_HIFCR |= (1<<5);	//clear flag
	}
}

void DMA2_Stream5_IRQHandler(void)
{
	if ( (DMA2_REG->DMA_HISR >>10) & 1) //half complete stream 5
	{
		if(DMA2_HIF_Notify_arr[Stream5] != Null_Ptr)
		{
			DMA2_HIF_Notify_arr[Stream5]();
			DMA2_Stream_Status_arr[Stream5] = Half_Complete;

		}
		DMA2_REG->DMA_HIFCR |= (1<<10);	//clear flag
	}

	if ( (DMA2_REG->DMA_HISR >>11) & 1) //complete stream 5
	{
		if(DMA2_TC_Notify_arr[Stream5] != Null_Ptr)
		{
			DMA2_TC_Notify_arr[Stream5]();
			DMA2_Stream_Status_arr[Stream5] = Ready;

		}
		DMA2_REG->DMA_HIFCR |= (1<<11);	//clear flag
	}
}

void DMA2_Stream6_IRQHandler(void)
{
	if ( (DMA2_REG->DMA_HISR >>20) & 1) //half complete stream 6
	{
		if(DMA2_HIF_Notify_arr[Stream6] != Null_Ptr)
		{
			DMA2_HIF_Notify_arr[Stream6]();
			DMA2_Stream_Status_arr[Stream6] = Half_Complete;

		}
		DMA2_REG->DMA_HIFCR |= (1<<20);	//clear flag
	}

	if ( (DMA2_REG->DMA_HISR >>21) & 1) //complete stream 6
	{
		if(DMA2_TC_Notify_arr[Stream6] != Null_Ptr)
		{
			DMA2_TC_Notify_arr[Stream6]();
			DMA2_Stream_Status_arr[Stream6] = Ready;

		}
		DMA2_REG->DMA_HIFCR |= (1<<21);	//clear flag
	}
}

void DMA2_Stream7_IRQHandler(void)
{
	if ( (DMA2_REG->DMA_HISR >>26) & 1) //half complete stream 7
	{
		if(DMA2_HIF_Notify_arr[Stream7] != Null_Ptr)
		{
			DMA2_HIF_Notify_arr[Stream7]();
			DMA2_Stream_Status_arr[Stream7] = Half_Complete;

		}
		DMA2_REG->DMA_HIFCR |= (1<<26);	//clear flag
	}

	if ( (DMA2_REG->DMA_HISR >>27) & 1) //complete stream 7
	{
		if(DMA2_TC_Notify_arr[Stream7] != Null_Ptr)
		{
			DMA2_TC_Notify_arr[Stream7]();
			DMA2_Stream_Status_arr[Stream7] = Ready;

		}
		DMA2_REG->DMA_HIFCR |= (1<<27);	//clear flag
	}
}
