// TIM1_private.h

#ifndef MCAL_TIM1_TIM1_PRIVATE_H_
#define MCAL_TIM1_TIM1_PRIVATE_H_

#define TIM1_BASE_ADDRESS	0X40010000
#define TIM1				(*((volatile unsigned long *)0x40010000))
#define TIM1_CR1			(*((volatile unsigned long *)0x40010000))
#define TIM1_CR2			(*((volatile unsigned long *)0x40010004))
#define TIM1_SMCR			(*((volatile unsigned long *)0x40010008))
#define TIM1_DIER			(*((volatile unsigned long *)0x4001000C))
#define TIM1_SR				(*((volatile unsigned long *)0x40010010))
#define TIM1_EGR			(*((volatile unsigned long *)0x40010014))
#define TIM1_CCMR1			(*((volatile unsigned long *)0x40010018))
#define TIM1_CCMR2			(*((volatile unsigned long *)0x4001001C))
#define TIM1_CCER			(*((volatile unsigned long *)0x40010020))
#define TIM1_CNT			(*((volatile unsigned long *)0x40010024))
#define TIM1_PSC			(*((volatile unsigned long *)0x40010028))
#define TIM1_ARR			(*((volatile unsigned long *)0x4001002C))
#define TIM1_RCR			(*((volatile unsigned long *)0x40010030))
#define TIM1_CCR1			(*((volatile unsigned long *)0x40010034))
#define TIM1_CCR2			(*((volatile unsigned long *)0x40010038))
#define TIM1_CCR3			(*((volatile unsigned long *)0x4001003C))
#define TIM1_CCR4			(*((volatile unsigned long *)0x40010040))
#define TIM1_BDTR			(*((volatile unsigned long *)0x40010044))
#define TIM1_DCR			(*((volatile unsigned long *)0x40010048))
#define TIM1_DMAR			(*((volatile unsigned long *)0x4001004C))

#define DIR 	4
#define CEN		0
#define TI1S 	7
#define CC1OF	9
#define CC1IF	1
#define CC1P	1
#define CC1E	0
#define IC1PSC	2
#define CC1S 	0


#endif
