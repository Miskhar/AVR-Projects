/*
 * Keypad.c
 *
 * Created: 1/13/2018 10:26:01 AM
 * Author : rawri
 */ 

/*
 * GccApplication17.c
 *
 * Created: 1/9/2018 6:51:23 PM
 * Author : rawri
 */ 

#define F_CPU 8000000UL /* 8Mhz clock rate */
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

static inline void ser_init() /* Static Inline functions are great for things that are called once (like initializing) */
{
	UCSR0B = (1 << TXEN0) | (1 << RXEN0); /* Serial Transmit and Recieve Enable */
	UCSR0C = (0 << USBS0) | (3 << UCSZ00); /* Set Stop Bit Length (1 Stop Bit) and Frame Length (8 data bits). No parity */
	UBRR0H = (unsigned char)(BAUD_PRESCALE >> 8); /* Load upper 8-bits of baud rate value into high byte of UBBR0 register */
	UBRR0L = (unsigned char)BAUD_PRESCALE; /* Load lower 8-bits of the baud rate value into low byte of UBBR0 register */
	while ( !( UCSR0A & (1 << UDRE0)));
	; /* Wait for an empty Transmit Buffer */
	UDR0 = display_On; /* turn LCD on with no blink and no cursor */
	
}

unsigned char row(void)
{
	
	
/* Keypad shit.... */
unsigned char keypad(void)
{;
	unsigned char column;
	unsigned char row;
	int key;
	DDRB = 0xF0;	//Configure Port A, Pins a7 to a4 are output. Pins a3 to a0 are input.
	PORTB = 0x0F;
	
	/* Column 1 */
	key=1;
	PORTB = (1 << 4);
	if(PB0 = 1)
	{
		key = row1();
	}
	if(PB1 = 1)
	{
		key = row2();
	}
	if(PB2 = 1)
	{
		key = row3();
	}
	if(PB3 = 1)
	{
		key= row4();
	}
	_delay_ms(10);
	PORTB ^= (1 << 4);
	
	/* Column 2 */
	key=2;
	PORTB = (1 << 5);
	if(PB0 = 1)
	{
		key = row1();
	}
	if(PB1 = 1)
	{
		key = row2();
	}
	if(PB2 = 1)
	{
		key = row3();
	}
	if(PB3 = 1)
	{
		key= row4();
	}
	_delay_ms(10);
	PORTB ^= (1 << 5);
	
	/* Column 3 */
	key=3;
	PORTB = (1 << 6);
	if(PB0 = 1)
	{
		key = row1();
	}
	if(PB1 = 1)
	{
		key = row2();
	}
	if(PB2 = 1)
	{
		key = row3();
	}
	if(PB3 = 1)
	{
		key= row4();
	}
	_delay_ms(10);
	PORTB ^= (1 << 6);
	
	/* Column 4 */
	key=4;
	PORTB = (1 << 7);
	if(PB0 = 1)
	{
		key = row1();
	}
	if(PB1 = 1)
	{
		key = row2();
	}
	if(PB2 = 1)
	{
		key = row3();
	}
	if(PB3 = 1)
	{
		key= row4();
	}
	_delay_ms(10);
	PORTB ^= (1 << 7);



int printCHAR(char character, FILE *stream) /* Has printchar become a stream */
{
	

	while ((UCSR0A & (1 << UDRE0)) == 0) {}; /* While the transmit flag is active, the serial buffer is a character */

	UDR0 = character;

	return 0;
}

FILE uart_str = FDEV_SETUP_STREAM(printCHAR, NULL, _FDEV_SETUP_RW); /* sets up printf */


int main(void)
{
	stdout = &uart_str; /* links stdout and stream from file we set up CHECK ME */
	char digit;	// temporary variable to hold the value of which key is pressed
	ser_init(); /* Serial Initialize and port C to outputs */
	
	UDR0 = backlight_on; /* turn on LCD backlight */
	
	

	
	while(1)
	{
		digit = keypad();	// call the  function "keypad" to return the value of key pressed,
		//and hold it with variable "digit"
		//Now evaluate value of "digit" to match with the LED pattern needed to be exported to Port B
		switch(digit)
		{
			case '0':
			while ( !( UCSR0A & (1 << UDRE0)));
			UDR0 = form_feed;
			_delay_ms(5); /* must pause for 5ms after form feed */
			UDR0 = backlight_on;
			printf("The # is:\r");
			printf("%d", digit);
			_delay_ms(50);
			break;
			
			case '1':
			while ( !( UCSR0A & (1 << UDRE0)));
			UDR0 = form_feed;
			_delay_ms(5);
			UDR0 = backlight_on;
			printf("The # is:\r");
			printf("%d", digit);
			_delay_ms(50);
			break;
			
			case '2':
			while ( !( UCSR0A & (1 << UDRE0)));
			UDR0 = form_feed;
			_delay_ms(5);
			UDR0 = backlight_on;
			printf("The # is:\r");
			printf("%d", digit);
			_delay_ms(50);
			break;
			
			case '3':
			while ( !( UCSR0A & (1 << UDRE0)));
			UDR0 = form_feed;
			_delay_ms(5);
			UDR0 = backlight_on;
			printf("The # is:\r");
			printf("%d", digit);
			_delay_ms(50);
			break;
			
			case '4':
			while ( !( UCSR0A & (1 << UDRE0)));
			UDR0 = form_feed;
			_delay_ms(5);
			UDR0 = backlight_on;
			printf("The # is:\r");
			printf("%d", digit);
			_delay_ms(50);
			break;
			
			case '5':
			while ( !( UCSR0A & (1 << UDRE0)));
			UDR0 = form_feed;
			_delay_ms(5);
			UDR0 = backlight_on;
			printf("The # is:\r");
			printf("%d", digit);
			_delay_ms(50);
			break;
			
			case '6':
			while ( !( UCSR0A & (1 << UDRE0)));
			UDR0 = form_feed;
			_delay_ms(5);
			UDR0 = backlight_on;
			printf("The # is:\r");
			printf("%x", digit);
			_delay_ms(50);
			break;
			
			case '7':
			while ( !( UCSR0A & (1 << UDRE0)));
			UDR0 = form_feed;
			_delay_ms(5);
			UDR0 = backlight_on;
			printf("The # is:\r");
			printf("%d", digit);
			_delay_ms(50);
			break;
			
			case '8':
			while ( !( UCSR0A & (1 << UDRE0)));
			UDR0 = form_feed;
			_delay_ms(5);
			UDR0 = backlight_on;
			printf("The # is:\r");
			printf("%d", digit);
			_delay_ms(50);
			break;
			
			case '9':
			while ( !( UCSR0A & (1 << UDRE0)));
			UDR0 = form_feed;
			_delay_ms(5);
			UDR0 = backlight_on;
			printf("The # is:\r");
			printf("%d", digit);
			_delay_ms(50);
			break;
			
			case 'A':
			while ( !( UCSR0A & (1 << UDRE0)));
			UDR0 = form_feed;
			_delay_ms(5);
			UDR0 = backlight_on;
			printf("The # is:\r");
			printf("%c", digit);
			_delay_ms(50);
			break;
			
			case 'B':
			while ( !( UCSR0A & (1 << UDRE0)));
			UDR0 = form_feed;
			_delay_ms(5);
			UDR0 = backlight_on;
			printf("The # is:\r");
			printf("%c", digit);
			_delay_ms(50);
			break;
			
			case 'C':
			while ( !( UCSR0A & (1 << UDRE0)));
			UDR0 = form_feed;
			_delay_ms(5);
			UDR0 = backlight_on;
			printf("The # is:\r");
			printf("%c", digit);
			_delay_ms(50);
			break;
			
			case 'D':
			while ( !( UCSR0A & (1 << UDRE0)));
			UDR0 = form_feed;
			_delay_ms(5);
			UDR0 = backlight_on;
			printf("The # is:\r");
			printf("%c", digit);
			_delay_ms(50);
			break;
			
			case '*':
			while ( !( UCSR0A & (1 << UDRE0)));
			UDR0 = form_feed;
			_delay_ms(5);
			UDR0 = backlight_on;
			printf("The # is:\r");
			printf("%c", digit);
			_delay_ms(50);
			break;
			
			case '#':
			while ( !( UCSR0A & (1 << UDRE0)));
			UDR0 = form_feed;
			_delay_ms(5);
			UDR0 = backlight_on;
			printf("The # is:\r");
			printf("%c", digit);
			_delay_ms(50);
			break;
			
			
		}
		
		
		
	}
	return(1);
}

