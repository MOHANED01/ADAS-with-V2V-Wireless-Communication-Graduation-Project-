/*
 * common_macros.h


 *
 *  Created on: Jul 20, 2022
 *      Author: Bahgat Mahmoud
 */

#ifndef UTILS_BIT_MATH_H_
#define UTILS_BIT_MATH_H_

#define   SET_BIT(VAR,BIT)  (VAR)|= ( 1<<(BIT))
#define   TOG_BIT(VAR,BIT)  (VAR)^= ( 1<<(BIT))
#define   CLEAR_BIT(VAR,BIT)  (VAR)&= ~(1<< (BIT))
#define   GET_BIT(VAR,BIT)   ((VAR>>(BIT)) & 1)
#define   BIT_IS_CLEAR(VAR,BIT)  !(( VAR &(1<<BIT))>>BIT)

#endif /* UTILS_COMMON_MACROS_H_ */

