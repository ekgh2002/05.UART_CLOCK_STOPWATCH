/*
 * led.c
 *
 * Created: 2022-08-09 오후 2:39:38
 *  Author: kccistc
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void shiftleftledon(void);
void shiftrightledon(void);
void shiftleftholdledon(void);
void shiftrightholdledon(void);
void fon(void);
void floweron(void);

extern uint32_t nodelay;


int led_command = 0;  //  nothing
//  1: ledalltoggle
//  2: shift_left_led_on
//  3: shift_right_led_on

void init_led()
{
	DDRA = 0xff;
}
int toggle = 0;



void shiftleftledon(void)
{
		for (int i = 0; i<8; i++)
		{
			PORTA = 0x01 << i;
			_delay_ms(300);
		}
		
}

void shiftrightledon(void)
{
	for (int i = 0; i<8; i++)
	{
		PORTA = 0x80 >> i;
		_delay_ms(300);
	}
}

void shiftleftholdledon(void)
{
	PORTA = 0x00;
	for (int i = 0; i<8; i++)
	{
		PORTA |= 0x01 << i;
		_delay_ms(300);
	}
}

void shiftrightholdledon(void)
{
	PORTA = 0x00;
	for (int i = 0; i<8; i++)
	{
		PORTA |= 0x80 >> i;
		_delay_ms(300);
	}
}

void foff(void)
{
	for (int i = 0; i<4; i++)
	{
		PORTA = (0x80 >> i) | (0x01 << i);
		_delay_ms(300);
		
	}
}

void floweron(void)
{
	for (int i = 0; i<4; i++)
	{
		PORTA = (0x10 << i) | (0x08 >> i);
		_delay_ms(300);
	}
}