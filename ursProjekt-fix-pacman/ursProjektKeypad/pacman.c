#define F_CPU 7372800UL

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "lcd.h"
#include "keyboard.h"


char red1[16];
char red2[16];
int redDots[32];
int end1, end2;
char pacman = 0b11111100;
char dot = 0b10100101;
char path = ' ';
int posPacmanx = 0;
int posPacmany = 0;
int prevPacmanx = 0;
int prevPacmany = 0;
int score = 0;
int tmpSeconds = 0;



void pokaziBodove() {
	lcd_clrscr();
	lcd_gotoxy(0, 0);
	lcd_puts(" Vasi bodovi: ");
	
		lcd_putc('0' + (score / 10));
		lcd_putc('0' + (score % 10));
}

void gameOverPacman() {
	lcd_clrscr();
	lcd_puts("Vrijeme isteklo!");
	
	_delay_ms(2000);
	pokaziBodove();
	_delay_ms(4000);
	return;
}


void newDot(int brojTocke) {
	
	start:
	redDots[brojTocke] = rand() % 31 + 1;
	int randomNumber = redDots[brojTocke];
	
	if (randomNumber < 16 && red1[randomNumber] == path){
		red1[randomNumber] = dot;
		
		} else if (randomNumber >= 16 && red2[randomNumber - 16] == path) {
		red2[randomNumber - 16] = dot;
		
		} else {
		goto start;
	}
	
/*
//  	if (brojTocke >= 16){
//  		red2[redDots[brojTocke] - 16] = path;
//  		} else if (brojTocke < 16){
//  		red1[redDots[brojTocke]] = path;
//  	}
*/


 	if (randomNumber >= 16){
 		red2[redDots[brojTocke] - 16] = dot;
 	} else if (randomNumber < 16){
		red1[redDots[brojTocke]] = dot;
 	}

	
}


void bodovi(int pacy) {
	for (int i = 0; i < 10; i++) {
		if (redDots[i] == pacy){
			score++;								
			newDot(i);
		}
	}
}


void mainScreenPacman() {
	lcd_clrscr();
	lcd_gotoxy(0, 0);
	lcd_puts(red1);
	lcd_gotoxy(0, 1);
	lcd_puts(red2);	
	
	_delay_ms(100);

}

void smjer(char direction) {
	
	
	prevPacmanx = posPacmanx;
	prevPacmany = posPacmany;
	
	if (PIND & _BV(5)){
		direction = '4';
		_delay_ms(3);
		while((PIND & _BV(5)));
		posPacmany--;
		if (posPacmany == -1)
		{
			posPacmany = 15;
		}
	}
	else if (PIND & _BV(7)){
		direction = '6';
		posPacmany++;
		_delay_ms(3);
		while((PIND & _BV(7)));
		if (posPacmany == 16)
		{
			posPacmany = 0;
		}
	}
	else if (PIND & _BV(6)){
		direction = '2';
		posPacmanx++;
		_delay_ms(3);
		while((PIND & _BV(6)));
		if (posPacmanx == 2)
		{
			posPacmanx = 0;
		}
	}
	else if (PIND & _BV(4)){
		direction = '8';
		posPacmanx--;
		_delay_ms(3);
		while((PIND & _BV(4)));
		if (posPacmanx == -1)
		{
			posPacmanx = 2;
		}
	}
	
	
	if ((!posPacmanx) && (direction == '4' || direction == '6')){
		
		red1[posPacmany] = pacman;
		red1[prevPacmany] = path;
	} else if ((!posPacmanx) && (direction == '2' || direction == '8')) {
		
		red1[posPacmany] = pacman;
		red2[posPacmany] = path;	
	} else if ((posPacmanx) && (direction == '4' || direction == '6')) {
		
		red2[posPacmany] = pacman;
		red2[prevPacmany] = path;
	} else if ((posPacmanx) && (direction == '2' || direction == '8')) {
		
		red2[posPacmany] = pacman;
		red1[posPacmany] = path;
	}
	//_delay_ms(200);
	
	if (!posPacmanx) {
		bodovi(posPacmany);
	} else {
		bodovi(posPacmany + 16);		
	}	
		
		mainScreenPacman();

	
}



void startPacman(int *seconds)
{
	posPacmanx = 0;
	posPacmany = 0;
	
	lcd_clrscr();
	lcd_gotoxy(3,0);
	lcd_puts("CUDOVISTE");
	_delay_ms(2000);
	
	//upute
	lcd_clrscr();
	lcd_gotoxy(4,0);
	lcd_puts("UPUTE:");
	_delay_ms(2000);
	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_puts("Nahrani cudoviste");
	lcd_gotoxy(0,1);
	lcd_puts("u 10 sekundi!");
	_delay_ms(2000);
	lcd_gotoxy(0,0);
	lcd_puts("Pomici joystick ");
	lcd_gotoxy(0,1);
	lcd_puts("u smjeru hrane.");
	_delay_ms(3000);
	
	
			
	int i;
	red1[0] = pacman;
	for (i = 1; i < 16; i++){
		red1[i] = path;
	}
	
	
	red1[i] = '\0';
	int j;
	for (j = 0; j < 16; j++){
		red2[j] = path;
	}
	red2[j] = '\0';

		
	int randomNumber;
		
		
	for (int i = 0; i < 10; i++){
		
		
		randomNumber = rand() % 31 + 1;
		if (randomNumber < 16 && red1[randomNumber] == path){
			red1[randomNumber] = dot;
			
		} else if (randomNumber >= 16 && red2[randomNumber - 16] == path) {
		red2[randomNumber - 16] = dot;
			
		} else {
			i--;
			continue;
		}
		
		redDots[i] = randomNumber;
		
		if (randomNumber < 16){
			red1[randomNumber] = dot;
		} else if (randomNumber >= 16) {
			red2[randomNumber - 16] = dot;
		}

	}
		
	mainScreenPacman();

	tmpSeconds = *seconds;
	score = 0;
    while (*seconds < tmpSeconds + 15) 
    {
		

		smjer(pressedKey());
		_delay_ms(2);
		

    }
	gameOverPacman();
	
	if (!posPacmanx) {
		red1[posPacmany] = path;
		} else {
		red2[posPacmany] = path;
	}
	return;
}
