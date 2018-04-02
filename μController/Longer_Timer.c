/*
 * Longer_Timers.c
 *
 * Created: 3/19/2018 5:45:17 PM
 * Author : Keith
 
 *	The goal of this program is to create longer delays with a timer (so that an 8-bit or 16-bit timer can be used to count delays of minutes, or hours, or days)
 *  The LED flips states on a 15 second timer (it could be minutes, or hours...but i didn't want to wait to test that)
 * NOTES:
		-Clock errors compound. if the clock is 1.1mHz instead of 1.0mHz, the timer will be 60 times that small error. For stable timers, very stable clocks are needed.
 
 *** HARDWARE: 
			-ATMega 328P
			-Blue LED
			-220 ohm resistor
			-PROGRAMMER: AVR Dragon
	HW Setup:
			> The LED and Resistor are on pin PC4 (2nd down from top on the right side)
 
 ** TCCR1B is the 16-bit timer  register
 * CS10-CS12 Control the timer with the clock input and the Prescalers for this input
 * For Example: (1<<CS10) is clock input with no prescaling
 (1<<CS11) is clock input with 8 prescaling (clk / 8)
 (1<<CS10) && (1<<CS11) is 64 prescaling (clk / 65)
 (1<<CS12) is 256 prescaling (clk / 256)
 (1<<CS12) && (1<<CS10) is 1024 Prescaling (clk / 1025)
 
 
 * Timer Resolution = (1 / (Input Frequency / Prescale)) = (Prescale / Input Frequency)
 
 * Target Timer Count = (Input Frequency / Prescale) / Target Frequency - 1
 
 
 */ 

#define F_CPU 8000000UL /* 8Mhz clock rate */

#include <avr/io.h>


int main(void)
{
	unsigned char ElapsedSeconds = 0; // Make a new counter variable and intialize it to 0
	
	DDRC = 0xFF; // Set Port C pins as outputs (LED on PC4)
	
	TCCR1B = (1 << CS12); // CS12 in TCCR1B sets the clock as timer input, with a 256 Prescaler
	
	while (1)
	{
		if (TCNT1 >= 31250) // Check Timer Value in statement, TRUE when it's 1 second
		{
			
			TCNT1 = 0; //Reset Timer value
			ElapsedSeconds++; //Increase Counter Variable
			
			if (ElapsedSeconds == 15) // Check if 15 seconds have passed
			{
				ElapsedSeconds = 0; // Reset Counter Variable
				PORTC ^= (1<<4); // Toggle the status of LED
			}
		}
		
		
	}
}
