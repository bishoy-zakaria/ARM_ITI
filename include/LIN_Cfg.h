#ifndef LIN_CFG_H
#define LIN_CFG_H

#include "Std_Types.h"

#define Frame_Num 3

typedef struct
{
	u8 Frame_ID;
	u8 Slot_Time; 			//millisecond
}LIN_Scheduler_Table_t;

#endif
