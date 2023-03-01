#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "Tool.h"
#include "Task1TurnOnLed.h"

/* Task1: µ„¡¡D1°¢D2 */
void TurnOnD1AndD2(void)
{
	SETBIT(PORTB, PORTB5);
	SETBIT(PORTD, PORTD5);
	return;
}