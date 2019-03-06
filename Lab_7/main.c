#include <MKL25Z4.H>
#include "gpio_defs.h"

void delayUs(int n);

void keypad_init(void){
	SIM->SCGC5 |=	;		/*enable clock to Port C */
	PORTC->PCR[0] = 	;   /*make PTD0 pin as GPIO and enable pullup */
	PORTC->PCR[0] = 	;	/*make PTD1 pin as GPIO and enable pullup */
	PORTC->PCR[0] = 	;	/*make PTD2 pin as GPIO and enable pullup */
	PORTC->PCR[0] = 	;	/*make PTD3 pin as GPIO and enable pullup */
	PORTC->PCR[0] = 	;	/*make PTD4 "*/
	PORTC->PCR[0] = 	;	/*make PTD5
	PORTC->PCR[0] = 	;
	PORTC->PCR[0] = 	;
	PTD->PDDR =		;	
}



void keypad_kbhit(void);


