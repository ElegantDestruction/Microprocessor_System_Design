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

int main(void)
{
    keypad_init();
    SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */
    PORTD->PCR[1] = 0x100;      /* make PTD1 pin as GPIO */
    PTD->PDDR |= 0x02;          /* make PTD1 as output pin */
    
    while(1)
    {
        if (keypad_kbhit() != 0)    /* if a key is pressed? */
          //  PTD->PCOR |= 0x02;          /* turn on blue LED */
				    PTD->PDOR =  ~MASK(BLUE_LED_POS); /* turn on blue LED */
        else
           // PTD->PSOR |= 0x02;          /* turn off blue LED */
				   PTD->PDOR =  MASK(BLUE_LED_POS); /* turn off blue LED */
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
    PTD->PDDR = 0x0F;         /* make PTD7-0 as input pins */
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

