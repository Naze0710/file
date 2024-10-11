#include "uart.h"

void UART_Init(void)		//波特率9600
{
	SCON = 0X50;	//串口工作方式1
	TMOD |= 0X20;	//定时器1工作方式2 工作于8位自动重载模式, 用于产生波特率
	TH1 = 0XFD;		//串口波特率9600
	TL1 = 0XFD;
	ET1 = 0; //禁止定时器1中断
	TR1 = 1; //启动定时器1
	EA = 1;  //启动接收中断
	ES = 1;  //打开中断
}
void UART_SendChar(char date)//发送单个字符
{
	ES = 0;
	TI=0;
    SBUF=date;        // 发送数据 --> SBUF串口数据寄存器
	while(!TI);		  // 等待数据发送完毕
	TI=0;			  // 清除发送标志
	ES = 1;
}
void UART_SendString(char *p)//发送字符串函数
{
	while(*p != NULL)
	{
		UART_SendChar(*p++);
	}
}
//中断接收数据
unsigned char recvdata[16];  //回传的数组,长度为16
unsigned char recvcount = 0;
extern unsigned int timeuart[2];//时间片，判断串口数据是否接收完成
void Uart1() interrupt 4
{                            
	unsigned char a;
	if (RI==1)
	{
		a=SBUF;     //接收数据
		RI=0;       //复位中断请求标志,接收数据后置1
		recvdata[recvcount++] = a;//保存到缓存区
		recvdata[recvcount] = '\0';//保存到缓存区
		timeuart[0] = 0;//接收到1个字节，清除1次标志位
	}
}
/*
用来解析数据
datalen -- 接收到数据的长度
*/
void Uart_DataAliy(void)
{
	
}

