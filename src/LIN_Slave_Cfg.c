#include "LIN_Slave_Cfg.h"


extern u8 Speed;


LIN_Frame_t		LIN_Slave_Frames[] = {
									[0] = 	{
												.ID 			= 0x10,
												.Signals		= &Speed,
												.Byte_Num		= 1

											}

								};

LIN_Slave_Frame_t	LIN_Slave_Frame[Frame_Number] = {
											[0] = 	{
														.LIN_Frame 			= &LIN_Slave_Frames[0],
														.LIN_Slave_Response	= LIN_Slave_TX
													}

										};
