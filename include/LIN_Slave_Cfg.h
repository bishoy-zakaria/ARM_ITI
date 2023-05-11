#ifndef LIN_SLAVE_CFG
#define LIN_SLAVE_CFG

#include "Std_Types.h"

#define Frame_Number	1


typedef enum
{
	LIN_Slave_TX=0,
	LIN_Slave_RX
}LIN_Slave_Response_t;


typedef struct
{
	u8 ID;
	u8 Byte_Num;
	u8* Signals;
}LIN_Frame_t;


typedef struct
{
	LIN_Frame_t* LIN_Frame;
	LIN_Slave_Response_t LIN_Slave_Response;
}LIN_Slave_Frame_t;

#endif
