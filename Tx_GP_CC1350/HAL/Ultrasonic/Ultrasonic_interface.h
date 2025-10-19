#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_
#include "../../MCAL/TIM1/TIM1_interface.h"
#include "../../MCAL/GPIO/GPIO_int.h"


void Ultrasonic_vInit(void);


u16 Ultrasonic_Get_Distance(void);









#endif
