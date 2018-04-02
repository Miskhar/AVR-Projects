/*
 * GccApplication6.c
 *
 * Created: 12/18/2017 7:21:25 PM
 * Author : rawri
 */ 

#define F_CPU 8000000

#include <avr/io.h>


int main(void)
{
   DDRD = 0xFF;
   
    while (1) 
    {
		PORTD ^= (1 << PD0);
		_delay_ms(250);
    }
}

