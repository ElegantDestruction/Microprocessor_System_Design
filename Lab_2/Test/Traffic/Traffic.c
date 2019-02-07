/*
 * Traffic.c
 *
 * Created: 12/4/2013 3:03:18 PM
 *  Author: UW-STOUT
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>

//CEE-345 Microprocessor System Design
//This program is a traffic lights controller
//PORTB is connected to LEDs on STK-600

//#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
//tab array stores RGY Traffic Lights data
//char tab[] PROGMEM = {0x0c,0x14,0x04,0x21,0x22,0x20};

const uint8_t tab[] PROGMEM = {0x0c,0x14,0x04,0x21,0x22,0x20};
int led=0x0c;
int i,j;



int main (void)
{
	DDRB=0xff;
	PORTB=~led;  //inverted due to low enabled LEDs on STK-600 board
	while(1) // infinite while loop
	{
		//read traffic lights data from memory location that stores
		//the first byte in tab array
		//see pgmspace.h for the definition of pgm_read_byte
		
		led=pgm_read_byte(&tab[0]);
		PORTB=~led;
		
		_delay_ms(4000);
		for(i=0;i<5;i++)
		{
			for (j=0;j<2;j++)
			{
				led=pgm_read_byte(&tab[j+1]);
				PORTB=~led;
				
				_delay_ms(400);
			}
		}
		led=pgm_read_byte(&tab[3]);
		PORTB=~led;
		
		_delay_ms(4000);
		for(i=0;i<5;i++)
		{
			for (j=0;j<2;j++)
			{
				led=pgm_read_byte(&tab[j+4]);
				PORTB=~led;
				
				_delay_ms(400);
			}
		}
	}
}





