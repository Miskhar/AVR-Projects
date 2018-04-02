/*
 * Keypad_Debounce_Attempt.c
 *
 * Created: 1/20/2018 6:36:05 PM
 * Author : rawri
 */ 
#define F_CPU 8000000UL /* 8Mhz clock rate */
#define BAUD 2400
#define USART_BAUDRATE 2400
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define display_On 0x16 /*  Parralax cmd: Display on with no cursor and no blink */
#define first_position 0x80 /* Parralax cmd: Move cursor to line 0 position 0 */
#define form_feed 0x0C /* Parralax cmd: Clear all text, move to line 0 pos 0 */
#define line_feed 0x0A /* Parralax cmd: Cursor moved to next line */
#define backlight_on 0x11 /* Parralax cmd: LCD Backlight on */
#define backlight_off 0x12 /* Parralax cmd: LCD Backlight off */

#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

static inline void ser_init() /* I'm told Static Inline functions are great for things that are called once (like initializing serial) */
{
	UCSR0B = (1 << TXEN0) | (1 << RXEN0); /* Serial Transmit and Recieve Enable */
	UCSR0C = (0 << USBS0) | (3 << UCSZ00); /* Set Stop Bit Length (1 Stop Bit) and Frame Length (8 data bits). No parity */
	UBRR0H = (unsigned char)(BAUD_PRESCALE >> 8); /* Load upper 8-bits of baud rate value into high byte of UBBR0 register */
	UBRR0L = (unsigned char)BAUD_PRESCALE; /* Load lower 8-bits of the baud rate value into low byte of UBBR0 register */
	while ( !( UCSR0A & (1 << UDRE0)));
	; /* Wait for an empty Transmit Buffer */
	UDR0 = display_On; /* Turn LCD on with no blink and no cursor */
	
}

ISR(PCINT0_vect) // PB0 Interrupt; All values here *MUST* be volatile
	{
	volatile char last_buttonstate = 0, just_pressed = 0, pressed = 0;
	volatile char buttonholdcounter =0;
	
	//Debounce for PB0
	if (! (PINB & (1 << PB0) ))
		{
			if (! (last_buttonstate & 0x1)) //was not pressed before
			{
				_delay_ms(10); // debounce
				if (PINB & (1 << PB0)) // filter out bounces
				{
					PCICR = (1 << PCIE0);
					return;
				}
			}
			last_buttonstate |= 0x1;
			just_pressed |= 0x1;
			return;
	}
	else
	{
			last_buttonstate &= ~0x01;
		}
		return;
		}

unsigned char keypad(void){	// Define the function to return which key is pressed
	unsigned char key;	//which key is pressed?
	unsigned char portb_pin;
	PCMSK0 |= (1<<PCINT0) | (1<<PCINT1) | (1<<PCINT2) | (1<<PCINT3); // Enable Pin Change Interrupts on PB pins 0-3
	PCICR |= (1<<PCIE0); // Allow PCINT0-PCINT7
	sei(); // Enable interrupts for this section
	DDRC = 0b00100000; // ISR LED SIGNAL *****************************
	
	unsigned char keypad_column[4] = {7,6,5,4};	//Pins b7, 6, 5, 4 of Port B control keypad columns (OUTPUTS)
	unsigned char keypad_row[4] = {3,2,1,0};	// Pins b3, 2, 1, 0 of Port B control keypad rows	(INPUTS)
	unsigned char keypad_array[4][4] ={	//Array contains all
		{'1','2','3','A'},
		{'4','5','6','B'},
		{'7','8','9','C'},
		{'*','0','#','D'}
	};
	unsigned char column;
	unsigned char row;

	DDRB = 0xF0;	//Configure Port B, Pins b7 to b4 are output. Pins b3 to b0 are input.
	for (column=0; column<4; column++)
	{	
		PORTB = ~(1<<(keypad_column[column]));
		_delay_ms(20);
		portb_pin = PINB;	//read the value from port B
		for(row=0; row<4; row++){
			if((portb_pin & (1<<(keypad_row[row])))==0) 
			{
				key = keypad_array[column][row];	// search for the corresponding element in keypad array
				return (key);	// return the answer, which key is pressed?
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

FILE uart_str = FDEV_SETUP_STREAM(printCHAR, NULL, _FDEV_SETUP_RW); /* Sets up "printf" */


int main(void)
{
	stdout = &uart_str; /* Links stdout and stream from file we set up */
	int digit;	/* Temporary variable to hold the value of which key is pressed */
	ser_init(); /* Serial Initialize */
	
	UDR0 = backlight_on; /* Turn on LCD backlight */
	
	

	
	while(1)
	{
		digit = keypad();	/* Call the  function "keypad" to return the value of key pressed, and hold it with variable "digit" */
		
		switch(digit) /* Now evaluate value of "digit" to match with the LED pattern needed to be exported to Port B */
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
			while ( !( UCSR0A & (1 << UDRE0))); /* Wait for serial buffer to clear, clear screen, turn on backlight, display text */
			UDR0 = form_feed;
			_delay_ms(5);
			UDR0 = backlight_on;
			printf("The # is:\r");
			printf("%c", digit);
			_delay_ms(50);
			break;
			
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case '*':
			case '#':
			while ( !( UCSR0A & (1 << UDRE0))); /* Wait for serial buffer to clear, clear screen, turn on backlight, display text */
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

