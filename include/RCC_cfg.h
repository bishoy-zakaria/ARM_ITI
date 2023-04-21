
#ifndef RCC_H_CFG
#define RCC_H_CFG

#define RCC_PripheralNumber    10        //number of pripherals you want to enable

#define RCC_SystemClock     RCC_HSI     //configuration of the initial system clock source

#define RCC_PLL_Source      RCC_HSE
#define RCC_PLL_M           RCC_enuPLLM_Div10
#define RCC_PLL_N           RCC_enuPLLN_MUL250
#define RCC_PLL_P			RCC_enuPLLP_Div8
#define RCC_PLL_Q			RCC_enuPLLQ_Div2

RCC_strPrescConfig RCC_strBusClockCfgArray[3] = {     /*BUS*/         /*Division*/
																									{RCC_enuPreAHB  , RCC_enuAHB_NotDiv },
																									{RCC_enuPreAPB1 , RCC_enuAPB1_NotDiv},
																									{RCC_enuPreAPB2 , RCC_enuAPB2_NotDiv}
																								};


RCC_enuPri_t RCC_enuPriEnableArray[RCC_PripheralNumber] ={
																											RCC_GPIOA,
																											RCC_GPIOB,
																											RCC_GPIOC,
																											RCC_GPIOD,
																											RCC_DMA1 ,
																											RCC_DMA2,
																											RCC_WWDG	,
																											RCC_SPI2	,
																											RCC_SPI3	,
																											RCC_USART1
	
																										};
#endif
