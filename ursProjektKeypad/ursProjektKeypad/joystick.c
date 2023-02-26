/*
 * CFile1.c
 *
 * Created: 23.2.2023. 18:25:51
 *  Author: Lucija
 */
#define F_CPU 7372800UL
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "RandomLed.h"


int check_direction(void) {
	DDRD = 0xf0;
	
	while(1) {
			if(PIND & _BV(7))
			{
				return 1; 
			}

			else if(PIND & _BV(6))
			{
				return 2;
			}
			else if(PIND & _BV(5))
			{
				return 3;
				
			}
			else if(PIND & _BV(4))
			{
				return 3;
				
			}
	}

}

