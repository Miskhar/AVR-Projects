/*
 * LCD_Test.c
 *
 * Created: 12/22/2017 1:59:44 PM
 * Author : rawri
 */ 
#define F_CPU 8000000UL
#define BAUD 2400
#define USART_BAUDRATE 2400
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


#include <util/delay.h>
#include <avr/io.h>


int main(void)
{
	/* Transmit Enable */
    UCSR0B = (1 << TXEN0);
	/* Set Stop Bit Length (1 Stop Bit) and Frame Length (8 data bits) */
	UCSR0C = (0 << USBS0) | (3 << UCSZ00);
	UBRR0H = (unsigned char)(UBRR >> 8); /* Load upper 8-bits of baud rate value into high byte of UBBR0 register */
	UBRR0L = (unsigned char)UBRR; /* Load lower 8-bits of the baud rate value into low byte of UBBR0 register */
	DDRC = 0xFF; /* Turn Port C into outputs for LEDS */
	
	
   for (;;)
    {
		while ( !( UCSR0A & (1<<UDRE)) ); /* Wait for an empty Transmit Buffer */
		UDR0 = 0xDC /* Play "A" note on Parallax LCD */
		PORTC ^= (1 << 5); /* Invert LED bit status */
		_delay_ms(250); /* Wait 250 ms */
    }
}

