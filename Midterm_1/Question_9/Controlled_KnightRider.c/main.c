/*
 * Exercise_1.c
 *
 * Created: 2/6 2:27:46
 * Author : Student
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

//Assume Switches are on PORTD*********


//Function to scan button input and return status value
int scan_buttons(){
	//Check to see if SW1 is pressed
	if (PIND & (1<<PD1) == 1){
		
		//Check to see if SW0
		if (PIND & (1<<PD0) == 1){
			_delay_ms(300);			//Wait for switch debounce
			//Check again if both SW0-1 are pressed, and return pattern 2 if so
			if((PIND & (1<<PD1) == 1) & (PIND & (1<<PD0) == 1)){
				return 2;
			}
		}
		//If SW1 was pressed, but Sw0 wasn't
		else {
			_delay_ms(300);			//Wait for switch debounce
			//Double check switch press after debounce, return pattern 1 if so
			if (PIND & (1<<PD1) == 1){
				return 1;
			}
		}
	}
	//If we get here, neither switch was pressed, so return pattern 0 (Default)
	else {
		return 0;
	}
}



int main(void)
{
	//Declare Variables
	int led = 1;
	int flag = 1;
	int pattern = 0;
	
	//Set DDRB so LEDs are out
	DDRB = 0xff;
	
	//Set up DDRD so Switches are input
	DDRD = 0x00;		//Makes second pin of DDRD input
	
	if (pattern == 1){	//If situation where sw1 is 1 and sw0 is 0
		led = 1;
		do {
		
			//Check button values
			pattern = scan_buttons();
		
			//Set the output equal to ~led
			PORTB = ~led;
		
			//Detect shift direction
			if (flag){
				led <<= 1;		//Shift left once
			
				//Detect if reached 256
				if (led==256){
					flag = 0;
					led=led/4;		//Grab first two bits of led to restart at "10"
				}
			}
			else{
				led >>= 1;		//Shift right once
			
				//Detect if reached 1
				if (led == 1){
					flag = 1;
				}
			}
			_delay_ms(200);
		
		} while (pattern == 1);
	}
	
	//If the situation where neither sw1-0 are pressed
	else if (pattern == 0){
		led = 1;
		do {
			
			//Scan for button input to continue operation
			pattern = scan_buttons();
			
			PORTB = ~led;
			led <<= 1;		//Shift left once
			if (led==256){
				led = led/4;
			}
		} while(pattern == 0);	
	}
	
	//If the situation where both sw1-0 are pressed
	else if (pattern == 2){
		led = 256;
		do {
			
			//Scan for button input to continue
			pattern = scan_buttons();
			
			PORTB = ~led;
			led >>= 1			//Right shift once
			if(led == 1){
				led = 256;
			}
		} while(pattern == 2);
	}
	
	return 0;
}



