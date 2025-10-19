/*
 * FMI_interface.h
 *
 *  Created on: Sep 6, 2023
 *      Author: mohaned
 */

#ifndef MCAL_FMI_FMI_INTERFACE_H_
#define MCAL_FMI_FMI_INTERFACE_H_

#include"../../LIB/STD_TYPES_H.h"

typedef enum
{
	sector0,sector1,sector2,sector3,sector4,sector5
}SECTOR;

typedef enum
{
	prescale8,prescale16,prescale32,prescale64
}SIZE;

typedef struct
{
	SECTOR Sector_Number; /*choose from sector0->5*/
	SIZE Size_Prescale;  /*choose size prescale program from prescale8,prescale16,..*/
}ERASE;

typedef struct
{
	SECTOR Sector_Number;
	SIZE Size_Prescale;
	u32  Write_Address; /*at which address want to write your data */
	u16* Read_Address_Array;/*address of array that you wants to read data from*/
	u16 Length_Of_Array;/*length of this array*/

}WRITE;

/*this function needed to erase a certain sector, synchronous   */
void MFMI_vSectorErase(ERASE* A_EraseStruct);

/*this function needed to write in a certain sector and address, synchronous   */
void MFMI_vFlashWrite(WRITE* A_WriteStruct);




#endif /* MCAL_FMI_FMI_INTERFACE_H_ */
