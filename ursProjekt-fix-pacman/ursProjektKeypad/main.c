/*
 * ursProjektKeypad.c
 *
 * Created: 3.2.2023. 0:04:03
 * Author : Lucija
 */ 
#define F_CPU 7372800UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "lcd.h"
#define TOP_OF_TIMER 28800

#include "Vjesala.h"
#include "RandomLed.h"
#include "pacman.h"
#include "keyboard.h"

int seconds = 0;
//int flag = 0;
/*
use(secondsPacman);
use(secondsRandomLed);
*/
ISR(TIMER1_COMPA_vect) {
	seconds++;
}


void game( char gameNumber) {
	lcd_clrscr();
	lcd_gotoxy(1,0);
	lcd_puts("Odabrali ste:");
	lcd_gotoxy(1,1);
	lcd_puts("igricu broj ");
	lcd_putc(gameNumber);
	
	_delay_ms(2000);
	
	if(gameNumber == '1') {
		//flag = 1;
		startVjesala();
	} else if(gameNumber == '2') {
		//flag = 2;
		
		randomLed(&seconds);
	} else if(gameNumber == '3') {
		//flag = 3;
		
		startPacman(&seconds);
	} else {
		lcd_puts("Odabrali ste nevazeci broj.");
	}
	lcd_clrscr();
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	lcd_puts("Odaberi igricu:");
	_delay_ms(1000);
	
	return;
	
}
		
int main(void) {
	
		//za LCD
		DDRB = _BV(3);
		TCCR0 = _BV(WGM01) | _BV(WGM00) | _BV(CS01) | _BV(COM01);
		OCR0 = 128;
		//brojac sekunda
		TIMSK |= _BV(OCIE1A);
		TCCR1B |= _BV(CS12) | _BV(WGM12);
		OCR1A = TOP_OF_TIMER;
		
		DDRD = 0xf0;
		DDRA = 0xf0;
		PORTA |= 0xf0;
		sei();
		
  /*DDRB = _BV(4);

   TCCR1A = _BV(COM1B1) | _BV(WGM10);
   TCCR1B = _BV(WGM12) | _BV(CS11);
   OCR1B = 128;
*/
   lcd_init(LCD_DISP_ON);
   lcd_clrscr();
   lcd_puts("Odaberi igricu:");
   _delay_ms(1000);


   while(1) {
	   char pressed = pressedKey();
	   if(pressed!='/') {
		 game(pressed);  
	   }
	   
	   _delay_ms(300);
   }
}