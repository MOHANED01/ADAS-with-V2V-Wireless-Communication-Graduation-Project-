/*
 * FMI_prog.c
 *
 *  Created on: Sep 6, 2023
 *      Author: mohaned
 */

#include"../../LIB/BIT_MATH.h"
#include"../../LIB/STD_TYPES_H.h"

#include"FMI_private.h"
#include"FMI_config.h"
#include"FMI_interface.h"

void MFMI_vSectorErase(ERASE* A_EraseStruct)
{
	/*reset register*/
	FLASH->CR= 0x80000000;

	while(GET_BIT(FLASH->SR,BSY)==1)
	{
		/*if flash memory is doing an operation --> wait */
	}

	/*in case of password not written --> write it to unlock CR register */
	if(GET_BIT( FLASH->CR,LOCK)==1)
	{
		FLASH->KEYR = KEY1;
		FLASH->KEYR = KEY2;
	}

	/*to set program size */
	FLASH->CR|=(u32)(A_EraseStruct->Size_Prescale<<PSIZE);

	/*to set which sector wants to erase */
	FLASH->CR|=(u32)(A_EraseStruct->Sector_Number<<SNB);

	/*to activate erase not flashing a program */
	SET_BIT(FLASH->CR,SER);

	/*start erase */
	SET_BIT(FLASH->CR,STRT);

	/*wait till erase occur*/
	while(GET_BIT(FLASH->SR,BSY));

	/*deactivate Sector erase*/
	CLR_BIT(FLASH->CR,SER);

}


void MFMI_vFlashWrite(WRITE* A_WriteStruct)
{
	/*reset register*/
	FLASH->CR= 0x80000000;

	while(GET_BIT(FLASH->SR,BSY)==1)
	{
		/*if flash memory is doing an operation --> wait */
	}

	/*in case of password not written --> write it to unlock CR register */
	if(GET_BIT( FLASH->CR,LOCK)==1)
	{
		FLASH->KEYR = KEY1;
		FLASH->KEYR = KEY2;
	}

	/*to set program size */
	FLASH->CR|=(u32)(A_WriteStruct->Size_Prescale<<PSIZE);

	/*to set which sector wants to erase */
	FLASH->CR|=(u32)(A_WriteStruct->Sector_Number<<SNB);

	/*to activate flashing program mood */
	SET_BIT(FLASH->CR,PG);

	for(u16 i=0;i<A_WriteStruct->Length_Of_Array;i++)
		{
			*((volatile u16*)(A_WriteStruct->Write_Address)) =  A_WriteStruct->Read_Address_Array[i];
			A_WriteStruct->Write_Address+=2;/*###########################*/

			/*wait if flash is busy */
			while(GET_BIT(FLASH->SR,BSY));

		}

	/*deactivate flashing program mood */
		CLEAR_BIT(FLASH->CR,PG);
}


