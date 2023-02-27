#ifndef __DELAY_BACKWARD_COMPATIBLE__
#define __DELAY_BACKWARD_COMPATIBLE__
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Tool.h"
#include "Task2BlinkLed.h"

//Task2Method2:用定时器中断实现
int cnt = 0; // 记录当前LED灯的状态经历了多少个10ms
/*
	@@parameter:
		pin:表示哪个引脚
		light_ten_ms:表示亮灯时间，单位10ms
		off_ten_ms:表示灭灯时间，单位10ms
*/
void change_led_status(int pin, int light_ten_ms, int off_ten_ms)
{
	char temp_val = PORTB | pin;
	if ((temp_val && light_ten_ms == cnt)
		|| (!temp_val && off_ten_ms == cnt))/* 亮灯且已亮灯800ms，或者灭灯且已灭灯500ms时改变灯的状态 */
	{
			IVTBIT(PORTB, pin); //反转引脚值
			cnt = 0;
	}
}

//定时器1计时10ms
ISR(TIMER1_OVF_vect)
{
	//设置定时器1初值
	TCNT1= 0xB1DF;
	cnt++;
	change_led_status(PORTB5, 80, 50); //改变D1（PORTB5）的状态	
}

void init_timer1(unsigned short tcnt1_init_value)
{
	/* 定时器1使用正常模式 */
	TCCR1A |= (0<<WGM11)|(0<<WGM10);
	TCCR1B |= (0<<WGM13)|(0<<WGM12);
	
	TCCR1B |= (0<<CS10)|(1<<CS11)|(0<<CS12); //对16MHz时钟频率进行8分频
	TIMSK1 |= (1<<TOIE1); //启用定时器/计数器1中断	
	TCNT1 = tcnt1_init_value; //设置定时器1初值
	SREG |= (1 << 7); //开启全局中断
	
	return;
}

void blink_led_method2(void)
{
	CLRBIT(DDRB, PORTB5);//PORTB5设为输出引用
	
	init_timer1(0xB1DF);//定时器1定时10ms，计数初值设为0xB1DF

	while(1);

	return;
}

//Task2Method1:使用_delay_ms实现
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