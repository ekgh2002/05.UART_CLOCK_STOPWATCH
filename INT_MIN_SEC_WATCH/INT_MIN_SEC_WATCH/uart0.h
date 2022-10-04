/*
 * uart.h
 *
 * Created: 2022-08-09 오전 10:47:49
 *  Author: kccistc
 */ 


#ifndef UART0_H_
#define UART0_H_
void init_uart0(void);
void UART0_transmit(uint8_t data);
void pc_command_processing();

extern void shift_left_led_on();
extern void shift_right_led_on();
extern void shift_left_hold_led_on();
extern void shift_right_hold_led_on();
extern void f_off();
extern void flower_on();


//  UART0로부터 1byte가 들어오면 rx(수신) interrupt 발생 되어 이곳으로 들어옴.
//  p278 표 12-3 참조
volatile unsigned char rx_buffer[100];
volatile uint8_t rx_ready_flag = 0;  //  완전한 문장이 들어 왔을때 1로 set 된다.
volatile int i = 0;

#endif /* UART_H_ */