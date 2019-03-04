#include <MKL25Z4.H>
#include "gpio_defs.h"

/* CEE-345 Microprocessor System Design
Demonstration of simple digital output
Use RGB LED on Freedom Board*/

void Delay(unsigned int time_del) {
		//~1ms * time_del
	volatile int t;
	
	while (time_del--) {
		for (t=4800; t > 0; t--)
			;
		
	}
}

/* Each LED corresponds to a bit on a port
	Red LED connected to Port B (PTB), bit 18 (RED_LED_POS)
	Green LED connected to Port B (PTB), bit 19 (GREEN_LED_POS)
	Blue LED connected to Port D (PTD), bit 1 (BLUE_LED_POS)
Active-Low outputs: Write a 0 to turn on an LED

Turning LEDs on and off
Turn on one LED: PTx->PDOR = ~ MASK(yyy_LED_POS) ;
Turn on two LEDs: PTx->PDOR = ~ (MASK(yyy_LED_POS) | MASK(zzz_LED_POS));
Turn all LEDs off: PTx->PDOR = 0xFFFFFFFF ;*/

void red(void)
{
	//turn on red led
	PTB-> PDOR = ~ MASK(RED_LED_POS);
	//turn off blue LED
	PTD->PDOR = 0xFFFFFFFF;
	
	//wait for 100 ms
	Delay(100);
	
	//turn off all LED
	PTB->PDOR = 0xFFFFFFFF;
	
	//turn off blue LED
	PTD->PDOR = 0xFFFFFFFF;
	
	//wait for 100 ms
	Delay(100);
	
	//turn on red led
	PTB-> PDOR = ~ MASK(RED_LED_POS);
	//turn off blue LED
	PTD->PDOR = 0xFFFFFFFF;
	
	//wait for 100 ms
	Delay(100);
	
}

/******************************
MAIN function
*******************************/


int main (void) {
	//Declare a global variable for debug
	unsigned int counter = 0;
	
	/* Configuration steps 
	1. Enable clock to GPIO ports
	2. Enable GPIO ports (2 step process)
	3. Set GPIO direction to output
	4. Ensure LEDs are off */
	
	//Enable clock to ports B and D
	/*The symbol SIM_SCGC5 defines the address of the fifth
	system clock rating register to be at 0x40048038. This and other 
	symbols that represent register addresses (or masks that set or clear
	specific bits) are defined in the mCU-specific header file, MKL25Z4.h.
	This header file is provided with the development tools.*/
	
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
	
	// Make 3 pins GPIO through GPIO setup below
	// The macro PORT_PCR_MUX() is defined in the header 
	// file and sets the MUX bits in the corresponding pin control register.
	// two steps process: configure pin multiplexer and select a GPIO pin
	// first, set pin to GPIO by using MUX = 1 in PCR register
	// second, select a GPIO pin
	// "&= ~PORT_PCR_MUX_MASK" below is used to clear bits in the MUX field
	// PORT_PCR_MUX(1) is to configure a port as a GPIO pin and
	// use |= to leave other bits unchanged
	
	PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(1); // Set PTB18 pin mux to GPIO
	
	// Set ports to outputs: Port Data Direction Register (PDDR)
	PTB->PDDR |= MASK(RED_LED_POS);
	
	//Turn off LEDs: Port Set Output Register (PSOR)
	
	PTB->PSOR = MASK(RED_LED_POS);
	
	//end of configuration code
	
	//flash LED repeatedly
	
	while(1) {
		red();
	}
	
}
