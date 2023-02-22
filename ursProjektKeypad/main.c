/*
 * ursProjektKeypad.c
 *
 * Created: 3.2.2023. 0:04:03
 * Author : Lucija
 */ 
#define F_CPU 7372800UL

#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>

#include "Vjesala.h"
#include "keyboard.h"




void game( char gameNumber) {
	lcd_clrscr();
	lcd_gotoxy(1,0);
	lcd_puts("Odabrali ste:");
	lcd_gotoxy(1,1);
	lcd_puts("igricu broj ");
	lcd_putc(gameNumber);
	
	_delay_ms(2000);
	
	if(gameNumber == '1') {
		startVjesala();
	} else if(gameNumber == '2') {
		
	}
	
}
		
int main(void) {
   DDRD = _BV(4);

   TCCR1A = _BV(COM1B1) | _BV(WGM10);
   TCCR1B = _BV(WGM12) | _BV(CS11);
   OCR1B = 128;

   lcd_init(LCD_DISP_ON);
   lcd_clrscr();
   lcd_puts("Odaberi igricu!");


   while(1) {
	   game(pressedKey());
	   _delay_ms(300);
   }
}

