/*AUTHOR : MOHANED HOSSAM
 *
 * DATE  : 10/2024
 *
 * DESCRIPTION :test CC1350 in LPWAN comm protocol using USART*/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES_H.h"
#include "MCAL/GPIO/GPIO_int.h"
#include "MCAL/RCC/RCC_int.h"
#include "MCAL/SYSTICK/SYSTICK_interface.h"
#include "MCAL/UART/UART_interface.h"
#include "MCAL/TIM1/TIM1_interface.h"
#include "HAL/Ultrasonic/Ultrasonic_interface.h"

#define START_BYTE 		0x0A
#define END_BYTE 		0X0D
#define CHECK_BYTE_1 	0X56
#define CHECK_BYTE_2 	0X55
#define FAR_DATA 		0x23
#define SEMI_FAR_DATA	0x24
#define NEAR_DATA		0x25
#define VERY_NEAR_DATA	0x26
#define GARBAGE			0x27

void main(void)
{
	/*1- system clock 16MHZ from HSI */
	MRCC_vInit();
	/*2- Enable GPIO peripheral clock for port A */
	MRCC_vEnableClock(RCC_AHB1,RCC_EN_GPIOA);
	/*3- Enable USART2 peripheral clock */
	MRCC_vEnableClock(RCC_APB1,RCC_EN_UART2);
	/*3- Enable FDI peripheral clock */
	MRCC_vEnableClock(RCC_AHB1LP,RCC_EN_FLITFLPEN);
	/*4- Enable TIM1 peripheral clock*/
	MRCC_vEnableClock(RCC_APB2,RCC_EN_TIM1);
	/////////////////////////////////////////////////////

	/* RED LED */
	MGPIO_vSetPinMode(GPIO_PORTA,GPIO_PIN6,GPIO_MODE_OUTPUT);
	MGPIO_vSetPinOutputType(GPIO_PORTA,GPIO_PIN6,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTA,GPIO_PIN6,GPIO_OUTSPEED_LOW);
	/* GREEN LED */
	MGPIO_vSetPinMode(GPIO_PORTA,GPIO_PIN5,GPIO_MODE_OUTPUT);
	MGPIO_vSetPinOutputType(GPIO_PORTA,GPIO_PIN5,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTA,GPIO_PIN5,GPIO_OUTSPEED_LOW);

	/////////////////////////////////////////////////////
	MGPIO_vSetPinMode(GPIO_PORTA,GPIO_PIN0,GPIO_MODE_OUTPUT);
	MGPIO_vSetPinOutputType(GPIO_PORTA,GPIO_PIN0,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTA,GPIO_PIN0,GPIO_OUTSPEED_LOW);
	/////////////////////////////////////////////////////
	/*4- Set Pin Mode For Pins 2 , 3 -> Alternative Function */
	MGPIO_vSetPinMode(GPIO_PORTA,GPIO_PIN2,GPIO_MODE_ALTFUN);
	MGPIO_vSetPinOutputType(GPIO_PORTA,GPIO_PIN2,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTA,GPIO_PIN2,GPIO_OUTSPEED_LOW);
	MGPIO_vSetAlternativeFunction(GPIO_PORTA,GPIO_PIN2,7);
	///////////////////////////////////////////////////////////////////////
	MGPIO_vSetPinMode(GPIO_PORTA,GPIO_PIN3,GPIO_MODE_ALTFUN);
	MGPIO_vSetPinOutputType(GPIO_PORTA,GPIO_PIN3,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTA,GPIO_PIN3,GPIO_OUTSPEED_LOW);
	MGPIO_vSetAlternativeFunction(GPIO_PORTA,GPIO_PIN3,7);
	///////////////////////////////////////////////////////////////////////
	/*6-MUSART Initialization*/
	USART_InitType usart_init={115200,USART_MODE_8BIT,USART_STOP_BIT_1,DISABLE,USART_EVEN_PARITY,
			USART_TX_RX,USART_OVER_SAMPLING_16};
	MUSART_vInit(&usart_init,USART2);
	///////////////////////////////////////////////////////////////////////
	TIM1_ConfigType TIM1_Config={Upcounter,CH1,NoPrescaler,Input_TI1,7};
	TIM1_vInit(&TIM1_Config);
	///////////////////////////////////////////////////////////////////////
	/*7- Ultrasonic Initialization*/
	Ultrasonic_vInit();

	///////////////////////////////////////////////////////////////////////

	u16 Distance_Ultrasonic=0;

	while(1){

		

		Distance_Ultrasonic = Ultrasonic_Get_Distance();


		if((Distance_Ultrasonic < 100) && (Distance_Ultrasonic >= 50)){

			MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN6,GPIO_HIGH);
						MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN5,GPIO_LOW);
			MUSART_vTransmitByteSynch(USART2,START_BYTE);
			MUSART_vTransmitByteSynch(USART2,CHECK_BYTE_1);
			MUSART_vTransmitByteSynch(USART2,CHECK_BYTE_2);
			MUSART_vTransmitByteSynch(USART2,FAR_DATA);
			MUSART_vTransmitByteSynch(USART2,END_BYTE);
		}
		else if((Distance_Ultrasonic < 50) && (Distance_Ultrasonic >= 30)){
		
			MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN6,GPIO_HIGH);
			MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN5,GPIO_HIGH);
			MUSART_vTransmitByteSynch(USART2,START_BYTE);
			MUSART_vTransmitByteSynch(USART2,CHECK_BYTE_1);
			MUSART_vTransmitByteSynch(USART2,CHECK_BYTE_2);
			MUSART_vTransmitByteSynch(USART2,SEMI_FAR_DATA);
			MUSART_vTransmitByteSynch(USART2,END_BYTE);
		}
		else if((Distance_Ultrasonic < 30) && (Distance_Ultrasonic >= 15)){
		
			MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN6,GPIO_LOW);
			MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN5,GPIO_HIGH);
			MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN5,GPIO_HIGH);
			MUSART_vTransmitByteSynch(USART2,START_BYTE);
			MUSART_vTransmitByteSynch(USART2,CHECK_BYTE_1);
			MUSART_vTransmitByteSynch(USART2,CHECK_BYTE_2);
			MUSART_vTransmitByteSynch(USART2,NEAR_DATA);
			MUSART_vTransmitByteSynch(USART2,END_BYTE);
		}
		else if((Distance_Ultrasonic < 15)){
		
			MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN6,GPIO_LOW);
			MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN5,GPIO_LOW);
			MUSART_vTransmitByteSynch(USART2,START_BYTE);
			MUSART_vTransmitByteSynch(USART2,CHECK_BYTE_1);
			MUSART_vTransmitByteSynch(USART2,CHECK_BYTE_2);
			MUSART_vTransmitByteSynch(USART2,VERY_NEAR_DATA);
			MUSART_vTransmitByteSynch(USART2,END_BYTE);
		}
		else{
			MUSART_vTransmitByteSynch(USART2,START_BYTE);
			MUSART_vTransmitByteSynch(USART2,CHECK_BYTE_1);
			MUSART_vTransmitByteSynch(USART2,CHECK_BYTE_2);
			MUSART_vTransmitByteSynch(USART2,GARBAGE);
			MUSART_vTransmitByteSynch(USART2,END_BYTE);

		}
	}




}
