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

int cnt1 = 0; // ��¼��ǰ�����˶��ٸ�1s

void init_uart(void)
{
    UCSR0A = 0x00;
    UCSR0B = 0x00;
    UCSR0C = 0x00;
    
    //RXEN0/TXEN0:�������ա�����ʹ��
    UCSR0B |= (1<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02);

    //��Ϊ����ģʽ���첽����У�顢1λֹͣλ��8λ����λ
    UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	UBRR0H = 0x00;
	UBRR0L = 0x19;
	/*
		����������Ϊ38400��
		�����¹�ʽ����UBBR0
			UBBR0 = F_CPU/(8*BaudRate) - 1
	*/
	
	
	return;
}

unsigned char data1 = 0xAA;
unsigned char data2[11] = {'h','e','l','l','o',' ','w','o','r','l','d'};

ISR(TIMER1_OVF_vect)
{
    //���ö�ʱ��1��ֵ����ʱ1s
    TCNT1 = 0x0BDB;
    cnt1++;
    
    if (1 == cnt1)
    { 
        SETBIT(PORTB, PORTB5);
    }

    if (3 == cnt1) //ÿʮ�뷢��һ��
    {
        CLRBIT(PORTB, PORTB5);
        //unsigned char index = 0;
        while (!(UCSR0A & (1<<UDRE0)));//��ⷢ��buffer�Ƿ�Ϊ��
        UDR0 = data1;
        cnt1 = 0;
            
    }       
}

void send_data(void)
{
	init_uart();//��ʼ��UART�Ĵ���
	init_timer1(0x0BDB, FREQUENCY_DIVISION_256); //��ʱ��1��ʱ1s��������ֵ��Ϊ0x0BDB, 256��Ƶ
	SREG |= (1<<7);//����ȫ���ж�
 
	while(1);
	return;
}

//Task3: ʵ��UARTͨ��
void uart_communication(void)
{
    send_data();
    return;
}
