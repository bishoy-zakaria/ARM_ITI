#include "Scheduler.h"
#include "Sched_Cfg.h"
#include "SYS_Tick.h"

typedef struct
{
	const runnable_t* task_ptr;
	u32 reminder;
}runnablelist_t;


extern runnable_t Runnable_Array[Tasks_Number];
runnablelist_t Task_List[Tasks_Number];
u8 Sytick_Flage=0;


static void Sched_Handeler(void);

void Sched_Init(void)
{
	u8 iterrator=0;
	SysTick_SelectClkSource(SysTick_enuAHB_CLK);
	SysTick_EnableExeption();
	SysTick_SetPeriodms(System_Tick_ms);
	SysTick_SetCallBack(Sched_Handeler);

	for(iterrator=0 ; iterrator<Tasks_Number ; iterrator++)
	{
		Task_List[iterrator].task_ptr  = &Runnable_Array[iterrator];
		Task_List[iterrator].reminder	= Runnable_Array[iterrator].StartDelay_ms;
	}
}

void Sched_Start(void)
{
	SysTick_Start();

	while(1)
	{
		if(Sytick_Flage == 1)
		{
			Scheduler();
			Sytick_Flage=0;
		}
	}
}

void Scheduler(void)
{
	u8 iterrator=0;
	for(iterrator=0 ; iterrator<Tasks_Number ; iterrator++)
	{
		if(Task_List[iterrator].reminder == 0)
		{
			Task_List[iterrator].task_ptr->cbf();
			Task_List[iterrator].reminder = Task_List[iterrator].task_ptr->Period_ms;
		}
		Task_List[iterrator].reminder -= System_Tick_ms;
	}
}

static void Sched_Handeler(void)
{
	if(Sytick_Flage == 0)
	{
		Sytick_Flage=1;
	}
	else //task missed period time
	{

	}
}
