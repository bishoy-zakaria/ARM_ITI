#include "Sched_Cfg.h"

extern void LCD_Task(void);
runnable_t Runnable_Array[Tasks_Number] =
{
		[0] =
		{
			.Name 			= "LCD Task",
			.cbf  			=  LCD_Task,
			.Period_ms		= 2,
			.StartDelay_ms	= 0
		}
};
