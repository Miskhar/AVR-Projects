/*
 * Timer_Test_1.c
 *
 * Created: 3/19/2018 4:25:00 PM
 * Author : Keith
 *
 * Testing Timers with an ATMEGA 328P running at FCPU
 
 * TCCR1B is the 16-bit timer  register
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
     DDRC = 0xFF; // Set Port C pins as outputs (LED on PC4)
	 
	 TCCR1B = (1 << CS12); // CS12 in TCCR1B sets the clock as timer input, with a 256 Prescaler
	 
    while (1) 
    {
		if (TCNT1 >= 31250) // This says that every second [(8MhZ input / 256 Prescaler)] NOTE: Use >= for this If statement!!
		{
			PORTC ^= (1<<4); // Toggle the status of LED
			
			TCNT1 = 0; //Reset Timer value
		}
		
		
    }
}

