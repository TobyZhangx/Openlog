/*
 * Openlog_all.c
 *
 * Created: 2023/2/24 13:33:00
 * Author : tbz
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Tool.h"
#include "Task1TurnOnLed.h"
#include "Task2BlinkLed.h"
#include "Task3UartCommunication.h"
									
int main(void)
{
	/* Task1: turn On D1 D2 */
	//TurnOnD1AndD2();
	
	/* Task2: Blink D1, 800ms On, 500ms Off */
	//Task2Method1: use lib function _delay_ms <util/delay.h>
	//blink_led_method1(800, 500);
	
	//Task2Method2: use Timer1/Interrupt
	//blink_led_method2();
	
	/* Task3: Communication by USART */
	uart_communication();
	
	return 0;
}

