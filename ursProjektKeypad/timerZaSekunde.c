#define F_CPU 7372800UL
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "lcd.h"
#define TOP_OF_TIMER 28800

int seconds = 0;
ISR(TIMER1_COMPA_vect) {
	seconds++;
}

int main(void)
{
	
	DDRB|=(1<<PB3);
	TCCR0 = _BV(WGM01) | _BV(WGM00) | _BV(CS01) | _BV(COM01);
	OCR0 = 100;
	
	TIMSK |= _BV(OCIE1A);
	TCCR1B |= _BV(CS12) | _BV(WGM12);
	OCR1A = TOP_OF_TIMER;
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	
	
	sei();

	while (1){
		char c[3];
		c[1] = '0' + (seconds % 10);
		c[0] = '0' + (seconds / 10) % 10;
		c[2] = '\0';
		
		lcd_gotoxy(4, 0);
		lcd_puts(c);
		
	}
}