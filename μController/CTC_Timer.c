/*
 * CTC_Timer.c
 *
 * Created: 3/19/2018 6:04:45 PM
 * Author : Keith
 */ 

#define F_CPU 8000000UL /* 8Mhz clock rate */

#include <avr/io.h>


int main(void)
{
	DDRC = 0xFF; // Set Port C pins as outputs (LED on PC4)
	TCCR1B = (1 << WGM12); //Configure Timer to CTC (Clear on Timer Compare) Mode
	OCR1A = 31250;  //Set Output Compare Register 1A Value to a rate of once per second (8mHz clock and 256 prescaler)
	TCCR1B = (1 << CS12); // CS12 in TCCR1B sets the clock as timer input, with a 256 Prescaler
	
	while (1)
	{
		if (TIFR1 & (1<<OCF1A)) // If TC1 Interrupt Flag Register & Output Compare Flag 1A are set (when the compare matches)
		{
			PORTC ^= (1<<4); // Toggle the status of LED
			
			 TIFR1 = (1 << OCF1A); // Clear CTC Flag
		}
		
		
	}
}

