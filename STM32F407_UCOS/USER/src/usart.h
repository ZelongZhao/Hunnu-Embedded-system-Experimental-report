#ifndef	USART_H
#define USART_H

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"

void usart_init(void);
void Usart_SendByte( USART_TypeDef * USARTx, uint8_t ch);
uint8_t Usart_ReceiveByte( USART_TypeDef * USARTx);
void printMynote(void *no_arg);
#endif
