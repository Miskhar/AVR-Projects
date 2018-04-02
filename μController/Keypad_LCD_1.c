/*
 * LCD_Keypad.c
 *
 * Created: 1/7/2018 8:12:03 PM
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

unsigned char keypad(void) /* 4x4 Keypad Matrix function */
{
	unsigned char key; /* stores which key is pressed on 4x4 */
	unsigned char portc_pin; /* reads value from port c */
	unsigned char keypad_column[4] = {7,6,5,4}; /* pins PC0, PC1, PC2, PC3 control keypad columns (outputs) */
	unsigned char keypad_row[4] = {3,2,1,0}; /* pins PB1, PB2, PB3, PB4 control keypad rows (inputs, pulled down) */
	unsigned char keypad_array[4][4] =
	{
		{'1','2','3','A'},
		{'4','5','6','B'},
		{'7','8','9','C'},
		{'*','0','#','D'}	};
		unsigned char column;
		unsigned char row;
		DDRC = 0x0F; /* Port C 0-3 set to outputs for columns */
		DDRB = 0x00; /* Port B all pins set to inputs for rows (only pins PB1-PB4 necessary */
		
		for (column=0; column<4; column++)
		{
			PORTC = ~(1<<(keypad_column[column]));
			_delay_ms(50);
			portc_pin = PINC; /* read value from port c...MAY BE ERROR HERE */
			for (row=0; row<4; row++)
			{
				if((portc_pin & (1<<(keypad_row[row])))==1)
				{
					key = keypad_array[column][row]; /* search for corresponding element from keypad array */
					return (key); /* return which key is pressed */
				}
			}
		}
	}

	int printCHAR(char character, FILE *stream) /* Has printchar become a stream */
	{
		

		while ((UCSR0A & (1 << UDRE0)) == 0) {}; /* While the transmit flag is active, the serial buffer is a character */

		UDR0 = character;

		return 0;
	}

	FILE uart_str = FDEV_SETUP_STREAM(printCHAR, NULL, _FDEV_SETUP_RW); /* sets up printf */

	int main(void)
	{
		unsigned char digit; /* temporary variable to store which digit on keypad has been pressed */
		
		ser_init(); /* Serial Initialize and port C to outputs */
		UDR0 = backlight_on; /* turn on LCD backlight */
		
		while(1)
		{
			digit = keypad(); /*call the function "keypad" to return the value of the key pressed and hold it in "digit" */
			stdout = &uart_str; /* links stdout and stream from file we set up CHECK ME */
			switch(digit)
			{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				while ( !( UCSR0A & (1 << UDRE0)));
				UDR0 = form_feed;
				UDR0 = backlight_on;
				printf("The # is:\r");
				printf("%d", digit);
				_delay_ms(1000);
				case 'A':
				case 'B':
				case 'C':
				case 'D':
				case '#':
				case '*':
				while ( !( UCSR0A & (1 << UDRE0)));
				UDR0 = form_feed;
				UDR0 = backlight_on;
				printf("The # is:\r");
				printf("%c", digit);
				_delay_ms(1000);
			}
		}
		return(1);
	}
	