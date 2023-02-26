/*
 * scrollingText.c
 *
 * Created: 26.2.2023. 17:32:40
 *  Author: Lucija
 */ 

#define F_CPU 7372800UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <string.h>
#include "lcd.h"



void scrollText(char firstWord[], char string[], int x, int y) {

	int i, j;
	int k = strlen(string);
	for(i = 0; i < strlen(string); i++) {
		lcd_clrscr();
		lcd_gotoxy(0,0);
		lcd_puts(firstWord);
		lcd_gotoxy(x,y);
		lcd_puts(string);
		for(j = 0; j < k; j++) {
			string[j] = string[j+1];
		}
		

		k--;
		_delay_ms(400);
	}

}

