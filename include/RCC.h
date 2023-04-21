

#ifndef RCC_H
#define RCC_H

#include "Bit_Math.h"
#include "Std_Types.h"

#define RCC_HSI  0
#define RCC_HSE  1
#define RCC_PLL  2


#define	RCC_enuAHB_NotDiv     	0b0000
#define	RCC_enuAHB_Div2       	0b1000
#define	RCC_enuAHB_Div4			0b1001
#define	RCC_enuAHB_Div8			0b1010
#define	RCC_enuAHB_Div16		0b1011
#define	RCC_enuAHB_Div46		0b1100
#define	RCC_enuAHB_Div128		0b1101
#define	RCC_enuAHB_Div256		0b1110
#define	RCC_enuAHB_Div512		0b1111


#define	RCC_enuAPB1_NotDiv		0b000
#define	RCC_enuAPB1_Div2 		0b100
#define	RCC_enuAPB1_Div4		0b101
#define	RCC_enuAPB1_Div8		0b110
#define	RCC_enuAPB1_Div16		0b111


#define	RCC_enuAPB2_NotDiv 		0b000
#define	RCC_enuAPB2_Div2   		0b100
#define	RCC_enuAPB2_Div4		0b101
#define	RCC_enuAPB2_Div8		0b110
#define	RCC_enuAPB2_Div16		0b111


typedef enum
{
	RCC_enuHSI=0,
	RCC_enuHSE,
	RCC_enuPLL
}RCC_enuSystemClock_t;



typedef enum
{
/********* AHB1 ************/
	RCC_GPIOA			=0,
	RCC_GPIOB				,
	RCC_GPIOC				,
	RCC_GPIOD				,
	RCC_GPIOE				,
	RCC_GPIOH			=7,
	RCC_CRC			 =12,
	RCC_DMA1		 =21,
	RCC_DMA2		 =22,
/********* AHB2 ************/
	RCC_OTGFS		 =29,
/********* APB1 ************/
	RCC_TIM2		 =30,
	RCC_TIM3				,
	RCC_TIM4				,
	RCC_TIM5				,
	RCC_WWDG		 =41,
	RCC_SPI2		 =44,
	RCC_SPI3			  ,
	RCC_USART2	 =47,
	RCC_I2C1		 =51,
	RCC_I2C2				,
	RCC_I2C3				,
	RCC_PWR			 =58,
/********* APB2 ************/
	RCC_TIM1		 =60,
	RCC_USART1	 =64,
	RCC_USART6			,
	RCC_ADC1		=68	,
	RCC_SDIO		=71	,
	RCC_SPI1				,
	RCC_SPI4				,
	RCC_STSCFG			,
	RCC_TIM9		=76 ,
	RCC_TIM10	  	  ,
	RCC_TIM11
	
}RCC_enuPri_t;


typedef enum
{
	RCC_enuPreAHB=0,
	RCC_enuPreAPB1,
	RCC_enuPreAPB2
}RCC_enuPrescaler_t;



typedef struct
{
	RCC_enuPrescaler_t Bus;
	u8 Division;
	
}RCC_strPrescConfig;


typedef enum
{
	RCC_enuHSINotReady=0,
	RCC_enuHSIReady
}RCC_enuStateHSI_t;

typedef enum
{
	RCC_enuHSENotReady=0,
	RCC_enuHSEReady
}RCC_enuStateHSE_t;

typedef enum
{
	RCC_enuPLLNotLocked=0,
	RCC_enuPLLLocked
}RCC_enuStatePLL_t;

typedef enum
{
	RCC_enuPLLM_Div2=2,
	RCC_enuPLLM_Div3,
	RCC_enuPLLM_Div4,
	RCC_enuPLLM_Div5,
	RCC_enuPLLM_Div6,
	RCC_enuPLLM_Div7,
	RCC_enuPLLM_Div8,
	RCC_enuPLLM_Div9,
	RCC_enuPLLM_Div10,
	RCC_enuPLLM_Div11,
	RCC_enuPLLM_Div12,
	RCC_enuPLLM_Div13,
	RCC_enuPLLM_Div14,
	RCC_enuPLLM_Div15,
	RCC_enuPLLM_Div16,
	RCC_enuPLLM_Div17,
	RCC_enuPLLM_Div18,
	RCC_enuPLLM_Div19,
	RCC_enuPLLM_Div20,
	RCC_enuPLLM_Div21,
	RCC_enuPLLM_Div22,
	RCC_enuPLLM_Div23,
	RCC_enuPLLM_Div24,
	RCC_enuPLLM_Div25,
	RCC_enuPLLM_Div26,
	RCC_enuPLLM_Div27,
	RCC_enuPLLM_Div28,
	RCC_enuPLLM_Div29,
	RCC_enuPLLM_Div30,
	RCC_enuPLLM_Div31,
	RCC_enuPLLM_Div32,
	RCC_enuPLLM_Div33,
	RCC_enuPLLM_Div34,
	RCC_enuPLLM_Div35,
	RCC_enuPLLM_Div36,
	RCC_enuPLLM_Div37,
	RCC_enuPLLM_Div38,
	RCC_enuPLLM_Div39,
	RCC_enuPLLM_Div40,
	RCC_enuPLLM_Div41,
	RCC_enuPLLM_Div42,
	RCC_enuPLLM_Div43,
	RCC_enuPLLM_Div44,
	RCC_enuPLLM_Div45,
	RCC_enuPLLM_Div46,
	RCC_enuPLLM_Div47,
	RCC_enuPLLM_Div48,
	RCC_enuPLLM_Div49,
	RCC_enuPLLM_Div50,
	RCC_enuPLLM_Div51,
	RCC_enuPLLM_Div52,
	RCC_enuPLLM_Div53,
	RCC_enuPLLM_Div54,
	RCC_enuPLLM_Div55,
	RCC_enuPLLM_Div56,
	RCC_enuPLLM_Div57,
	RCC_enuPLLM_Div58,
	RCC_enuPLLM_Div59,
	RCC_enuPLLM_Div60,
	RCC_enuPLLM_Div61,
	RCC_enuPLLM_Div62,
	RCC_enuPLLM_Div63
}RCC_enuPLLM_t;


typedef enum
{
	RCC_enuPLLN_MUL192=192,
	RCC_enuPLLN_MUL193,
	RCC_enuPLLN_MUL194,
	RCC_enuPLLN_MUL195,
	RCC_enuPLLN_MUL196,
	RCC_enuPLLN_MUL197,
	RCC_enuPLLN_MUL198,
	RCC_enuPLLN_MUL199,
	RCC_enuPLLN_MUL200,
	RCC_enuPLLN_MUL201,
	RCC_enuPLLN_MUL202,
	RCC_enuPLLN_MUL203,
	RCC_enuPLLN_MUL204,
	RCC_enuPLLN_MUL205,
	RCC_enuPLLN_MUL206,
	RCC_enuPLLN_MUL207,
	RCC_enuPLLN_MUL208,
	RCC_enuPLLN_MUL209,
	RCC_enuPLLN_MUL210,
	RCC_enuPLLN_MUL211,
	RCC_enuPLLN_MUL212,
	RCC_enuPLLN_MUL213,
	RCC_enuPLLN_MUL214,
	RCC_enuPLLN_MUL215,
	RCC_enuPLLN_MUL216,
	RCC_enuPLLN_MUL217,
	RCC_enuPLLN_MUL218,
	RCC_enuPLLN_MUL219,
	RCC_enuPLLN_MUL220,
	RCC_enuPLLN_MUL221,
	RCC_enuPLLN_MUL222,
	RCC_enuPLLN_MUL223,
	RCC_enuPLLN_MUL224,
	RCC_enuPLLN_MUL225,
	RCC_enuPLLN_MUL226,
	RCC_enuPLLN_MUL227,
	RCC_enuPLLN_MUL228,
	RCC_enuPLLN_MUL229,
	RCC_enuPLLN_MUL230,
	RCC_enuPLLN_MUL231,
	RCC_enuPLLN_MUL232,
	RCC_enuPLLN_MUL233,
	RCC_enuPLLN_MUL234,
	RCC_enuPLLN_MUL235,
	RCC_enuPLLN_MUL236,
	RCC_enuPLLN_MUL237,
	RCC_enuPLLN_MUL238,
	RCC_enuPLLN_MUL239,
	RCC_enuPLLN_MUL240,
	RCC_enuPLLN_MUL241,
	RCC_enuPLLN_MUL242,
	RCC_enuPLLN_MUL243,
	RCC_enuPLLN_MUL244,
	RCC_enuPLLN_MUL245,
	RCC_enuPLLN_MUL246,
	RCC_enuPLLN_MUL247,
	RCC_enuPLLN_MUL248,
	RCC_enuPLLN_MUL249,
	RCC_enuPLLN_MUL250,
	RCC_enuPLLN_MUL251,
	RCC_enuPLLN_MUL252,
	RCC_enuPLLN_MUL253
}RCC_enuPLLN_t;

typedef enum
{
	RCC_enuPLLP_Div2=0,
	RCC_enuPLLP_Div4,
	RCC_enuPLLP_Div6,
	RCC_enuPLLP_Div8
}RCC_enuPLLP_t;


typedef enum
{
	RCC_enuPLLQ_Div2=2,
	RCC_enuPLLQ_Div3,
	RCC_enuPLLQ_Div4,
	RCC_enuPLLQ_Div5,
	RCC_enuPLLQ_Div6,
	RCC_enuPLLQ_Div7,
	RCC_enuPLLQ_Div8,
	RCC_enuPLLQ_Div9,
	RCC_enuPLLQ_Div10,
	RCC_enuPLLQ_Div11,
	RCC_enuPLLQ_Div12,
	RCC_enuPLLQ_Div13,
	RCC_enuPLLQ_Div14,
	RCC_enuPLLQ_Div15
}RCC_enuPLLQ_t;


typedef enum
{
		RCC_enuOk=0,
		RCC_enuNotOk,
		RCC_enuNullPtr
}RCC_tenuErrorStatus;

RCC_tenuErrorStatus RCC_enuSystemClockInit(void);
RCC_tenuErrorStatus RCC_enuSystemClockSwitch(RCC_enuSystemClock_t cpy_source);
RCC_tenuErrorStatus RCC_enuEnableSource(RCC_enuSystemClock_t cpy_source);
RCC_tenuErrorStatus RCC_enuDisableSource(RCC_enuSystemClock_t cpy_source);
RCC_tenuErrorStatus RCC_enuConfigPLL(RCC_enuSystemClock_t cpy_source , RCC_enuPLLM_t cpy_M , RCC_enuPLLN_t cpy_N , RCC_enuPLLP_t cpy_P , RCC_enuPLLQ_t cpy_Q );
RCC_tenuErrorStatus RCC_enuPLLSystemClockSwitch(RCC_enuSystemClock_t cpy_source , RCC_enuPLLM_t cpy_M , RCC_enuPLLN_t cpy_N , RCC_enuPLLP_t cpy_P , RCC_enuPLLQ_t cpy_Q );
RCC_tenuErrorStatus RCC_enuPriEnable(RCC_enuPri_t cpy_pri);
RCC_tenuErrorStatus RCC_enuPriDisable(RCC_enuPri_t cpy_pri);
RCC_tenuErrorStatus RCC_enuCheckClockStatus(RCC_enuSystemClock_t cpy_source ,  u8* add_status);
RCC_tenuErrorStatus RCC_enuGetSystemClock(RCC_enuSystemClock_t* add_source);
RCC_tenuErrorStatus RCC_enuConfigurePres(RCC_enuPrescaler_t cpy_pre ,  u8 val);

#endif
