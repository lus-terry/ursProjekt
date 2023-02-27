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
#include <string.h>
#include "lcd.h"
#define TOP_OF_TIMER 28800

#include "RandomLed.h"
#include "keyboard.h"
#include "scrollingText.h"
#include "Vjesala.h"
#include "pacman.h"

int seconds = 0;

ISR(TIMER1_COMPA_vect) {
	seconds++;
}


void game( char gameNumber) {
	_delay_ms(1000);
	lcd_clrscr();
	lcd_gotoxy(1,0);
	lcd_puts("Odabrali ste:");
	lcd_gotoxy(1,1);
	
	
	if(gameNumber == '1') {
		lcd_puts("igricu broj ");
		lcd_putc(gameNumber);
		
		_delay_ms(2000);
		startVjesala();
	} else if(gameNumber == '2') {
		lcd_puts("igricu broj ");
		lcd_putc(gameNumber);
		
		_delay_ms(2000);
		seconds = 0;
		randomLed(&seconds);
	} else if(gameNumber == '3') {
		lcd_puts("igricu broj ");
		lcd_putc(gameNumber);
		
		_delay_ms(2000);
		seconds = 0;
		startPacman(&seconds);
	} else {
		lcd_puts("nevazeci broj!");
		
		_delay_ms(3000);
	}
	lcd_clrscr();
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	lcd_puts("Odaberi igricu:");
	_delay_ms(1000);
	
	return;
	
}

void chooseGame() {
	 lcd_clrscr();
	 lcd_gotoxy(0,0);
	 lcd_puts("Odaberi igru: ");
	 _delay_ms(1000);
	 lcd_gotoxy(0,1);
	 lcd_puts("1) POGODI RIJEC");
	 _delay_ms(2000);
	 lcd_clrscr();
	 lcd_gotoxy(0,0);
	 lcd_puts("2) UHVATI LEDICU");
	 _delay_ms(1000);
	 lcd_gotoxy(0,1);
	 lcd_puts("3) CUDOVISTE");
	 


	 while(1) {
		 char pressed = pressedKey();
		 if(pressed!='/') {
			 game(pressed);
		 }
		 
		 _delay_ms(300);
	 }
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
		
   lcd_init(LCD_DISP_ON);
   lcd_clrscr();
   lcd_gotoxy(4,0);
   lcd_puts("ARKADNE");
   lcd_gotoxy(6,1);
   lcd_puts("IGRE");
   _delay_ms(2000);
   lcd_clrscr();
   scrollText("Pripremili:", "Lucija K, Tonino T, Teo V                            ", 0,1);
   _delay_ms(250);
   chooseGame();
    
}
