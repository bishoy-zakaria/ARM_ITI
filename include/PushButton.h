
#ifndef PushButton_H
#define PushButton_H

#include "GPIO.h"
#include "PushButton_cfg.h"

#define PushButton_PU		0 		/******  pull up res option   ******/
#define PushButton_PD		1 		/******  pull down res option ******/

#define PushButton_NotPressed	0
#define PushButton_Pressed		1

typedef struct
{
	void* 	port;
	u32 	pin;
	u32 	PinMode;
	u32		speed;
	u32		ButtonMode;
	u8 		name [20];
}PushButton_strCFG_t;


typedef enum
{
	PushButton_enuOK=0,
	PushButton_enuNotOK,
	PushButton_enuNullPtr
}PushButton_Error_t;


void PushButton_init(void);

PushButton_Error_t PushButton_WriteValue(PushButton_enuCfg_t LED_enuNum , u8* buffer_add);



#endif
