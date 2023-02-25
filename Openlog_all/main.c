/*
 * Openlog_all.c
 *
 * Created: 2023/2/24 13:33:00
 * Author : tbz
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//#define F_CPU	16000000UL s(��util/delay.h���޸������)

#define turn_on(PORT, n)     PORT |= (1 << n)
#define turn_off(PORT, n)    PORT &= ~(1 << n)

void TurnOnD1AndD2(void);
void BlinkLedD1_Method2(void);

/* Task1: ����D1��D2 */
void TurnOnD1AndD2(void)
{
	turn_on(PORTB, PORTB5);
	turn_on(PORTD, PORTD5);
	return;
}

//Task2Method1:ʹ��_delay_msʵ��
#define BlinkLedD1_Method1(OnTimeMs, OffTimeMs) \
{												\
	while(1)									\
	{											\
		turn_on(PORTB, PORTB5);					\
		_delay_ms(OnTimeMs);					\
		turn_off(PORTB, PORTB5);				\
		_delay_ms(OffTimeMs);					\
	}											\
}												\

//Task2Method2:�ö�ʱ���ж�ʵ��
int cnt = 0; // ��¼��ǰLED�Ƶ�״̬�����˶��ٸ�10ms
char bLedLight = 0; // ��ǰLED��״̬��0�������1�������
//��ʱ��1��ʱ10ms
ISR(TIMER1_OVF_vect)
{
	TCNT1H = 0xB1;
	TCNT1L = 0xDF;
	cnt++;
}
void BlinkLedD1_Method2(void)
{
	TCCR1B |= (0<<CS10)|(1<<CS11)|(0<<CS12);
	TIMSK1 |= (1<<TOIE1);
		
	SREG |= (1 << 7);
	TCNT1H = 0xB1;
	TCNT1L = 0xDF;

	while(1)
	{
		if (bLedLight)/* ������800ms����� */
		{
			if (80 == cnt)
			{
				turn_off(PORTB, PORTB5);
				bLedLight = 0;
				cnt = 0;
			}
		}
		else /* ����500ms������ */
		{
			if (50 == cnt)
			{
				turn_on(PORTB, PORTB5);
				bLedLight = 1;
				cnt = 0;
			}
		}
	}

	return;
}

//Task3: Uart send/receive
/*void SendDataByUart()
{
	
	return;	
}*/

int main(void)
{
	/* Task1: turn On D1 D2 */
	//TurnOnD1AndD2();
	
	/* Task2: Blink D1, 800ms On, 500ms Off */
	//Task2Method1: use lib function _delay_ms <util/delay.h>
	//BlinkLedD1_Method1(800, 500);
	
	//Task2Method2: use Timer1/Interrupt
	BlinkLedD1_Method2();
	
	/* Task3:  */
	//SendDataByUart();
	
	return 0;
}

