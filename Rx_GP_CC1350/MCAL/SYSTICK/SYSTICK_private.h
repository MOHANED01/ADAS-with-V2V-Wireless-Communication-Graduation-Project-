/*
 * SYSTICK_private.h
 *
 *  Created on: Aug 15, 2023
 *      Author: mohaned
 */

#ifndef MCAL_SYSTICK_SYSTICK_PRIVATE_H_
#define MCAL_SYSTICK_SYSTICK_PRIVATE_H_

#define SYSTICK_BASE_ADDRESS 0XE000E010
typedef struct
{
	volatile u32 CTRL;
	volatile u32 LOAD;
	volatile u32 VAL;
	volatile u32 CALIB;

}SYSTICK_MemMap_t;

#define SYSTICK ((volatile SYSTICK_MemMap_t*)(SYSTICK_BASE_ADDRESS))


#define COUNTFLAG    16
#define CLKSOURCE    2
#define TICKINT      1
#define SYSTICK_ENABLE   0

#define SYSTICK_AHB       1
#define SYSTICK_AHB_OVER_8  8

#define ENABLE   1
#define DISABLE  0

#define SINGLE   0
#define PERIODIC 1
#endif /* MCAL_SYSTICK_SYSTICK_PRIVATE_H_ */
