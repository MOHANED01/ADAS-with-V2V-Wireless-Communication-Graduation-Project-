// TIM1_interface.h

#ifndef MCAL_TIM1_TIM1_INTERFACE_H_
#define MCAL_TIM1_TIM1_INTERFACE_H_
#include "TIM1_private.h"
#include "../../LIB/STD_TYPES_H.h"

typedef enum
{
	Upcounter,Downcounter
}Direction;

typedef enum
{
	CH1,CH1_2_3
}TI_selection;

typedef enum
{
	NoPrescaler,Two_Events,Four_Events,Eight_Events
}IC1_Prescaler;

typedef enum
{
	Output,Input_TI1,Input_TI2,Input_TRC
}CC1_Selection;


typedef struct
{
	u8 Direction;
	u8 TI_selection;
	u8 IC1_Prescaler;
	u8 CC1_Selection;
	u8 T1_Prescaler;
}TIM1_ConfigType;


void TIM1_vInit(const TIM1_ConfigType *Config_Ptr);

void TIM1_START(void);

void TIM1_STOP(void);

u16 TIM1_InputCapture(void);





#endif
