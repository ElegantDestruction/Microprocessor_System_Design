/*
 * Ex_3.c
 * Created: 1/28 4:27:10
 * Author : Jacob Hillebrand
 */ 

#include <avr/io.h>			// header file defines the pin connections to AVR internal hardware
#define F_CPU 4000000UL		//AVR clock frequency in Hz
#include <util/delay.h>		// header file defines delay function for AVRs


int main(void)
{
	DDRB = 0xFF;	//this make PB0 to PB7 as outputs
	uint8_t holder =1;  //holder of all button values
	
    while (1) 
    {
		PORTB = ~holder;
		holder <<=1;
		
		if (holder == 0)
		holder=1;
		_delay_ms(100);
		
    }
	
	return 0;
}



