/*
 * HEXPARSER_program.c
 *
 *  Created on: Sep 7, 2023
 *      Author: mohaned
 */
#include"../../LIB/BIT_MATH.h"
#include"../../LIB/STD_TYPES_H.h"

#include"../../MCAL/FMI/FMI_Interface.h"

#include"HEXPARSER_config.h"
#include"HEXPARSER_interface.h"
#include"HEXPARSER_private.h"



/*
 * each line in hex file called record...each record consists of :
 * 1)first 2 digits are character count to specify data size in byte
 * 2)next 4 digits are low address
 * 3)next 2 digits are record type
 * 00-> data , 01->end of file , 04->high address , 05->absolute address
 * 4) data
 * 5)last 2 digits are checksum
 *":10 0000 00 0000 0120 C502 0008 CB02 0008 CF02 0008  52"
 * 012 3456 78 9 (location of each digit in array)
 *0x10   0b0001 0000 --> 16 bytes data
 *CharacterCount size   CC =  (CC_H<<4) |  CC_L (as binary now CC is need to determine size of array to send) ;
 *lower_address   bit3,4,5,6
 *address = lower_address | (Higher_address<<4) ;
  */


/*this function used to transfer ascii code to hex(as we receive file as ascii code not hex)
 * transfer only one digit hex*/
static u8 HEXPARSER_u8AsciiToHex(u8 A_u8Ascii)
{
	u8 L_ReturnValue=0;
	if(A_u8Ascii>='0' && A_u8Ascii<='9')
	{
		L_ReturnValue = A_u8Ascii - '0' ;
	}
	else if (A_u8Ascii>='A' && A_u8Ascii<='F')
	{
		L_ReturnValue = A_u8Ascii- 'A' + 10 ;
	}
	return  L_ReturnValue ;
}

/*to flash hex file record by record then burn it in flash
 * A_u8Data is an address to a specific record */
void HEXPARSER_vParseData(u8 *A_u8Data)
{
	u8 L_CC,L_CC_Low,L_CC_High,L_Digits[4]={0};
	u16 L_Buffer[50]={0};
	u32 L_Address;

	/*counter counts to detect data size*/
	L_CC_Low=HEXPARSER_u8AsciiToHex(A_u8Data[1]);/*transfer only one hex digit*/
	L_CC_High=HEXPARSER_u8AsciiToHex(A_u8Data[2]);
	L_CC=L_CC_Low|(L_CC_High<<4);

	/*lower address*/
	for(u8 i=0;i<4;i++)
	{
		L_Digits[i]=HEXPARSER_u8AsciiToHex(A_u8Data[3+i]);
	}
		L_Address =(u32) ((L_Digits[0]<<12) | (L_Digits[1]<<8) | (L_Digits[2]<<4) | (L_Digits[3]) | HIGH_ADDRESS);

		for(u8 i=0 ; i<(L_CC/2) ;i++)
		{
			L_Digits[0] = HEXPARSER_u8AsciiToHex(A_u8Data[i*4+9]);
			L_Digits[1] = HEXPARSER_u8AsciiToHex(A_u8Data[i*4+10]);
			L_Digits[2] = HEXPARSER_u8AsciiToHex(A_u8Data[i*4+11]);
			L_Digits[3] = HEXPARSER_u8AsciiToHex(A_u8Data[i*4+12]);
			L_Buffer[i] =((L_Digits[0]<<12) | (L_Digits[1]<<8) | (L_Digits[2]<<4) | L_Digits[3]) ;
		}

//		WRITE write={sector0,prescale16,L_Address,L_Buffer,L_CC/2};
//	    MFMI_vFlashWrite(&write);
	 //   MFMI_vFlashWrite( L_Address,L_Buffer,L_CC/2  );



}
