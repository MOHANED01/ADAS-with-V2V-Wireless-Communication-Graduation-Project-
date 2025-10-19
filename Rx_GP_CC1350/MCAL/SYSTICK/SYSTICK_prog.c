/*
 * SYSTICK_prog.c
 *
 *  Created on: Aug 15, 2023
 *      Author: mohaned
 */
#include"../../LIB/STD_TYPES_H.h"
#include"../../LIB/BIT_MATH.h"

#include"SYSTICK_config.h"
#include"SYSTICK_interface.h"
#include"SYSTICK_private.h"

static void (*G_CallBackPtrSingle)(void)=NULL;
static void (*G_CallBackPtrPeriodic)(void)=NULL;

void MSYSTICK_vStartTimer(void)
{
	SET_BIT(SYSTICK->CTRL,0);
}

void MSYSTICK_vStopTimer(void)
{
	CLEAR_BIT(SYSTICK->CTRL,0);
}

void MSYSTICK_vInit(void)
{
	/*enable clk */
	#if (SYSTICK_CLK_SOURCE==SYSTICK_AHB)
	{
		SET_BIT(SYSTICK->CTRL,2);
	}
	#elif(SYSTICK_CLK_SOURCE==SYSTICK_AHB_OVER_8)
	{
		CLEAR_BIT(SYSTICK->CTRL,2);
	}
	#endif
/*enable PIE*/
#if (SYSTICK_INTERRUPT==ENABLE)
{
	SET_BIT(SYSTICK->CTRL,1);
}
#elif(SYSTICK_INTERRUPT==DISABLE)
{
	CLEAR_BIT(SYSTICK->CTRL,0);
	CLEAR_BIT(SYSTICK->CTRL,1);
}
#endif




}


void MSYSTICK_vSetBusyWait_ms(u32 A_u32Tick)
{
/*initialize VALUE register*/
	SYSTICK->VAL=0X00000000;
	A_u32Tick=(A_u32Tick*1000);/*to transfare it to micro*/
	/*put our number in LOAD register*/
	SYSTICK->LOAD=A_u32Tick;
	/*start timer by enable the counter */
	MSYSTICK_vStartTimer();
	/*polling to flag*/
	while(GET_BIT(SYSTICK->CTRL,16)==0)
	{

	}
	MSYSTICK_vStopTimer();

}


void MSYSTICK_vSetIntervalSingle_ms(u32 A_u32Tick, void(*A_CallBackFun)(void))
{
	/*initialize VALUE register*/
		SYSTICK->VAL=0X00000000;
		A_u32Tick=(A_u32Tick*1000);/*to transfare it to micro*/
		/*put our number in LOAD register*/
		SYSTICK->LOAD=A_u32Tick;
		G_CallBackPtrSingle=A_CallBackFun;
		/*start timer by enable the counter */
		MSYSTICK_vStartTimer();
		SET_BIT(SYSTICK->CTRL,TICKINT);
}

void MSYSTICK_vSetIntervalPeriodic_ms(u32 A_u32Tick, void(*A_CallBackFun)(void))
{
	/*initialize VALUE register*/
			SYSTICK->VAL=0X00000000;
			A_u32Tick=(A_u32Tick*1000);/*to transfare it to micro*/
			/*put our number in LOAD register*/
			SYSTICK->LOAD=A_u32Tick;
			G_CallBackPtrPeriodic=A_CallBackFun;

			/*start timer by enable the counter */
			MSYSTICK_vStartTimer();
			SET_BIT(SYSTICK->CTRL,TICKINT);


}


u32 MSYSTICK_u32GetElapsedTime_us()
{
	return  ((SYSTICK->LOAD)-(SYSTICK->VAL)) ;
}


u32 MSYSTICK_u32GetRemainingTime_us()
{
	return  (SYSTICK->VAL) ;
}

void  SysTick_Handler (void)
{
	if(G_CallBackPtrPeriodic!=0)
	{
		G_CallBackPtrPeriodic();
	}
	else if (G_CallBackPtrSingle!=0)
		{
		G_CallBackPtrSingle();
		G_CallBackPtrSingle=NULL;
		MSYSTICK_vStopTimer();
		}

}






