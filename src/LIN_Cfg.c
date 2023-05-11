#include "LIN_Cfg.h"


u8 Frame_Index	= 0;

LIN_Scheduler_Table_t	LIN_Scheduler_Table[Frame_Num] = {
													[0] = 	{
																.Frame_ID		= 0x10,
																.Slot_Time		= 10
															},

													[1] = 	{
																.Frame_ID		= 0x20,
																.Slot_Time		= 10
															},

													[2] = 	{
																.Frame_ID		= 0x30,
																.Slot_Time		= 10
															}
												};
