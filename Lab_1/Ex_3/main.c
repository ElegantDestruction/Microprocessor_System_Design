/*
 * Ex_3.c
 * Created: 1/28 4:27:10
 * Author : Jacob Hillebrand
 */ 
#define F_CPU 8000000UL		//AVR clock frequency in Hz
#include <avr/io.h>			// header file defines the pin connections to AVR internal hardware
#include <util/delay.h>		// header file defines delay function for AVRs


int main(void)
{
    /* Replace with your application code */
	PORTB = 0xff;
	DDRB = 0xff;	//this make PB0 to PB7 as outputs
	
    while (1) 
    {
		PORTB |= (1<<PB1);
		
		_delay_ms(100);
		PORTB &= ~(1<<PB1);
		_delay_ms(100);
    }
	
	return 0;
}

