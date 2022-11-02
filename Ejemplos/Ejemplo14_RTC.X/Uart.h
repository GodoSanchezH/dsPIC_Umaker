/* 
 * File:   Uart.h
 * Author: HP
 *
 * Created on 8 de octubre de 2022, 05:02 PM
 */

#ifndef UART_H
#define	UART_H

#include <stdint.h>

void Uart_Init(uint32_t Baudios);
void Uart_TX_Char(char c);
void Uart_TX_String(char *str);

#endif	/* UART_H */

