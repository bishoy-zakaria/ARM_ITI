
#include "RCC.h"
#include "RCC_cfg.h"
#include "RCC_priv.h"

RCC_tenuErrorStatus RCC_enuSystemClockInit(void)
{
	RCC_enuSystemClock_t local_CurrentSource;
	u8 local_iterator=0;
	RCC_tenuErrorStatus  local_status = RCC_enuOk;

	local_status = RCC_enuGetSystemClock( &local_CurrentSource );		//get the current source
	local_status = RCC_enuEnableSource(RCC_SystemClock);            //enable RCC_SystemClock


	for(local_iterator=0 ; local_iterator<3 ; local_iterator++)    //configure the clock of buses AHB,APB1 and APB2
		{
			local_status = RCC_enuConfigurePres(RCC_strBusClockCfgArray[local_iterator].Bus , RCC_strBusClockCfgArray[local_iterator].Division);
		}

	for(local_iterator=0 ; local_iterator<RCC_PripheralNumber ; local_iterator++)    //configure the clock of buses AHB,APB1 and APB2
		{
			local_status = RCC_enuPriEnable(RCC_enuPriEnableArray[local_iterator]);
		}

	#if RCC_SystemClock != RCC_PLL
		local_status = RCC_enuSystemClockSwitch(RCC_SystemClock);			 //switch to RCC_SystemClock
		local_status = RCC_enuDisableSource(local_CurrentSource);		   //disable the prev source
	#else
		local_status = RCC_enuPLLSystemClockSwitch(RCC_PLL_Source , RCC_PLL_M , RCC_PLL_N , RCC_PLL_P , RCC_PLL_Q);
		if( RCC_PLL_Source != local_CurrentSource)
		{
			local_status = RCC_enuDisableSource(local_CurrentSource);		   //disable the prev source
		}
	#endif


	return local_status;
}

RCC_tenuErrorStatus RCC_enuEnableSource(RCC_enuSystemClock_t cpy_source)
{
	RCC_tenuErrorStatus  local_status = RCC_enuOk;
	u8 local_SourceStatus=0; //initialization as all enums for the status are zero in case not ready
	switch(cpy_source)
	{
		case RCC_enuHSI:
			SET_BIT(RCC.RCC_CR,0);
			while( local_SourceStatus == RCC_enuHSINotReady)
			{
				local_status = RCC_enuCheckClockStatus( RCC_enuHSI,&local_SourceStatus );
			}
		break;

		case RCC_enuHSE:
			SET_BIT(RCC.RCC_CR,16);
			while( local_SourceStatus == RCC_enuHSENotReady)
			{
				local_status = RCC_enuCheckClockStatus( RCC_enuHSE,&local_SourceStatus );
			}
		break;

		case RCC_enuPLL:
			SET_BIT(RCC.RCC_CR,24);
			while( local_SourceStatus == RCC_enuPLLNotLocked)
			{
				local_status = RCC_enuCheckClockStatus( RCC_enuPLL,&local_SourceStatus );
			}
		break;
	}
	return local_status;
}

RCC_tenuErrorStatus RCC_enuDisableSource(RCC_enuSystemClock_t cpy_source)
{
	RCC_tenuErrorStatus  local_status = RCC_enuOk;
	RCC_enuSystemClock_t local_CurrentSource;
	u8 local_SourceStatus=1;              //initial value for ready state
	local_status = RCC_enuGetSystemClock(&local_CurrentSource);
	if (local_CurrentSource != cpy_source) //the source must be not the system clock source
	{
		switch(cpy_source)
		{
			case RCC_enuHSI:
				CLR_BIT(RCC.RCC_CR,0);
				while( local_SourceStatus == RCC_enuHSIReady)
				{
					local_status = RCC_enuCheckClockStatus( RCC_enuHSI,&local_SourceStatus );
				}

			break;

			case RCC_enuHSE:
				CLR_BIT(RCC.RCC_CR,16);
				while( local_SourceStatus == RCC_enuHSEReady)
				{
					local_status = RCC_enuCheckClockStatus( RCC_enuHSE,&local_SourceStatus );
				}

			break;

			case RCC_enuPLL:
				CLR_BIT(RCC.RCC_CR,24);
				while( local_SourceStatus == RCC_enuPLLLocked)
			{
				local_status = RCC_enuCheckClockStatus( RCC_enuPLL,&local_SourceStatus );
			}

			break;
		}
	}

	else
	{
		local_status = RCC_enuNotOk;
	}
	return local_status;
}

RCC_tenuErrorStatus RCC_enuSystemClockSwitch(RCC_enuSystemClock_t cpy_source)
{
	RCC_tenuErrorStatus  local_status = RCC_enuOk;
	RCC_enuSystemClock_t local_CurrentSource = cpy_source;
	local_status = RCC_enuEnableSource(cpy_source);//enable the source and wait to be ready
	switch(cpy_source)
	{
		case RCC_enuHSI:
			RCC.RCC_CFGR =  WriteBinaryVal(RCC.RCC_CFGR ,(0b00), 0, 2);
			while(local_CurrentSource != RCC_enuHSI)
			{
				local_status = RCC_enuGetSystemClock(&local_CurrentSource);
			}
		break;

		case RCC_enuHSE:
			RCC.RCC_CFGR =  WriteBinaryVal(RCC.RCC_CFGR ,(0b01), 0, 2);
			while(local_CurrentSource != RCC_enuHSE)
			{
				local_status = RCC_enuGetSystemClock(&local_CurrentSource);
			}
		break;

	}
	return local_status;
}


RCC_tenuErrorStatus RCC_enuPLLSystemClockSwitch(RCC_enuSystemClock_t cpy_source , RCC_enuPLLM_t cpy_M , RCC_enuPLLN_t cpy_N , RCC_enuPLLP_t cpy_P , RCC_enuPLLQ_t cpy_Q )
{
	RCC_tenuErrorStatus local_status = RCC_enuOk;
	RCC_enuSystemClock_t local_CurrentSource = cpy_source;

	local_status = RCC_enuGetSystemClock(&local_CurrentSource);

	if(local_CurrentSource != RCC_enuPLL)
	{
		local_status = RCC_enuConfigPLL(cpy_source , cpy_M , cpy_N ,cpy_P ,cpy_Q);
		RCC.RCC_CFGR =  WriteBinaryVal(RCC.RCC_CFGR ,(0b10), 0, 2);
			while(local_CurrentSource != RCC_enuPLL)
			{
				local_status = RCC_enuGetSystemClock(&local_CurrentSource);
			}
	}

	else   //thiscondition when we need to reconfigure pll and it is system clock
	{
		local_status = RCC_enuSystemClockSwitch(cpy_source);    //switch the system clock in the source of PLL
		local_status = RCC_enuConfigPLL(cpy_source , cpy_M , cpy_N ,cpy_P ,cpy_Q); //configure PLL
		RCC.RCC_CFGR =  WriteBinaryVal(RCC.RCC_CFGR ,(0b10), 0, 2);
			while(local_CurrentSource != RCC_enuPLL)
			{
				local_status = RCC_enuGetSystemClock(&local_CurrentSource);
			}

	}

	return local_status;
}


RCC_tenuErrorStatus RCC_enuConfigPLL(RCC_enuSystemClock_t cpy_source , RCC_enuPLLM_t cpy_M , RCC_enuPLLN_t cpy_N , RCC_enuPLLP_t cpy_P , RCC_enuPLLQ_t cpy_Q )
{
	u8 local_SourceStatus=0;
	RCC_enuStatePLL_t local_enuPLLStatus = RCC_enuPLLLocked; //intialization as locked status for pll
	RCC_tenuErrorStatus local_status = RCC_enuOk;
	
	local_status = RCC_enuDisableSource(RCC_enuPLL);     //disable the PLL and check if it is not locked
	
	RCC.RCC_PLLCFGR =  WriteBinaryVal(RCC.RCC_PLLCFGR , cpy_M , 0, 6);
	RCC.RCC_PLLCFGR =  WriteBinaryVal(RCC.RCC_PLLCFGR , cpy_N , 6, 9);
	RCC.RCC_PLLCFGR =  WriteBinaryVal(RCC.RCC_PLLCFGR , cpy_P , 16, 2);
	RCC.RCC_PLLCFGR =  WriteBinaryVal(RCC.RCC_PLLCFGR , cpy_Q , 24, 4);
	
	switch(cpy_source)
	{
		case RCC_enuHSI:
			local_status = RCC_enuCheckClockStatus(cpy_source , &local_SourceStatus); //check the status of HSI
			if(local_SourceStatus == RCC_enuHSINotReady)
			{
				local_status = RCC_enuEnableSource(RCC_enuHSI);   //enable the HSI and wait until it is ready
				CLR_BIT(RCC.RCC_PLLCFGR,22);
			}

			else
			{
				CLR_BIT(RCC.RCC_PLLCFGR,22);
			}
		break;
		case RCC_enuHSE:
			local_status = RCC_enuCheckClockStatus(cpy_source , &local_SourceStatus); //check the status of HSE
			if(local_SourceStatus == RCC_enuHSENotReady)
			{
				local_status = RCC_enuEnableSource(RCC_enuHSE);   //enable the HSE and wait until it is ready
				SET_BIT(RCC.RCC_PLLCFGR,22);
			}
			
			else
			{
				SET_BIT(RCC.RCC_PLLCFGR,22);
			}
		break;
	}

	local_status = RCC_enuEnableSource(RCC_enuPLL);   //enable the PLL and wait until it is ready

	return local_status;
}

RCC_tenuErrorStatus RCC_enuPriEnable(RCC_enuPri_t cpy_pri)
{
	RCC_tenuErrorStatus local_status = RCC_enuOk;
	if ((cpy_pri>=RCC_GPIOA) && (cpy_pri<=RCC_DMA2)) //AHB1ENR
	{
		SET_BIT(RCC.RCC_AHB1ENR , cpy_pri);
	}
	
	else if(cpy_pri==RCC_OTGFS) //AHB2ENR
	
	{
		SET_BIT(RCC.RCC_AHB2ENR , RCC_OTGFS);
	}	

	else if((cpy_pri>=RCC_TIM2) && (cpy_pri<=RCC_PWR)) //APB1ENR
	{
		SET_BIT(RCC.RCC_APB1ENR , (cpy_pri-RCC_TIM2));
	}
	
	else if((cpy_pri>=RCC_TIM1) && (cpy_pri<=RCC_TIM11)) //APB2ENR
	{
		SET_BIT(RCC.RCC_APB2ENR , (cpy_pri-RCC_TIM1));
	}
	
	else
	{
		local_status = RCC_enuNotOk;
	}
	
	return local_status;
}

RCC_tenuErrorStatus RCC_enuPriDisable(RCC_enuPri_t cpy_pri)
{
	RCC_tenuErrorStatus local_status = RCC_enuOk;
	if ((cpy_pri>=RCC_GPIOA) && (cpy_pri<=RCC_DMA2)) //AHB1ENR
	{
		CLR_BIT(RCC.RCC_AHB1ENR , cpy_pri);
	}
	
	else if(cpy_pri==RCC_OTGFS) //AHB2ENR
	
	{
		CLR_BIT(RCC.RCC_AHB2ENR , RCC_OTGFS);
	}	

	else if((cpy_pri>=RCC_TIM2) && (cpy_pri<=RCC_PWR)) //APB1ENR
	{
		CLR_BIT(RCC.RCC_APB1ENR , (cpy_pri-RCC_TIM2));
	}
	
	else if((cpy_pri>=RCC_TIM1) && (cpy_pri<=RCC_TIM11)) //APB2ENR
	{
		CLR_BIT(RCC.RCC_APB2ENR , (cpy_pri-RCC_TIM1));
	}
	
	else
	{
		local_status = RCC_enuNotOk;
	}
	
	return local_status;
}

RCC_tenuErrorStatus RCC_enuCheckClockStatus(RCC_enuSystemClock_t cpy_source ,  u8* add_status)
{
	RCC_tenuErrorStatus local_status = RCC_enuOk;
	if(add_status == Null_Ptr)
	{
		local_status = RCC_enuNullPtr;
	}
	
	else
	{
		switch(cpy_source)
		{
			case RCC_enuHSI:
				*add_status = GET_BIT(RCC.RCC_CR , 1);
		
			break;
			
			case RCC_enuHSE:
				*add_status = GET_BIT(RCC.RCC_CR , 17);
			break;
			
			case RCC_enuPLL:
				*add_status = GET_BIT(RCC.RCC_CR , 25);
			break;
			
		}
	}
	
	return local_status;
}

RCC_tenuErrorStatus RCC_enuGetSystemClock(RCC_enuSystemClock_t* add_source)
{
	RCC_tenuErrorStatus local_status = RCC_enuOk;
	if(add_source == Null_Ptr)
	{
		local_status = RCC_enuNullPtr;
	}
	
	else
	{
		if( GET_BIT(RCC.RCC_CFGR , 3) == 1 )
		{
			if ( GET_BIT(RCC.RCC_CFGR , 2) == 1 )
			{
				local_status = RCC_enuNotOk;
			}
			
			else
			{
				*add_source = RCC_enuPLL;
			}
		}
		
		else
		{
			if ( GET_BIT(RCC.RCC_CFGR , 2) == 1 )
			{
				*add_source = RCC_enuHSE;
			}
			
			else
			{
				*add_source = RCC_enuHSI;
			}
		}
	}
	return local_status;
}

RCC_tenuErrorStatus RCC_enuConfigurePres(RCC_enuPrescaler_t cpy_pre , u8 val)
{
	RCC_tenuErrorStatus local_status = RCC_enuOk;
	
	switch(cpy_pre)
	{
		case RCC_enuPreAHB:
			RCC.RCC_CFGR =  WriteBinaryVal(RCC.RCC_CFGR , val , 4, 4);
		break;
		
		case RCC_enuPreAPB1:
			RCC.RCC_CFGR =  WriteBinaryVal(RCC.RCC_CFGR , val , 10, 3);
		break;
		
		case RCC_enuPreAPB2:
			RCC.RCC_CFGR =  WriteBinaryVal(RCC.RCC_CFGR , val , 13, 3);
		break;
	}
	return local_status;
}
