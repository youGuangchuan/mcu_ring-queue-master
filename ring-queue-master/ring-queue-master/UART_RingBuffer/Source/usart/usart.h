#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h" 
#include "stdio.h" 
#include "ringQueue.h"

#define RING_BUF_SIZE   128

extern RQ uart1_que;
extern uint8_t uart1_buf[RING_BUF_SIZE];

void usart_init(u32 bound);
void usart_sendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void usart_sendString( USART_TypeDef * pUSARTx, char *str);

#endif //__USART_H


