/* Matrix keypad detect

* This program checks a 4x4 matrix keypad to see whether
 * a key is pressed or not.  When a key is pressed, it turns
 * on the blue LED.
 *
 * PortC 7-4 are connected to the columns and PortC 3-0 are connected
 * to the rows.
 */

#include <MKL25Z4.H>
#include "gpio_defs.h"

void delayUs(int n);

void keypad_init(void);
char keypad_kbhit(void);
char keypad_getkey(void);
void LED_init(void);
void LED_set(char value);

int main(void)
{
		unsigned char key;
    keypad_init();
		LED_init();
    
    while(1)
    {
        key = keypad_getkey();		//Read in keypad input
				LED_set(key);							//Set LED based on values given
//			if (keypad_kbhit() != 0)
//				PTD->PDOR = ~MASK(BLUE_LED_POS);
//			else
//				PTD->PDOR = MASK(BLUE_LED_POS);
    }
}


/* this function initializes PortC that is connected to the keypad.
 * All pins are configured as GPIO input pin with pullup enabled.
 */
void keypad_init(void)
{
    SIM->SCGC5 |= 0x0800;       /* enable clock to Port C */ 
    PORTC->PCR[0] = 0x103;      /* make PTD0 pin as GPIO and enable pullup*/
    PORTC->PCR[1] = 0x103;      /* make PTD1 pin as GPIO and enable pullup*/
    PORTC->PCR[2] = 0x103;      /* make PTD2 pin as GPIO and enable pullup*/
    PORTC->PCR[3] = 0x103;      /* make PTD3 pin as GPIO and enable pullup*/
    PORTC->PCR[4] = 0x103;      /* make PTD4 pin as GPIO and enable pullup*/
    PORTC->PCR[5] = 0x103;      /* make PTD5 pin as GPIO and enable pullup*/
    PORTC->PCR[6] = 0x103;      /* make PTD6 pin as GPIO and enable pullup*/
    PORTC->PCR[7] = 0x103;      /* make PTD7 pin as GPIO and enable pullup*/
    //PTD->PDDR = 0x0F;         /* make PTD7-0 as input pins */
}

/* This is a non-blocking function.
 * If a key is pressed, it returns 1.
 * Otherwise, it returns a 0 (not ASCII '0'). */
char keypad_kbhit(void)
{
    int col;

    PTC->PDDR |= 0x0F;          /* enable column (PTC4-PTC7) as input */
																/* enable row (PTC0-PTC3) as output */
    PTC->PCOR = 0x0F;           /* enable all rows driven low */
    delayUs(2);                 /* wait for signal return */
    col = PTC->PDIR & 0xF0;     /* read all columns */
																/* PDOR has a vaue of 0xF0 when no key pressed */
																
    PTC->PDDR = 0;              /* disable all rows */
    if (col == 0xF0)
        return 0;               /* no key pressed */
    else
        return 1;               /* a key is pressed */
}

void delayUs(int n)
{
    int i; int j;
    for(i = 0 ; i < n; i++) {
        for(j = 0; j < 8; j++) ;
    }
}


/* Turn on or off the LEDs based on the value passed */
void LED_set(char value)
{
	if(value == '1')
		PTB->PCOR = 0x40000;	//Turn on Red LED
	
	else if(value == '2')
		PTB->PSOR = 0x40000;	//Turn off Red LED
	
	else if(value == '#')
		PTB->PCOR = 0x80000;	//Turn on Green LED
	
	else if(value == 'D')
		PTB->PSOR = 0x80000;	//Turn off Green LED
}

/* Initialize all the LEDs */
void LED_init(void)
{
	SIM->SCGC5 |= 0x400;			//Enable clock to Port B
	SIM->SCGC5 |= 0x1000;			//Enable clock to Port D
	
	PORTB->PCR[18] = 0x100;		//Make PTB18 pin as GPIO
	PTB->PDDR |= 0x40000;			//Make PTB18 as output pin
	PTB->PSOR |= 0x40000;			//Turn off red LED
	
	PORTB->PCR[19] = 0x100;		//Make PTB19 pin as GPIO
	PTB->PDDR |= 0x80000;			//Make PTB19 as output pin
	PTB->PSOR |= 0x80000;			//Turn off green LED
	
	PORTD->PCR[1] = 0x100;		//Make PTD1 pin as GPIO
	PTD->PDDR |= 0x02;				//Make PTD1 as an output pin
	PTD->PSOR |= 0x02;				//Turn off blue LED
}


//This function should get the key pressed on the keypad and return it
char keypad_getkey(void){
	int row, col;
	const char col_select[] = {0x01, 0x02, 0x04, 0x08}; //One row is going to be active
	const char keymap[] = "123A456B789C*0#D";
	
	//Check to see if any key is pressed first
	PTC->PDDR |= 0x0F;			//Enable column (PTC4-7) as input
													//Enable row (PTC0-PTC3) as output?????
	PTC->PCOR = 0x0F;				//Enable all rows driven low
	delayUs(2);							//Wait for signal to settle
	col = PTC->PDIR & 0xF0;	//Read all columns (will have a value of 0xF0 when not pressed
	PTC->PDDR = 0;					//Disable all rows
	
	//Return 0 when no key pressed
	if (col == 0xF0)
		return 0;
	
	//Determine which key was pressed
	for (col = 0; col < 4; col++){
		PTC->PDDR &= ~(0xF << 4);											//Disable all columns
		PTC->PDDR |= col_select[col] << 4;						//Enable only 1 column
		PTC->PSOR = 0x0F << 4;												//Turn the active column high
		delayUs(2);																		//Allow signal to settle
		row = PTC->PDIR & 0xF;									//Read all rows
		PTC->PCOR = 0xF << 4;													//Set all the column data pins low
		if (row != 0) break;													//If row isn't 0, an input was detected
	}
	
	//Cleanup and exit if no key pressed
	PTC->PDDR &= ~(0xF << 4);											//Disable all columns again
	if (col == 4) return 0;												//If col is 4, it means no key was pressed; return 0
	
	//Determine what key was pressed via creative math and return it
	if (row == 0x01) return keymap[col + 0 * 4 + 1];		//column 0
	if (row == 0x02) return keymap[col + 1 * 4 + 1];		//column 1
	if (row == 0x04) return keymap[col + 2 * 4 + 1];		//column 2
	if (row == 0x08) return keymap[col + 3 * 4 + 1];		//column 3
	
	return 0; 		//Just in case something goes awry
	
	
	
}
