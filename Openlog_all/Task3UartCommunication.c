#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Tool.h"
#include "Task2BlinkLed.h"
#include "Task3UartCommunication.h"

int cnt1 = 0; // 记录当前经历了多少个1s

void uart_send_char(char data)
{
    while (!(UCSR0A & (1<<UDRE0)));//检测发送buffer是否为空
    UDR0 = data; 
    return;
}

void uart_send_str(char str[], int len)
{
    int index = 0;
    while (index < len)
    {
        uart_send_char(str[index]);
        index++;    
    }
    return;
}

void init_uart(void)
{
    //RXEN0/TXEN0:开启接收、发送使能
    UCSR0B |= (1<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02);

    //设为以下模式：异步、不校验、1位停止位、8位数据位
    UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	
	/*
		波特率设置为38400，
		按以下公式计算UBBR0
			UBBR0 = F_CPU/(16*BaudRate) - 1
	*/
	UBRR0H = 0x00;
	UBRR0L = 0x19;
	
	return;
}

char data1 = 0xAA;
char data2[11] = {'h','e','l','l','o',' ','w','o','r','l','d'};

ISR(TIMER1_OVF_vect)
{
    //设置定时器1初值，定时1s
    TCNT1 = 0x0BDB;
    cnt1++; 
}

void send_data(void)
{
	init_uart();//初始化UART寄存器
	init_timer1(0x0BDB, FREQUENCY_DIVISION_256); //定时器1定时1s，计数初值设为0x0BDB, 256分频
	SREG |= (1<<7);//开启全局中断
 
	while(1)
    {
        if (1 == cnt1)
        { 
            CLRBIT(PORTB, PORTB5);//灭灯
        }            
        if (10 == cnt1) //每十秒发送一次
        {
            //uart_send_char(data1);
            uart_send_str(data2, 11);//亮灯
            SETBIT(PORTB, PORTB5);
            cnt1 = 0;   
        }
    }
	return;
}

//Task3: 实现UART通信
void uart_communication(void)
{
    SETBIT(DDRB, DDB5);//PORTB5引脚设为输出引脚
    CLRBIT(PORTB, PORTB5); //PORTB5引脚设为低电平
    
    send_data();
    return;
}
