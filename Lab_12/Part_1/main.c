/* Generate 60 Hz with varying duty cycle PWM output
A LED Light Dimmer
The pulse period is set by the MOD register. Using the CnV
register we set the pulse width (duty cycle). If CnV = 0, then
output has 0 duty cycle. If CnV is greater than or equal to
MOD, the duty cycle is 100%.

Duty Cycle = CnV/(MOD+1) * 100%

TMPx_MOD = (41.98MHz / 60 Hz) - 1 = 699,665. This is not acceptable
because it is larger than 65,535 (2^16), the maximum value of TMPx_MOD
register can hold. Now, (699,666/128)-1 is acceptable 
if we use prescaler of 128. The lowest prescaler is 16, then 
(699,666/16)-1=43,728

The CnV register value is incremented 
by 437 (1%) every 20ms. Because the LED is low active,
the longer the duty cycle results in lower light intensity
*/

#include <MKL25Z4.H>
void delayMs(int n);

int main (void) {
	int pulseWidth = 0;
	
	SIM->SCGC5 |= 0x1000;			//enable clock to Port D
	PORTD->PCR[1] = 0x0400;		//PTD1 used by TPM0
	
	SIM->SCGC6 |= 0x01000000;		//enable clock to TPM0
	SIM->SOPT2 |= 0x01000000;		//Use MCGFLLCLK as timer counter clock
	TPM0->SC = 0;								//reset timer
	TPM0->CONTROLS[1].CnSC = 0x20 | 0x08;		//Edge-aligned, pulse high
	TPM0->MOD = 43702;					//Set up modulo register for 60 Hz
	TPM0->CONTROLS[1].CnV = 14568;
	TPM0->SC = 0x0C;						//Enable TPM0 with prescaler
	
	while (1) {
		pulseWidth += 437;
		if (pulseWidth > 43702)
			pulseWidth = 0;
		TPM0->CONTROLS[1].CnV = pulseWidth;		
		delayMs(20);
	}
}

/*Delay in milliseconds
* The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit()
*/
void delayMs(int n) {
	int i,j;
	for (i = 0; i < n; i++){
		for (j = 0; j < 7000; j++) {}
		}
}
