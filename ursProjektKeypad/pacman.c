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
int red1dots[10];
int red2dots[10];
int end1, end2;
char pacman = '<';
char dot = '.';
int posPacmanx = 0;
int posPacmany = 0;
int prevPacmanx = 0;
int prevPacmany = 0;
int score = 0;
int tmpSeconds = 0;


void pokaziBodove() {
	lcd_clrscr();
	lcd_gotoxy(0, 0);
	lcd_puts("Vasi bodovi: ");
	
		lcd_putc('0' + (score / 10));
		lcd_putc('0' + (score % 10));
}

void gameOverPacman() {
	lcd_clrscr();
	lcd_puts("Vrijeme je isteklo");
	
	_delay_ms(1000);
	pokaziBodove();
	_delay_ms(3000);
	return;
}

void bodovi(int dots1[10], int pacy, int n) {
	for (int i = 0; i < n; i++) {
		if (dots1[i] == pacy){
			red1[dots1[i]] = pacman;
			score++;
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
	
	//bodovi(red1dots, posPacmany, end1, score);
	//bodovi(red2dots, posPacmany, end2, score);
	

	
}

void smjer(char direction) {
	
	
	prevPacmanx = posPacmanx;
	prevPacmany = posPacmany;
	
	if (direction == '4'){
		posPacmany--;
		if (posPacmany == -1)
		{
			posPacmany = 15;
		}
	}
	if (direction == '6'){
		posPacmany++;
		if (posPacmany == 16)
		{
			posPacmany = 0;
		}
	}
	else if (direction == '2'){
		posPacmanx++;
		if (posPacmanx == 2)
		{
			posPacmanx = 0;
		}
	}
	else if (direction == '8'){
		posPacmanx--;
		if (posPacmanx == -1)
		{
			posPacmanx = 2;
		}
	}
	
	
	if ((!posPacmanx) && (direction == '4' || direction == '6')){
		
		red1[posPacmany] = pacman;
		red1[prevPacmany] = '_';
	} else if ((!posPacmanx) && (direction == '2' || direction == '8')) {
		
		red1[posPacmany] = pacman;
		red2[posPacmany] = '_';	
	} else if ((posPacmanx) && (direction == '4' || direction == '6')) {
		
		red2[posPacmany] = pacman;
		red2[prevPacmany] = '_';
	} else if ((posPacmanx) && (direction == '2' || direction == '8')) {
		
		red2[posPacmany] = pacman;
		red1[posPacmany] = '_';
	}
	/*
	lcd_gotoxy(posPacmanx, posPacmany);
	lcd_putc(pacman);
	_delay_ms(200);
	*/
	
	bodovi(red1dots, posPacmany, end1);
	bodovi(red2dots, posPacmany, end2);
	
	mainScreenPacman();

	
}



void startPacman(int *seconds)
{
	
	lcd_clrscr();
	lcd_gotoxy(4,0);
	lcd_puts("Pac-man!");
	_delay_ms(2000);
	
	
	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_puts("Skupi bodove");
	lcd_gotoxy(0,1);
	lcd_puts("u 10 sekundi");
	_delay_ms(2000);
	
	
			
	int i;
	red1[0] = pacman;
	for (i = 1; i < 16; i++){
		red1[i] = '_';
	}
	
	
	red1[i] = '\0';
	int j;
	for (j = 0; j < 16; j++){
		red2[j] = '_';
	}
	red2[j] = '\0';
		
		
	/*lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_putc(pacman);
	_delay_ms(250);*/
		
	int randomNumberx;
	int randomNumbery;
	
	int z = 0;
	int k = 0;

		
		
	for (int i = 0; i < 10; i++){
		
		
		randomNumberx = rand() % 2;
		randomNumbery = rand() % 15 + 1;

		
		if (!randomNumberx){
			
			red1[randomNumbery] = dot;
			red1dots[z] = randomNumbery;
			z++;
			
		} else if (randomNumberx) {
			
			red2[randomNumbery] = dot;
			red2dots[k] = randomNumbery;
			k++;
			
		}
	}
	
	//red1dots[z] = '\0';
	//red2dots[k] = '\0';
	
	end1 = z;
	end2 = k;
		
		
	mainScreenPacman();

		tmpSeconds = *seconds;
	
    while (*seconds < tmpSeconds + 15) 
    {
		

		smjer(pressedKey());
		_delay_ms(400);
		

    }
	gameOverPacman();
	return;
}