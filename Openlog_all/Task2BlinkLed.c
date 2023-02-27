#ifndef __DELAY_BACKWARD_COMPATIBLE__
#define __DELAY_BACKWARD_COMPATIBLE__
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Tool.h"
#include "Task2BlinkLed.h"

//Task2Method2:�ö�ʱ���ж�ʵ��
int cnt = 0; // ��¼��ǰLED�Ƶ�״̬�����˶��ٸ�10ms
/*
	@@parameter:
		pin:��ʾ�ĸ�����
		light_ten_ms:��ʾ����ʱ�䣬��λ10ms
		off_ten_ms:��ʾ���ʱ�䣬��λ10ms
*/
void change_led_status(int pin, int light_ten_ms, int off_ten_ms)
{
	char temp_val = PORTB | pin;
	if ((temp_val && light_ten_ms == cnt)
		|| (!temp_val && off_ten_ms == cnt))/* ������������800ms����������������500msʱ�ı�Ƶ�״̬ */
	{
			IVTBIT(PORTB, pin); //��ת����ֵ
			cnt = 0;
	}
}

//��ʱ��1��ʱ10ms
ISR(TIMER1_OVF_vect)
{
	//���ö�ʱ��1��ֵ
	TCNT1= 0xB1DF;
	cnt++;
	change_led_status(PORTB5, 80, 50); //�ı�D1��PORTB5����״̬	
}

void init_timer1(unsigned short tcnt1_init_value)
{
	/* ��ʱ��1ʹ������ģʽ */
	TCCR1A |= (0<<WGM11)|(0<<WGM10);
	TCCR1B |= (0<<WGM13)|(0<<WGM12);
	
	TCCR1B |= (0<<CS10)|(1<<CS11)|(0<<CS12); //��16MHzʱ��Ƶ�ʽ���8��Ƶ
	TIMSK1 |= (1<<TOIE1); //���ö�ʱ��/������1�ж�	
	TCNT1 = tcnt1_init_value; //���ö�ʱ��1��ֵ
	SREG |= (1 << 7); //����ȫ���ж�
	
	return;
}

void blink_led_method2(void)
{
	CLRBIT(DDRB, PORTB5);//PORTB5��Ϊ�������
	
	init_timer1(0xB1DF);//��ʱ��1��ʱ10ms��������ֵ��Ϊ0xB1DF

	while(1);

	return;
}

//Task2Method1:ʹ��_delay_msʵ��
void blink_led_method1(double on_time_ms, double off_time_ms)
{
	while(1)
	{
		SETBIT(PORTB, PORTB5);
		_delay_ms(on_time_ms);
		CLRBIT(PORTB, PORTB5);
		_delay_ms(off_time_ms);
	}
}