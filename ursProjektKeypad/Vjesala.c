/*
 * Vjesala.c
 *
 * Created: 3.2.2023. 20:12:57
 *  Author: Lucija
 */ 

#define F_CPU 7372800UL

#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#include "keyboard.h"
#include "joystick.h"

#define PRT	PORTD
#define DDR	DDRD
#define PIN	PIND



char words[][14]={"UGRADBENI", "ATMEGA", "PROJEKT", "SENZORI", "RITEH", "PROGRAMER", "RIJEKA", "PROTEUS", "ASEMBLER", "KUTIJA" };
//char words[][14]={"ABC", "DEF"};
char abc[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','R','S','T','U','V','Z'};
char leftRight[10]="<   >";
char word[16];
char lines[16];

int pos=0;
int correct=0;
int wrong=3;
int flag=0;

void gameOver() {
	lcd_clrscr();
	lcd_puts("Game over");
}

void win() {
	lcd_clrscr();
	lcd_puts("Pogodili ste!");
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
	lcd_gotoxy(4,1);
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
			flag = 1;
		}
		
	}
	mainScreen();
	if(flag){
		return;
	}
	wrong_letter();
	wrong--;
	wrong_letter();
	mainScreen();
	
}

void letter( int direction) {
	if(direction==1) {
		pos-=1;
		if(pos==-1) {
			pos=21;
		}
	}else if(direction==2) {
		pos+=1;
		if(pos==22) {
			pos=0;
		}
	} 
	
	lcd_gotoxy(2,0);
	leftRight[2]=abc[pos];
	lcd_putc(leftRight[2]);
	_delay_ms(200);
	
	if(direction==3) {
		//korisnik je odabrao letter
		flag = 0;
		check(abc[pos]);
		
	}
	
}

void startVjesala(void) {
	lcd_clrscr();
	lcd_gotoxy(4,0);
	lcd_puts("VJESALA");
	_delay_ms(2000);
	
	//upute
	
	lcd_clrscr();
	lcd_gotoxy(4,0);
	lcd_puts("UPUTE:");
	_delay_ms(2000);
	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_puts("< pritisni 1");
	lcd_gotoxy(0,1);
	lcd_puts("> pritisni 3");
	_delay_ms(3000);
	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_puts("za odabir slova");
	lcd_gotoxy(0,1);
	lcd_puts("pritisni 2");
	_delay_ms(3000);

	
	int randomNumber = 0;
	//randomNumber=rand() % 10; //dobivamo brojeve od 0 do 9 = indexi unutar words
	
	
	//crtice
	
	
	strcpy(word,words[randomNumber]);
	int length=strlen(word);
	int i;
	
	for( i = 0; i < length; i++) {
		lines[i] = '_';
	}
	lines[i] = '\0';
	
	mainScreen();
	
	
	while(1) {
		
		
		//letter(pressedKey());
		letter(check_direction());
		_delay_ms(400);
		
		
		
	}
	
	
	
	


}
