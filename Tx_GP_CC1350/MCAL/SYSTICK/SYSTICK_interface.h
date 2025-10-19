/*
 * SYSTICK_interface.h
 *
 *  Created on: Aug 15, 2023
 *      Author: mohaned
 */

#ifndef MCAL_SYSTICK_SYSTICK_INTERFACE_H_
#define MCAL_SYSTICK_SYSTICK_INTERFACE_H_

/*
 * SYSTICK_interface.h
 *
 *  Created on: Feb 28, 2023
 *      Author: mohaned
 */

#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_
#include"../../LIB/STD_TYPES_H.h"



/*apply clock choice(AHB or AHB/8) from config file*/
void MSYSTICK_vInit(void);

/*
 * this function make synch. delay
 * i assume F=8MHZ*/
void MSYSTICK_vSetBusyWait_ms(u32 A_u32Tick);

void MSYSTICK_vSetBusyWait_us(u32 A_u32Tick);

/*
 *  name of call back function(name of function to be executed when timer end counting)
 * callback function executed one time only
 * i assume F=8MHZ*/
void MSYSTICK_vSetIntervalSingle_ms(u32 A_u32Tick, void(*CallBackFun)(void));

/*
 *  name of call back function(name of function to be executed when timer end counting)
 * callback function executed periodic
 * i assume F=8MHZ*/
void MSYSTICK_vSetIntervalPeriodic_ms(u32 A_u32Tick, void(*CallBackFun)(void));

/*how many time elapsed
 * i assume F=8MHZ*/
u32 MSYSTICK_u32GetElapsedTime_us();

/*what is the remaining time
 * i assume F=8MHZ*/
u32 MSYSTICK_u32GetRemainingTime_us();
/*to stop counting */
void MSYSTICK_vStopTimer(void);

#endif


#endif /* MCAL_SYSTICK_SYSTICK_INTERFACE_H_ */
