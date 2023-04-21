
#ifndef LED_H
#define LED_H

#include "GPIO.h"
#include "LED_cfg.h"

#define LED_ActiveLow  		0
#define LED_ActiveHigh 		1


typedef struct
{
	void* 	port;
	u32 	pin;
	u32 	PinMode;
	u32		speed;
	u32		LedMode;
	u8 		name [20];
	u8		color[10];
}LED_strCFG_t;


typedef enum
{
	LED_enuLow=0,
	LED_enuHigh
}LED_enuValue_t;

typedef enum
{
	LED_enuOK=0,
	LED_enuNotOK,
	LED_enuNullPtr
}LED_Error_t;


void LED_init(void);


LED_Error_t LED_WriteValue(LED_enuCfg_t LED_enuNum , LED_enuValue_t LED_enuValue);


#endif
