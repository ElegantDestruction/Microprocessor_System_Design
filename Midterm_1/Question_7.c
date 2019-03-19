#define F_CPU 80000000UL
#include <avr/io.h>
#include <util/delay.h>

//PORTD is connected to Switches
//PORTB is connected to LEDs

int main(void){
	//Initialize PORTB
	PORTB = 0x00;
	DDRB = 0xff;
	
	//Initialize PORTD
	PORTD = 0x00;
	DDRD = 0x00;
	
	char base = 0x00;		//0x00 for reference
	char check;				//variable for later use
	
	while (1){
	
	check = PIND;			//Grab input from switches
	
	
	//If there is a switch pressed, delay for a sec to 
	//	check if it really is pressed
	if (check != base){
		delay(20);
		check = PIND;
		//Once debounced, check to see if the end 2 switches
		//	(SW0 and SW1) are pressed. If so, turn on LED0
		if (check != 0x02){
			PORTB = ~(0x01);
		}
		//Else make sure the LEDs are off
		else{
			PORTB = 0xFF;
		}
	}
	//Else make sure the LEDs are off
	else{
		PORTB = 0xFF;
	}
}