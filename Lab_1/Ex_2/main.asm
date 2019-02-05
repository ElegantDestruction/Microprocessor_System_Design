; Lab_1_Ex_1
; In this lab we are making the AT8515 toggle
; LEDs in a sequential order

.include "m8515def.inc"  ; Header file for ATmega8515 micro

.def temp = r16   ;renaming the r16 reg to temp

start:
	
	ldi temp, low(RAMEND)	; load SPL (the lowest byte of the stack)
	out SPL, temp			; load low byt address to SPL pointer register
	ldi temp, high(RAMEND)	; load SPH (the high byte of the stack)
	out SPH, temp			; load high byte address to SPH pointer register

	ldi temp, $ff			; Set up PORTB as outputs
	out DDRB, temp			; DDRB - Data register B
	out PORTB, temp	

loadbyte:
	
	ldi temp, $aa			; load aa into temp
	out PORTB, temp			; load temp into PORTB
	rcall one_sec_delay		; delay
	ldi temp, $55			; load 55 into temp
	out PORTB, temp			; load temp into PORTB
	rcall one_sec_delay		; delay
	rjmp loadbyte			; repeat

one_sec_delay:
	
	ldi r20, 20				; 20d = 14h
	ldi r21, 25				; 25d = 19h
	ldi r22, 25

delay:
							; delays with a nested loop
	dec r22					; 255*255 total iterations
	brne delay

	dec r21					; 255 iterations
	brne delay

	dec r20					; 20 iterations
	brne delay

	ret						; ret
