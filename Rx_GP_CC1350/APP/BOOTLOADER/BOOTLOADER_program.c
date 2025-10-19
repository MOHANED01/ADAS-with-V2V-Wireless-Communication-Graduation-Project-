/*
 * BOOTLOADER.program.c
 *
 *  Created on: Sep 7, 2023
 *      Author: mohaned
 */
#include"../../LIB/BIT_MATH.h"
#include"../../LIB/STD_TYPES_H.h"

#include"../HEXPARSER/HEXPARSER_interface.h"
#include"../../MCAL/FMI/FMI_Interface.h"
#include"../../MCAL/SYSTICK/SYSTICK_interface.h"
#include"../../MCAL/UART/UART_interface.h"
#include"../../MCAL/RCC/RCC_int.h"
#include"../../MCAL/GPIO/GPIO_int.h"

#define RECORD_OK 255
#define START_BOOTING 1


/*address of Vector Table*/
#define SCB_VTOR  *((volatile u32*) (0xE000ED00 + 0x08))

typedef void (*G_tptr)(void);


void BOOTLOADER_vInitSystemBoot(void)
{
	/*RCC enable*/
	MRCC_vInit();
	/* Enable USART2 peripheral clock */
	MRCC_vEnableClock(RCC_APB1,RCC_EN_UART2);
	/*Enable FDI peripheral clock */
	MRCC_vEnableClock(RCC_AHB1LP,RCC_EN_FLITFLPEN);



	MGPIO_vSetPinMode(GPIO_PORTA,GPIO_PIN9,GPIO_MODE_OUTPUT);
	MGPIO_vSetPinOutputType(GPIO_PORTA,GPIO_PIN9,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTA,GPIO_PIN9,GPIO_OUTSPEED_LOW);

	/*GPIO enable --> Alternative Function */
	MGPIO_vSetPinMode(GPIO_PORTA,GPIO_PIN2,GPIO_MODE_ALTFUN);
	MGPIO_vSetPinOutputType(GPIO_PORTA,GPIO_PIN2,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTA,GPIO_PIN2,GPIO_OUTSPEED_LOW);
	MGPIO_vSetAlternativeFunction(GPIO_PORTA,GPIO_PIN2,7);

	MGPIO_vSetPinMode(GPIO_PORTA,GPIO_PIN3,GPIO_MODE_ALTFUN);
	MGPIO_vSetPinOutputType(GPIO_PORTA,GPIO_PIN3,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTA,GPIO_PIN3,GPIO_OUTSPEED_LOW);
	MGPIO_vSetAlternativeFunction(GPIO_PORTA,GPIO_PIN3,7);


	/*USART init*/
	USART_InitType uart_init={9600,USART_MODE_8BIT,USART_STOP_BIT_1,
			DISABLE,USART_EVEN_PARITY,USART_TX_RX,USART_OVER_SAMPLING_8 };
	MUSART_vInit(&uart_init,USART2);

	/*systick init*/
	MSYSTICK_vInit();


}

static void APP_vSystemBoot(void)
{
	SCB_VTOR = 0x08004000;

	/*define local variable to points on address that i want to be run */
	G_tptr L_Application=NULL;

	/*Set Address to call with Reset Handeler_ISR [startup code of Application]
	 * startup code of a specific application */

	L_Application = *(G_tptr*)0x08004004;

	/*jump to startup code of this application*/
	L_Application();
}

void BOOTLOADER_vStartBootLoader(void)
{


	u8 i=0,L_EraseFlag=0,L_ReceiveBuffer[100]={0};

	/*receive record via USART in array*/
	L_ReceiveBuffer[i]=MUSART_u8ReceiveByteSynchBlocking(USART2);

	/*while not reached end of file ...continue receiving*/

	while(L_ReceiveBuffer[8]!='1')
	{
		while(L_ReceiveBuffer[i]!='\0')
		{
			i++;
			if(L_ReceiveBuffer[8]=='1')
			{
				/*in case of end of file...out of first loop */
				break;
			}
			//MSYSTICK_vSetBusyWait_ms(10);
			while(MUSART_u8ReceiveByteSynchBlocking(USART2)!=START_BOOTING)
			{
				/*in case of not receiving START_BOOTING be in infinite loop */
			}
			MUSART_vTransmitByteSynch(USART2,START_BOOTING);
			L_ReceiveBuffer[i]=MUSART_u8ReceiveByteSynchBlocking(USART2);

			//			if(L_ReceiveBuffer[0] == ':'&&L_ReceiveBuffer[1]=='0'&&L_ReceiveBuffer[2]=='2'&&L_ReceiveBuffer[3]=='0' )
			//			MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN9,GPIO_HIGH);
			/*now i received first record*/
		}
		//		if(L_ReceiveBuffer[i]=='\0')
		//			MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN9,GPIO_HIGH);

		if(L_ReceiveBuffer[8]=='1')
		{
			/*in case of end of file ....out of second while loop*/
			break;
		}
		else
		{
			if(L_EraseFlag==0)
			{
				L_EraseFlag=1;
				/*erase application area
				 *FMI init          */
				//				ERASE erase={sector0,prescale16};
				//				MFMI_vSectorErase(&erase);

				 MFMI_vEraseSector(FMI_SEC0);
				//void MFMI_vFlashWrite(FMI_WriteOperationData* WriteStruct);
//				if(L_ReceiveBuffer[i]=='\0')
//					MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN9,GPIO_HIGH);

				//MSYSTICK_vSetBusyWait_ms(10);
			//	MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN9,GPIO_HIGH);
			}


			/*write application area*/
//			if(L_ReceiveBuffer[i]=='\0')

			HEXPARSER_vParseData(L_ReceiveBuffer);
			MSYSTICK_vSetBusyWait_ms(5);
			//			if(L_ReceiveBuffer[i]=='\0')
			//				MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN9,GPIO_HIGH);


			/*send as acknowledgment   */
			MUSART_vTransmitByteSynch(USART2,RECORD_OK);
			MSYSTICK_vSetBusyWait_ms(5);
			//			MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN9,GPIO_HIGH);


			/*start again*/
			i=0;

		}


	}


	/*in case of end of file  send acknowledgment */
	/*MUSART_vTransmitByteSynch(USART2,FILE_OK);*/

	/*stay 50ms then go to your APPLICATION*/
	MSYSTICK_vSetIntervalSingle_ms(50,APP_vSystemBoot);



}

