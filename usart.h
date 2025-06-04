/*
 * usart.h
 *
 *  Created on: 20 May 2025
 *      Author: JonathanStorey
 */
#include "em_usart.h"

#ifndef USART_H_
#define USART_H_

void usart_init(void);
void put_char(char c, int);
void print_string(const char *str, int);
char USART_ReceiveChar(USART_TypeDef *usart);

#endif /* USART_H_ */
