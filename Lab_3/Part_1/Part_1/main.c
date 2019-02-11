/*
 * Part_1.c
 *	C version of Lab_3 - Keypad input
 * Created: 2/11 3:03:28
 * Author : Jacob Hillebrand
 */ 
//This exercise is a Keypad-LED blinker program. The LEDs on the STK-600
//blink number of times according to the number pressed on the 
//16-key Digilent keypad. Keys 1,2,3 are implemented in C

//PORTD is connected to Digilent PmodKeypad
//PORTB is connected to LEDs


#include <avr/io.h>
#define F_CPU 4000000UL		//Set clock frequency to 4 MHz
#include <util/delay.h>		//Header file allowing a delay function
#include <stdlib.h>			//imports the C standard library

char key_code[] = {0xE7,0xEE,0xDE,0xBE,0xED,0xDD,0xBD,0xEB,0xDB,0xBB,0x7E,0x7D,0x7B,0x77,0xB7,0xD7};
	
//a delay function for switch debounce
void delay(long value){		
	while(--value);	
}

//Scan function to scan keypad to read key-press
char scan(){
	//Declare necessary variables
	char temp,key,i; 
	
	//Begin the scan loop
	PORTD = 0x0f;
	
	//Make temp == PIND
	do {
		temp = PIND;
	} while (temp != 0x0f);
	
	while (1) {
		for (i = 0; i < 4; i++){
			temp =~(0x80 >> i);		//~(0b1000 0000) = 0b0111 1111
			PORTD = temp;
			key = PIND;
			if (key != temp){
				delay(20);		//delay for the switch debounces
				key = PIND;		//a pressed key is detected and return return its value
				if (key != temp) return (key);		
			}
		}
	}
	
}

//Test if a key was pressed
char gotkey(){
	char temp;		
	int i;
	temp = scan();
	for (i = 0; i <= 15; i++){
		if (temp == key_code[i]) return(i);
	}
	return (16);
}

int main(void)
{
	
	char keys;
	
	//Initialize Port B
	PORTB = 0x00;
	DDRB = 0xFF;
	
	//Initialize Port D
	PORTD = 0x00;
	DDRD = 0xF0;
	
    while (1) {
		keys = gotkey();
		
		while(keys != 0){
			//Cycle the LEDs on
			PORTB = 0xFF;
			_delay_ms(500);
			//Cycle the LEDs off
			PORTB = 0x00;
			_delay_ms(500);
			//Decrement keys
			keys = keys-1;	
		}
		
    }
}

