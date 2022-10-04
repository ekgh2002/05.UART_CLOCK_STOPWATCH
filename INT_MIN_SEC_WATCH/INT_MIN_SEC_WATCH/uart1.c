/*
 * uart1.c
 *
 * Created: 2022-08-08 오후 9:23:06
 *  Author: sikwon
 */ 

#include "uart1.h"

volatile uint8_t rx1String[64]={0,};
volatile uint8_t rx1ReadyFlag=0;
extern int led_command;

ISR(USART1_RX_vect)
{
	UART1_ISR_Receive();
}

void init_UART1()
{
	UCSR1B |= ((1<<RXEN1) | (1<<TXEN1) | (1<<RXCIE1));
	UCSR1A |= (1<<U2X1);
	UBRR1H = 0;
	UBRR1L = 207; // 9600 buadrate
}


void UART1_transmit(unsigned char data)
{	
	while ( !(UCSR1A & (1<<UDRE1)) );
	UDR1 = data;
}


void UART1_print_string(unsigned char *str)
{
	for (int i=0; str[i]; i++)
	UART1_transmit(str[i]);
}

uint8_t UART1_IsRxD()
{
	return (UCSR1A & (1<<7));
}


void UART1_ISR_Receive()
{
	volatile static uint8_t head=0;
	volatile uint8_t data;
	
	data = UDR1;
UART0_transmit(data);
	// UART0_transmit(data);
	if (data == '\n' || data == '\r')
	{
		if (head) rx1String[head] = '\0';
		head=0;
		rx1ReadyFlag = 1;
	}
	else
	{
		rx1String[head] = data;
		head++;
	}
}

void bt_command_processing()
{
	if (rx1ReadyFlag)			   //  if (rx_ready_flag >= 1)
	{
		rx1ReadyFlag = 0;
		printf("%s\n", rx1String);
		if (strncmp(rx1String, "shiftleftledon", strlen("shiftleftledon")-1)==0)   //  -1 : null 을 빼기위함
		led_command = 1;
		if (strncmp(rx1String, "shiftrightledon", strlen("shiftrightledon")-1)==0)   //  -1 : null 을 빼기위함
		led_command = 2;
		if (strncmp(rx1String, "shiftleftholdledon", strlen("shiftleftholdledon")-1)==0)   //  -1 : null 을 빼기위함, 앞의수가 작으면 -1, 크면 1, 같으면 0
		led_command = 3;
		if (strncmp(rx1String, "shiftrightholdledon", strlen("shiftrightholdledon")-1)==0)   //  -1 : null 을 빼기위함
		led_command = 4;
		if (strncmp(rx1String, "foff", strlen("foff")-1)==0)   //  -1 : null 을 빼기위함
		led_command = 5;
		if (strncmp(rx1String, "floweron", strlen("floweron")-1)==0)   //  -1 : null 을 빼기위함
		led_command = 6;
	}
	switch(led_command)
	{
		case 1:
		shiftleftledon();
		break;
		case 2:
		shiftrightledon();
		break;
		case 3:
		shiftleftholdledon();
		break;
		case 4:
		shiftrightholdledon();
		break;
		case 5:
		foff();
		break;
		case 6:
		floweron();
		break;
	}
}