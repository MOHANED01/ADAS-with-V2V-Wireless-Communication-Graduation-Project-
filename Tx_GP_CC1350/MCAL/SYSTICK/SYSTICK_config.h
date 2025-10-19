/*
 * SYSTICK_config.h
 *
 *  Created on: Aug 15, 2023
 *      Author: mohaned
 */

#ifndef MCAL_SYSTICK_SYSTICK_CONFIG_H_
#define MCAL_SYSTICK_SYSTICK_CONFIG_H_

/*you can choose on of these options
 *  SYSTICK_AHB
 * SYSTICK_AHB_OVER_8
 */
#define SYSTICK_CLK_SOURCE  SYSTICK_AHB_OVER_8
/*
 * ENABLE
 * DISABLE
 */
#define SYSTICK_INTERRUPT  ENABLE


#endif /* MCAL_SYSTICK_SYSTICK_CONFIG_H_ */
