/*
 * Vjesala.c
 *
 * Created: 3.2.2023. 20:12:57
 *  Author: Lucija
 */ 

#define F_CPU 7372800UL

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "lcd.h"
#include "keyboard.h"
#include "scrollingText.h"

#define PRT	PORTD
#define DDR	DDRD
#define PIN	PIND


char words[][14]={"UGRADBENI", "ATMEGA", "PROJEKT", "SENZORI", "RITEH", "PROGRAMER", "RIJEKA", "PROTEUS", "ASEMBLER", "KUTIJA" };
char abc[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','R','S','T','U','V','Z'};
char leftRight[10]="<   >";
char word[16];
char lines[16];

int pos=0;
int correct=0;
int wrong=5;
int flag=1;
int correctLetterFlag = 0;

void gameOver() {
	lcd_clrscr();
	lcd_gotoxy(3,0);
	lcd_puts("Game over");
	_delay_ms(2000);
	lcd_gotoxy(0,0);
	lcd_puts("trazena rijec:");
	lcd_gotoxy(0,1);
	lcd_puts(word);
	_delay_ms(2000);
	flag = 0;
}

void win() {
	lcd_clrscr();
	lcd_gotoxy(1,0);
	lcd_puts("Pogodili ste!");
	_delay_ms(2000);
	lcd_gotoxy(0,0);
	lcd_puts("trazena rijec:");
	lcd_gotoxy(0,1);
	lcd_puts(word);
	_delay_ms(2000);
	flag = 0;
}

void mainScreen() {
	lcd_clrscr();
	lcd_gotoxy(1,1);
	lcd_puts(lines);
	
	lcd_gotoxy(1,0);
	leftRight[2]=abc[pos];
	lcd_putc(leftRight[0]);
	lcd_putc(leftRight[2]);
	lcd_putc(leftRight[4]);
	
	_delay_ms(100);
	
	if(!wrong) {
		gameOver();
	}
	if(strstr(lines, word)){
		_delay_ms(1000);
		win();
	}
	
}



void wrong_letter() {
	lcd_clrscr();
	
	lcd_gotoxy(0,0);
	lcd_puts("Preostali zivoti:");
	lcd_gotoxy(1,1);
	for(int i = 0; i < wrong; i++) {
		lcd_puts("<3 ");
	}
	_delay_ms(1500);
	
}


void check(char letter) {
	for(int i = 0; i <strlen(word); i++) {
		if(word[i]==letter) {
			lines[i]=letter;
			correct++;	
			correctLetterFlag=1;
		
		}
		
	}
	mainScreen();
	
	if(correctLetterFlag){
		return;
	}
	
	wrong_letter();
	wrong--;
	wrong_letter();
	mainScreen();
	
}

void letter() {
	if(PIND & _BV(5)) {
	
		pos-=1;
		if(pos==-1) {
			pos=21;
		}
	}else if(PIND & _BV(7)) {
		
		pos+=1;
		if(pos==22) {
			pos=0;
		}
	} 
	
	lcd_gotoxy(2,0);
	leftRight[2]=abc[pos];
	lcd_putc(leftRight[2]);
	_delay_ms(200);
	
	if(PIND & _BV(6) || PIND & _BV(4)) {
		
		//korisnik je odabrao letter
		correctLetterFlag = 0;
		check(abc[pos]);
		
	}
	
}

void startVjesala(void) {
	flag = 1;
	correctLetterFlag = 0;
	wrong=5;
	
	lcd_clrscr();
	lcd_gotoxy(2,0);
	lcd_puts("POGODI RIJEC");
	_delay_ms(2000);
	
	//upute
	lcd_clrscr();
	lcd_gotoxy(4,0);
	lcd_puts("UPUTE:");
	_delay_ms(2000);
	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_puts("za odabir slova:");
	lcd_gotoxy(0,1);
	lcd_puts("  lijevo-desno");
	_delay_ms(2000);
	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_puts("za potvrdu slova:");
	lcd_gotoxy(0,1);
	lcd_puts("  gore/dole");
	_delay_ms(3000);
	lcd_clrscr();


	
	int randomNumber = 0;
	randomNumber = TCNT0 % 10;
	
	
	//crtice
	strcpy(word,words[randomNumber]);
	int length=strlen(word);
	int i;
	
	for( i = 0; i < length; i++) {
		lines[i] = '_';
	}
	lines[i] = '\0';
	
	mainScreen();
	
	
	while(flag) {
		letter();
		
		_delay_ms(50);
		
	}
	
	


}
