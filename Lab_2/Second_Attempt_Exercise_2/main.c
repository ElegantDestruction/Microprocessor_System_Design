/*
 * Second_Attempt_Exercise_2.c
 *
 * Created: 2/6 4:23:40
 * Author : Student
 */ 


#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

//Declare variables and constants
const uint8_t tab[] PROGMEM = {0x0c,0x14,0x04,0x21,0x22,0x20};
int led = 0x0c;
int i,j;


int main(void)
{
	//Declare output ports and LED assignments
	DDRB = 0xff;
	PORTB = ~led;
	
	//Begin while loop
    while (1) {
		
		//Initial read of array values
		led = pgm_read_byte(&tab[0]);
		PORTB = ~led;
		
		//delay 4 seconds
		_delay_ms(4000);
		
		//Loop through light changes 5 times
		for(i = 0; i < 5; i++){
			
			//Loop to read second and third light values tab[1-2] and display
			for (j = 0; j < 2; j++){
				led = pgm_read_byte(&tab[j+1]);
				PORTB = ~led;
				
				//slight delay between each light transition
				_delay_ms(400);
			}
		}
		
		//Read the 4th light values (tab[3]) and display
		led  = pgm_read_byte(&tab[3]);
		PORTB = ~led;
		
		//4 second delay
		_delay_ms(4000);
		
		//Loop through second set of light changes 5 times
		for (i = 0; i < 5; i++){
			
			//Loop through 5th & 6th light values 
			for (j = 0; j < 2; j++){
				led = pgm_read_byte(&tab[j+4]);
				PORTB = ~led;
				
				//Slight delay between each light transition
				_delay_ms(400);
			}
		}
		
		return 0;
    }
}

