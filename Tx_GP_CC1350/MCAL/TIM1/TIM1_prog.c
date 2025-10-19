
#include"../../LIB/STD_TYPES_H.h"
#include"../../LIB/BIT_MATH.h"

#include"TIM1_config.h"
#include"TIM1_interface.h"
#include"TIM1_private.h"
//#include "../GPIO/GPIO_int.h"
//#include "../SYSTICK/SYSTICK_interface.h"

void TIM1_vInit(const TIM1_ConfigType *Config_Ptr){
	TIM1_CR1 |= (Config_Ptr->Direction<<DIR);
	TIM1_CR2 |= (Config_Ptr->TI_selection << TI1S);
	TIM1_CCMR1 |= (Config_Ptr->IC1_Prescaler <<IC1PSC) | (Config_Ptr->CC1_Selection <<CC1S);
	TIM1_PSC = Config_Ptr->T1_Prescaler;
	SET_BIT(TIM1_CCER,CC1E);
	TIM1_CNT = 0;
}

void TIM1_START(void){
	SET_BIT(TIM1_CR1,CEN);
}

void TIM1_STOP(void){
	TIM1_CNT = 0;
	CLEAR_BIT(TIM1_CR1,CEN);
}

u16 TIM1_InputCapture(void){
	u16 Dummy;
	SET_BIT(TIM1_CR1,CEN); // Start counter
	CLEAR_BIT(TIM1_CCER,CC1P); // Detect Rising edge
	while((BIT_IS_CLEAR(TIM1_SR,CC1IF))){} // Wait for Rising edge
	Dummy= TIM1_CCR1;
	TIM1_CNT=0; // Reset timer
	SET_BIT(TIM1_CCER,CC1P); // Change to waiting for Falling edge
	while((BIT_IS_CLEAR(TIM1_SR,CC1IF))){} // Wait for Falling edge
	TIM1_STOP(); // Falling edge detected, stop the timer
	return TIM1_CCR1; // return the high time in ticks
}
