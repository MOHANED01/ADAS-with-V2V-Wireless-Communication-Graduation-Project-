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
	/*2- Enable GPIO peripheral clock for port A and port B */
	MRCC_vEnableClock(RCC_AHB1,RCC_EN_GPIOA);

	MRCC_vEnableClock(RCC_AHB1,RCC_EN_GPIOB);

	/*3- Enable USART2 peripheral clock */
	MRCC_vEnableClock(RCC_APB1,RCC_EN_UART2);
	/*3- Enable FDI peripheral clock */
	MRCC_vEnableClock(RCC_AHB1LP,RCC_EN_FLITFLPEN);
	//////////////////////////////////////////////////////////////////////
	/*LED CONFIGURATIONS*/
	/* RED LED */
	MGPIO_vSetPinMode(GPIO_PORTB,GPIO_PIN0,GPIO_MODE_OUTPUT);
	MGPIO_vSetPinOutputType(GPIO_PORTB,GPIO_PIN0,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTB,GPIO_PIN0,GPIO_OUTSPEED_LOW);
	/* YELLOW LED */
	MGPIO_vSetPinMode(GPIO_PORTB,GPIO_PIN1,GPIO_MODE_OUTPUT);
	MGPIO_vSetPinOutputType(GPIO_PORTB,GPIO_PIN1,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTB,GPIO_PIN1,GPIO_OUTSPEED_LOW);
	/* GREEN LED */
	MGPIO_vSetPinMode(GPIO_PORTA,GPIO_PIN6,GPIO_MODE_OUTPUT);
	MGPIO_vSetPinOutputType(GPIO_PORTA,GPIO_PIN6,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTA,GPIO_PIN6,GPIO_OUTSPEED_LOW);
	/* BLUE LED */
	MGPIO_vSetPinMode(GPIO_PORTA,GPIO_PIN7,GPIO_MODE_OUTPUT);
	MGPIO_vSetPinOutputType(GPIO_PORTA,GPIO_PIN7,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTA,GPIO_PIN7,GPIO_OUTSPEED_LOW);
	///////////////////////////////////////////////////////////////////////
	MGPIO_vSetPinMode(GPIO_PORTA,GPIO_PIN0,GPIO_MODE_OUTPUT);
	MGPIO_vSetPinOutputType(GPIO_PORTA,GPIO_PIN0,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTA,GPIO_PIN0,GPIO_OUTSPEED_LOW);
	///////////////////////////////////////////////////////////////////////
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
	/*5-MUSART Initialization*/

	USART_InitType usart_init={115200,USART_MODE_8BIT,USART_STOP_BIT_1,DISABLE,USART_EVEN_PARITY,
			USART_TX_RX,USART_OVER_SAMPLING_16};
	MUSART_vInit(&usart_init,USART2);
	u8 Dummy=0;


	//MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN7,GPIO_HIGH);


	while(1){

		//		while(Dummy != START_BYTE)
		//		{
		//			Dummy = MUSART_u8ReceiveByteSynchBlocking(USART2);
		//			MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN4,GPIO_HIGH);
		//			MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN5,GPIO_HIGH);
		//			MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN6,GPIO_HIGH);
		//			MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN7,GPIO_HIGH);
		//		}
		Dummy = MUSART_u8ReceiveByteSynchBlocking(USART2);
		if(Dummy == CHECK_BYTE_1)
		{
			if(MUSART_u8ReceiveByteSynchBlocking(USART2) == CHECK_BYTE_2)
			{

				switch(MUSART_u8ReceiveByteSynchBlocking(USART2))
				{
				case FAR_DATA:
					MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN6,GPIO_HIGH);
					MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN7,GPIO_LOW);
					MGPIO_vSetPinValue(GPIO_PORTB,GPIO_PIN0,GPIO_LOW);
					MGPIO_vSetPinValue(GPIO_PORTB,GPIO_PIN1,GPIO_LOW);
					break;

				case SEMI_FAR_DATA:
					MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN6,GPIO_LOW);
					MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN7,GPIO_HIGH);
					MGPIO_vSetPinValue(GPIO_PORTB,GPIO_PIN0,GPIO_LOW);
					MGPIO_vSetPinValue(GPIO_PORTB,GPIO_PIN1,GPIO_LOW);
					break;

				case NEAR_DATA:
					MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN6,GPIO_LOW);
					MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN7,GPIO_LOW);
					MGPIO_vSetPinValue(GPIO_PORTB,GPIO_PIN0,GPIO_HIGH);
					MGPIO_vSetPinValue(GPIO_PORTB,GPIO_PIN1,GPIO_LOW);
					break;

				case VERY_NEAR_DATA:
					MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN6,GPIO_LOW);
					MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN7,GPIO_LOW);
					MGPIO_vSetPinValue(GPIO_PORTB,GPIO_PIN0,GPIO_LOW);
					MGPIO_vSetPinValue(GPIO_PORTB,GPIO_PIN1,GPIO_HIGH);
					break;

				case GARBAGE:
					MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN6,GPIO_LOW);
					MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN7,GPIO_LOW);
					MGPIO_vSetPinValue(GPIO_PORTB,GPIO_PIN0,GPIO_LOW);
					MGPIO_vSetPinValue(GPIO_PORTB,GPIO_PIN1,GPIO_LOW);
					break;
				}
			}
		}




	}

}

