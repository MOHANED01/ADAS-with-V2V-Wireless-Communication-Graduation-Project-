
#include"../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES_H.h"

#include "UART_private.h"
#include"UART_interface.h"
#include"UART_config.h"


void (*G_CallbackPtr[3])(void);/*3 callback pointers as this micro have 3 USART*/

void MUSART_vInit(USART_InitType *A_InitStruct,USART_MemMap_t *USARTx)
{

	USARTx->CR1 = 0;
	USARTx->CR1= (A_InitStruct->Oversampling<<MUSART_CR1_OVER8_BIT)|
			(A_InitStruct->DataWidth<<MUSART_CR1_M_BIT)|(A_InitStruct->Parity_Enable<<MUSART_CR1_PCE_BIT)|
			(A_InitStruct->Parity_Selection<<MUSART_CR1_PS_BIT);
	switch(A_InitStruct->TransferDirection)
	{
	case USART_TX_ONLY:
		SET_BIT(USARTx->CR1,MUSART_CR1_TE_BIT); break;
	case USART_RX_ONLY:
		SET_BIT(USARTx->CR1,MUSART_CR1_RE_BIT); break;
	case USART_TX_RX:
		SET_BIT(USARTx->CR1,MUSART_CR1_TE_BIT);
		SET_BIT(USARTx->CR1,MUSART_CR1_RE_BIT); break;
	}
	USARTx->CR2=(A_InitStruct->StopBits<<12);

	switch(A_InitStruct->Oversampling)
	{
	case USART_OVER_SAMPLING_8:
		USARTx->BRR= UART_BRR_SAMPLING8(PCLK, A_InitStruct->BaudRate); break;
	case USART_OVER_SAMPLING_16:
		USARTx->BRR=UART_BRR_SAMPLING16(PCLK, A_InitStruct->BaudRate); break;
	}
	USARTx->SR=0;
	SET_BIT(USARTx->CR1,MUSART_CR1_UE_BIT);
}

void MUSART_vDisable(USART_MemMap_t *USARTx)
{
	CLEAR_BIT(USARTx->CR1,MUSART_CR1_UE_BIT);
}

void MUSART_vTransmitByteSynch(USART_MemMap_t *USARTx ,u8 A_u8Byte)
{
	while(GET_BIT(USARTx->SR,MUSART_SR_TXE_BIT)==0);
	USARTx->DR=A_u8Byte;
	/*to clear flag */
	while(GET_BIT(USARTx->SR,MUSART_SR_TC_BIT)==0)  ;
	CLEAR_BIT(USARTx->SR,MUSART_SR_TC_BIT) ;


}
u8 MUSART_vTransmitByteAsynch(USART_MemMap_t *USARTx ,u8 A_u8Byte)
{
	if(GET_BIT(USARTx->SR,MUSART_SR_TXE_BIT)==1)
	{
		USARTx->DR=A_u8Byte;
		return OK  ;
	}
	else return NOT_OK  ;

}
void MUSART_vTransmitString(USART_MemMap_t *USARTx,u8 *A_ptru8String)
{
	u16 i=0;
	while(A_ptru8String[i]!='\0')
	{
		MUSART_vTransmitByteSynch(USARTx,A_ptru8String[i]);
		i++;
	}
	A_ptru8String[i]='\0';/*to be sure in receiving that i receive all string*/
}

u8 MUSART_u8ReceiveByteSynchNonBlocking(USART_MemMap_t *USARTx)
{
	for(u16 i=0;i<THRESHOLD_VALUE;i++)
	{
		if(GET_BIT(USARTx->SR,MUSART_SR_RXNE_BIT)==1)
		{
			CLEAR_BIT(USARTx->SR,MUSART_SR_RXNE_BIT);/*to clear flag*/
			return USARTx->DR;
		}
	}
	return NOT_OK;
}
void MUSART_ptrReceiveStringSynchNonBlocking(USART_MemMap_t *USARTx ,char* A_u8str )
{
	u8 L_Rx=MUSART_u8ReceiveByteSynchNonBlocking(USARTx);
	u16 L_Counter=0;
	while (L_Rx!=NOT_OK&&L_Rx!='\0')
	{
		A_u8str[L_Counter]=L_Rx;
		L_Counter++;
		L_Rx=MUSART_u8ReceiveByteSynchNonBlocking(USARTx);
	}
	if(L_Rx=='\0')
	{
		A_u8str[L_Counter]='\0';
	}
}
u8 MUSART_u8ReceiveByteSynchBlocking(USART_MemMap_t *USARTx )
{
	while(GET_BIT(USARTx->SR,MUSART_SR_RXNE_BIT)!=1);

	//CLEAR_BIT(USARTx->SR,MUSART_SR_RXNE_BIT);/*to clear flag*/
	return USARTx->DR;

}

void MUSART_vRxSetInterrupt(USART_MemMap_t *USARTx, u8 A_u8Status)
{
	switch(A_u8Status)
	{
	case ENABLE :  SET_BIT(USARTx->CR1,MUSART_CR1_RXNEIE_BIT);break ;
	case DISABLE : CLEAR_BIT(USARTx->CR1,MUSART_CR1_RXNEIE_BIT);break ;
	}
}

u8 MUSART_u8ReadDataRegister(USART_MemMap_t *USARTx)
{
	return USARTx->DR;
}

void MUSART1_vSetCallBack(void (*ptr) (void) )
{
	G_CallbackPtr[0]=ptr;
}
void MUSART2_vSetCallBack(void (*ptr) (void) )
{
	G_CallbackPtr[1]=ptr;
}
void MUSART6_vSetCallBack(void (*ptr) (void) )
{
	G_CallbackPtr[2]=ptr;
}

void USART1_IRQHandler(void)
{
	/* clear all flags */
	USART1 -> SR = 0 ;
	if(G_CallbackPtr[0] != NULL)
	{
		G_CallbackPtr[0]();
	}
}

void USART2_IRQHandler(void)
{
	USART2 -> SR = 0 ;
	if(G_CallbackPtr[1] != NULL)
	{
		G_CallbackPtr[1]();
	}
}

void USART6_IRQHandler(void)
{
	USART6 -> SR = 0 ;
	if(G_CallbackPtr[2] != NULL)
	{
		G_CallbackPtr[2]();
	}
}


