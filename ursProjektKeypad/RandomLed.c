#define F_CPU 7372800UL
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "RandomLed.h"
#define TOP_OF_TIMER 28800

int seconds = 0;
ISR(TIMER1_COMPA_vect) {
	seconds++;
}


int randNumber()
{
	int num = 0;
	num = TCNT0 % 4;
	return num;
}
void check_activity(int *punti, int *ledOn, int brLedice)
{
	PORTA ^= _BV(7 - *ledOn);
	if(brLedice == *ledOn)
	{
		(*punti)++;
	}
	else{
		lcd_gotoxy(4, 0);
		lcd_puts("Pogresno");
		_delay_ms(2000);
		lcd_gotoxy(4, 0);
		lcd_puts("        ");
	}
	
	_delay_ms(3);
	while((PIND & _BV(7 - brLedice)));
	*ledOn = randNumber();
	PORTA ^= _BV(7 - *ledOn);
	return;
}
void randomLed(void)
{

	lcd_clrscr();
	int gameOn = 1;
	int ledOn = 0;
	int punti = 0;
	PORTA ^= _BV(7 - ledOn);
	sei();
	while(gameOn){
		if(seconds == 40)
		{
			lcd_clrscr();
			lcd_gotoxy(0, 0);
			lcd_puts("Vrijeme isetklo!");
			lcd_gotoxy(0, 1);
			lcd_putc('0' + (punti / 10));
			lcd_putc('0' + (punti % 10));
			gameOn = 0;
			_delay_ms(500);
		}
		else{
			if((PIND & _BV(7)) && gameOn)
			{
				check_activity(&punti, &ledOn, 0);
			}
			
			else if((PIND & _BV(6)) && gameOn)
			{
				check_activity(&punti, &ledOn, 1);
			}
			else if((PIND & _BV(5)) && gameOn)
			{
				check_activity(&punti, &ledOn, 2);
				
			}
			else if((PIND & _BV(4)) && gameOn)
			{
				check_activity(&punti, &ledOn, 3);
				
			}
			if(gameOn){
				lcd_gotoxy(1, 1);
				lcd_putc('0' + ledOn);
				lcd_puts("  ");
				lcd_putc('0' + (punti / 10));
				lcd_putc('0' + (punti % 10));
				lcd_puts("  ");
				lcd_putc('0' + (seconds / 10));
				lcd_putc('0' + (seconds % 10));
			}
		}
	}
}