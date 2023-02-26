/*
 * CFile1.c
 *
 * Created: 22.2.2023. 18:53:24
 *  Author: Lucija
 */ 

#include <avr/io.h>

#define KEY_PRT 	PORTA
#define KEY_DDR		DDRA
#define KEY_PIN		PINA

#define keyboard PORTA

unsigned char colStatus, rowStatus;

uint16_t rowMask = 0x0F;
uint16_t columnMask = 0x0F;

unsigned char keypad[4][4] = {{'A','1','2','3'},
{'B','4','5','6'},
{'C','7','8','9'},
{'D','*','0','#'}};

 char pressedKey() {
	 
	 //prva 4 pina treba postaviti na 1, a druga 4 na 0 -> stupci i redovi
	 KEY_DDR = 0xF0;
	 KEY_PRT = 0xFF;
	 

		 
		 //provjera dal je pritisnuta tipka, u kojem redu?
		 
		 //slucaj: red 0
		 KEY_PRT=0xEF;  //11101111 -> red 0
		 colStatus = KEY_PIN & columnMask;
		 if(colStatus != 0x0F) { // npr C4C3C2C1=1110 to znaci da je pritisnuta tipka u prvom stupcu
			 rowStatus = 0;
			 goto rows;
		 }
		 //slucaj:red 1
		 KEY_PRT=0xDF;  //11011111 -> red 1
		 colStatus = KEY_PIN & columnMask;
		 if(colStatus != 0x0F) {
			 rowStatus = 1;
			 goto rows;
		 }
		 //slucaj:red 2
		 KEY_PRT=0xBF;  //10111111 -> red 2
		 colStatus = KEY_PIN & columnMask;
		 if(colStatus != 0x0F) {
			 rowStatus = 2;
			 goto rows;
		 }
		 //slucaj:red 3
		 KEY_PRT=0x7F;  //01111111 -> red 3
		 colStatus = KEY_PIN & columnMask;
		 if(colStatus != 0x0F) {
			 rowStatus = 3;
			 goto rows;
		 }
		 
		 //provjera u kojem stupcu je pritisnuta tipka
		 rows:;
		 if(colStatus == 0x0e) {
			 //1110 -> stupac 0
			 return keypad[0][rowStatus];
			 } else if(colStatus == 0x0d) {
			 //1101 -> stupac 1
			 return keypad[1][rowStatus];
			 } else if(colStatus == 0x0b) {
			 //1011 -> stupac 2
			 return keypad[2][rowStatus];
			 } else if(colStatus == 0x07) {
			 //0111 -> stupac 3
			 return keypad[3][rowStatus];
		 }

	 return '/';
 }