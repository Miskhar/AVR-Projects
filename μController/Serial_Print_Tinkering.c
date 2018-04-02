/*
 * GccApplication8.c
 *
 * Created: 1/3/2018 6:33:32 PM
 * Author : rawri
 */ 


#define F_CPU 8000000UL
#define BAUD 2400
#define USART_BAUDRATE 2400
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define display_On 0x16 /* Display on with no cursor and no blink */
#define first_position 0x80 /* Move cursor to line 0 position 0 */
#define form_feed 0x0C /* Clear all text, move to line 0 pos 0 */
#define line_feed 0x0A /* Cursor moved to next line */
#define backlight_on 0x11 /* LCD Backlight on */
#define backlight_off 0x12 /* LCD Backlight off */

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

int printCHAR(char character, FILE *stream) /* Has printchar become a stream */
{
	while ((UCSR0A & (1 << UDRE0)) == 0) {};

	UDR0 = character;

	return 0;
}

FILE uart_str = FDEV_SETUP_STREAM(printCHAR, NULL, _FDEV_SETUP_RW); /* sets up printf */

int main(void)
{
	/* Transmit Enable */
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	/* Set Stop Bit Length (1 Stop Bit) and Frame Length (8 data bits) */
	UCSR0C = (0 << USBS0) | (3 << UCSZ00);
	UBRR0H = (unsigned char)(BAUD_PRESCALE >> 8); /* Load upper 8-bits of baud rate value into high byte of UBBR0 register */
	UBRR0L = (unsigned char)BAUD_PRESCALE; /* Load lower 8-bits of the baud rate value into low byte of UBBR0 register */
	DDRC = 0xFF; /* Turn Port C into outputs for LEDS */
	
	
	for (;;) /* repeat forever */
	{
		while ( !( UCSR0A & (1 << UDRE0)));
		; /* Wait for an empty Transmit Buffer */
		UDR0 = display_On; /* Play "A" note on Parallax LCD */
		PORTC ^= (1 << 5); /* Invert LED bit status */
		_delay_ms(250); /* Wait 250 ms */
		UDR0 = backlight_on;
		UDR0 = first_position;
		_delay_ms(500);
		

		stdout = &uart_str;
		printf("Hello World!!! \n\r");
		_delay_ms(1000);
		UDR0 = line_feed;
		_delay_ms(1000);
		printf("Goodbye World...\r");
		_delay_ms(500);
		UDR0 = form_feed;
		_delay_ms(500);
		UDR0 = first_position;
		printf("XxX");
		_delay_ms(500);
		UDR0 = backlight_off;
		UDR0 = form_feed;
		_delay_ms(1000);
	}
}
