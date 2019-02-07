/*
 * Exercise_1.c
 *
 * Created: 2/6 2:27:46
 * Author : Student
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
	//Declare Variables
	int led = 1;
	int flag = 1;
	
	//Set DDRB so LEDs are out
	DDRB = 0xff;
	
	//Create do-while loop
	do {
		
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
		
    } while (1);
	
	return 0;
}

