#include "uart.h"

void UART_Init(void)		//������9600
{
	SCON = 0X50;	//���ڹ�����ʽ1
	TMOD |= 0X20;	//��ʱ��1������ʽ2 ������8λ�Զ�����ģʽ, ���ڲ���������
	TH1 = 0XFD;		//���ڲ�����9600
	TL1 = 0XFD;
	ET1 = 0; //��ֹ��ʱ��1�ж�
	TR1 = 1; //������ʱ��1
	EA = 1;  //���������ж�
	ES = 1;  //���ж�
}
void UART_SendChar(char date)//���͵����ַ�
{
	ES = 0;
	TI=0;
    SBUF=date;        // �������� --> SBUF�������ݼĴ���
	while(!TI);		  // �ȴ����ݷ������
	TI=0;			  // ������ͱ�־
	ES = 1;
}
void UART_SendString(char *p)//�����ַ�������
{
	while(*p != NULL)
	{
		UART_SendChar(*p++);
	}
}
//�жϽ�������
unsigned char recvdata[16];  //�ش�������,����Ϊ16
unsigned char recvcount = 0;
extern unsigned int timeuart[2];//ʱ��Ƭ���жϴ��������Ƿ�������
void Uart1() interrupt 4
{                            
	unsigned char a;
	if (RI==1)
	{
		a=SBUF;     //��������
		RI=0;       //��λ�ж������־,�������ݺ���1
		recvdata[recvcount++] = a;//���浽������
		recvdata[recvcount] = '\0';//���浽������
		timeuart[0] = 0;//���յ�1���ֽڣ����1�α�־λ
	}
}
/*
������������
datalen -- ���յ����ݵĳ���
*/
void Uart_DataAliy(void)
{
	
}

