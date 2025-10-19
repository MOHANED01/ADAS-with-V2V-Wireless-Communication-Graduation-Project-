
#ifndef MCAL_UART_UART_INT_H_
#define MCAL_UART_UART_INT_H_
#include"UART_private.h"



typedef struct
{
	u32 BaudRate;/*any number will be written in config.h*/
	u16 DataWidth;/*8 bits or 9 bits*/
	u16 StopBits ;/*1 or 1.5 or 2 or 2.5..this fraction like frequency of the clock (duration of stop bit)*/
	u16 Parity_Enable; /*parity or no parity*/
	u16 Parity_Selection;/*even or odd*/
	u16 TransferDirection;/*TX_ONLY  RX_ONLY  TX_RX*/
	u16 Oversampling;/*this need to detect noise with factor 8 or 16 per 1 bit */
}USART_InitType;


#define OK                        0
#define NOT_OK                    1

#define USART_OVER_SAMPLING_16    0
#define USART_OVER_SAMPLING_8     1

#define USART_TX_ONLY             0
#define USART_RX_ONLY             1
#define USART_TX_RX               2

#define USART_EVEN_PARITY         0
#define USART_ODD_PARITY          1

#define USART_MODE_8BIT		      0
#define USART_MODE_9BIT		      1

#define USART_STOP_BIT_1	      0
#define USART_STOP_BIT_1_OVER_2   1
#define USART_STOP_BIT_2	      2
#define USART_STOP_BIT_3_OVER_2   3

#define    ENABLE			      1
#define    DISABLE			      0

/*you must create a structure of type A_InitStruct have all specs of uart module you want
 * USARTx : which usart you need ex:USART1*/
void MUSART_vInit(USART_InitType *A_InitStruct,USART_MemMap_t *USARTx);

/*to disable USART ...to enable it again must call vInit again */
void MUSART_vDisable(USART_MemMap_t *USARTx);

/*to transmit one byte in synchronous mood*/
void MUSART_vTransmitByteSynch(USART_MemMap_t *USARTx ,u8 A_u8Byte);

/*to transmit one byte in Asynchronous mood*/
u8 MUSART_vTransmitByteAsynch(USART_MemMap_t *USARTx ,u8 A_u8Byte);

/*to transmit string in synchronous mood only*/
void MUSART_vTransmitString(USART_MemMap_t *USARTx,u8 *A_ptru8String);

/*receive byte synchronous but with limited timeout */
u8 MUSART_u8ReceiveByteSynchNonBlocking(USART_MemMap_t *USARTx);

/*receive string synchronous but with limited timeout */
void MUSART_ptrReceiveStringSynchNonBlocking(USART_MemMap_t *USARTx ,char* A_u8str );

/*receive byte synchronous(all system will stop without this byte)*/
u8 MUSART_u8ReceiveByteSynchBlocking(USART_MemMap_t *USARTx );

/*to enable interrupt */
void MUSART_vRxSetInterrupt(USART_MemMap_t *USARTx, u8 A_u8Status);

/*to read data in data register equal to recieve Asynch*/
u8 MUSART_u8ReadDataRegister(USART_MemMap_t *USARTx);

/*these call backs need in receiving in Asynchronous mood */
void MUSART1_vSetCallBack(void (*ptr) (void) );
void MUSART2_vSetCallBack(void (*ptr) (void) );
void MUSART6_vSetCallBack(void (*ptr) (void) );

#endif /* MCAL_UART_UART_INT_H_ */
