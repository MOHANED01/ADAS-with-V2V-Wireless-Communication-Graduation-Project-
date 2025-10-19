/******************************************************************/
/* Author  :MOHAMED ADEL                                          */
/* Version :VO1                                                   */
/* Data    :2019                                                  */
/******************************************************************/
/******************************************************************/
/* Description                                                    */
/* -----------                                                    */
/* this components is used to define the basic standend           */
/* types used in the system developed in the course               */
/******************************************************************/
/******************************************************************/
/******************************************************************/
/**  This unpublished material is proprietary to Mohamed Adel.   **/
/**  All rights reserved. The methods and techniques described   **/
/**  herein are considered trade secrets and/or confidential.    **/
/**  Reproduction or distribution, in whole or in part, is       **/
/**  forbidden except by express written permission of           **/
/**                  Eng:-Mohamed Adel                           **/
/******************************************************************/
/******************************************************************/

/* comment :Header file guard */
#ifndef STD_TYPES_H
#define STD_TYPES_H
#define ZERO 0
#define NULL (void*)0
#define SHIFT_OPERATOR (u8)1

/* comment: unsigned 8 bits types */
typedef unsigned char u8;
/* comment: unsigned 16 bits types */
typedef unsigned short u16;
/* comment: unsigned 32 bits types */
typedef unsigned long int u32;
/* comment: signed 8 bits types */
typedef signed char s8;
/* comment: signed 16 bits types */
typedef signed short int s16;
/* comment: signed 32 bits types */
typedef signed long int s32;
/* comment: float 32 bits types */
typedef float f32;
/* comment: float 64 bits types */
typedef double f64;
typedef  unsigned long long      u64;
typedef  signed   long long      s64;

/*comment : Standard Error Enum used for driver Return type*/
typedef enum
{
	OK = 0,
	NOT_OK

} STD_ERROR;
/*comment : 8 bit register*/
typedef union {
	struct
	{
		u8 BIT0 : 1;
		u8 BIT1 : 1;
		u8 BIT2 : 1;
		u8 BIT3 : 1;
		u8 BIT4 : 1;
		u8 BIT5 : 1;
		u8 BIT6 : 1;
		u8 BIT7 : 1;
	} BitAccess;
	u8 ByteAccess;
} REGISTER_8BIT;

/*comment : 16 bit register*/
typedef union {
	struct
	{
		u16 BIT0 : 1;
		u16 BIT1 : 1;
		u16 BIT2 : 1;
		u16 BIT3 : 1;
		u16 BIT4 : 1;
		u16 BIT5 : 1;
		u16 BIT6 : 1;
		u16 BIT7 : 1;
		u16 BIT8 : 1;
		u16 BIT9 : 1;
		u16 BIT10 : 1;
		u16 BIT11 : 1;
		u16 BIT12 : 1;
		u16 BIT13 : 1;
		u16 BIT14 : 1;
		u16 BIT15 : 1;
	} BitAccess;
	u16 ByteAccess;
} REGISTER_16BIT;

/*comment : 32 bit register*/
typedef union {
	struct
	{
		u32 BIT0 : 1;
		u32 BIT1 : 1;
		u32 BIT2 : 1;
		u32 BIT3 : 1;
		u32 BIT4 : 1;
		u32 BIT5 : 1;
		u32 BIT6 : 1;
		u32 BIT7 : 1;
		u32 BIT8 : 1;
		u32 BIT9 : 1;
		u32 BIT10 : 1;
		u32 BIT11 : 1;
		u32 BIT12 : 1;
		u32 BIT13 : 1;
		u32 BIT14 : 1;
		u32 BIT15 : 1;
		u32 BIT16 : 1;
		u32 BIT17 : 1;
		u32 BIT18 : 1;
		u32 BIT19 : 1;
		u32 BIT20 : 1;
		u32 BIT21 : 1;
		u32 BIT22 : 1;
		u32 BIT23 : 1;
		u32 BIT24 : 1;
		u32 BIT25 : 1;
		u32 BIT26 : 1;
		u32 BIT27 : 1;
		u32 BIT28 : 1;
		u32 BIT29 : 1;
		u32 BIT30 : 1;
		u32 BIT31 : 1;
	} BitAccess;
	u32 ByteAccess;
} REGISTER_32BIT;


#endif //!STD_TYPES_H
