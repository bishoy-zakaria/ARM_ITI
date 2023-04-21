#ifndef SCHEDULER_CFG_H
#define SCHEDULER_CFG_H

#include"Std_Types.h"

#define System_Tick_ms	1
#define Tasks_Number	1

typedef void(*runnablecbf_t)(void);
typedef struct
{
	char* 			Name;
	runnablecbf_t 	cbf;
	u32				Period_ms;
	u32				StartDelay_ms;
}runnable_t;


#endif
