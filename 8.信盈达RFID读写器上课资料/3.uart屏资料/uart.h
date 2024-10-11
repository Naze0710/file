#ifndef _UART_H_
#define _UART_H_

#include <reg52.h>
#include <stdio.h>

extern unsigned char recvdata[16];  //回传的数组,长度为16
extern unsigned char recvcount;

void UART_Init(void);
void UART_SendChar(char date);
void UART_SendString(char *p);
void Uart_DataAliy(void);

#endif
