#define F_CPU 7372800UL
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "RandomLed.h"
#define TOP_OF_TIMER 28800
int tmpSecondsLed = 0;

int randNumber()
{
	int num = 0;
	num = TCNT0 % 4;
	return num;
}
void check_activity(int *punti, int *ledOn, int brLedice)
{
	if(*ledOn > 1)
	PORTC ^= _BV(3 - *ledOn);
	else{
		PORTC ^= _BV(7 - *ledOn);
	}
	if(brLedice == *ledOn)
	{
		(*punti)++;
	}
	else{
		lcd_clrscr();
		lcd_gotoxy(4, 0);
		lcd_puts("Pogresno");
		_delay_ms(2000);
		lcd_clrscr();
		lcd_gotoxy(4, 0);
		lcd_puts("        ");
	}
	
	_delay_ms(3);
	while((PIND & _BV(7 - brLedice)));
	*ledOn = randNumber();
	if(*ledOn > 1)
	PORTC ^= _BV(3 - *ledOn);
	else{
		PORTC ^= _BV(7 - *ledOn);
	}
	return;
}
void randomLed(int *seconds)
{
	lcd_clrscr();
	lcd_gotoxy(3,0);
	lcd_puts("RANDOM LED");
	_delay_ms(2000);
	
	//upute
	lcd_clrscr();
	_delay_ms(2000);
	lcd_clrscr();
	lcd_gotoxy(4,0);
	lcd_puts("UPUTE:");
	_delay_ms(2000);
	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_puts("Pomici joystick prema");
	lcd_gotoxy(0,1);
	lcd_puts("upaljenoj ledici.");
	_delay_ms(3000);
	DDRC = 0xff;
	PORTC = 0xff;
	tmpSecondsLed = *seconds;
	lcd_clrscr();
	int gameOn = 1;
	int ledOn = 0;
	int punti = 0;
	PORTC ^= _BV(7 - ledOn);
	sei();
	while(*seconds < tmpSecondsLed + 40){
		
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
			lcd_gotoxy(0, 0);
			lcd_puts("Bodovi:");
			lcd_putc('0' + (punti / 10));
			lcd_putc('0' + (punti % 10));
			
			lcd_gotoxy(0, 1);
			lcd_puts("Vrijeme:");
			lcd_putc('0' + ((*seconds - tmpSecondsLed) / 10));
			lcd_putc('0' + ((*seconds - tmpSecondsLed) % 10));
		}
	}
	lcd_clrscr();
	lcd_gotoxy(0, 0);
	

	if(ledOn > 1)
	PORTC ^= _BV(3 - ledOn);
	else{
		PORTC ^= _BV(7 - ledOn);
	}
	lcd_puts("Vrijeme isteklo!");
	_delay_ms(2000);
	lcd_clrscr();
	lcd_gotoxy(1, 0);
	lcd_puts("Bodovi:");
	lcd_gotoxy(0, 1);
	lcd_putc('0' + (punti / 10));
	lcd_putc('0' + (punti % 10));
	_delay_ms(4000);
	gameOn = 0;
	
}