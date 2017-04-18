/*
 * CODENAME : RED COMET
 * redcomet.c
 *
 * Created: 10.04.2017 13:53:03
 * Author : Adam Kordecki
 */ 
#include <avr/io.h>
#include <util/delay.h>

#define SCREEN_SIZE 4		//Ilo�� segment�w LED
#define F_CPU 8000000		//8 MHz
#define SEGMENT_DDR DDRB	//Kt�re piny s� do manipulowania segmentami
#define SEGMENT_PORT PORTB	//Kt�ry port jest do manipulowania segmentami
#define SELECT_DDR DDRC		//Kt�re piny s� do wyboru segmentu
#define SELECT_DDR PORTC	//Kt�ry port jest do wyboru segmentu

volatile int screen[SCREEN_SIZE] = {0,0,0,0};
volatile int digits[10] = {
	0b11000000,	// 0
	0b11111001,	// 1
	0b10100100,	// 2
	0b10110000,	// 3
	0b10011001,	// 4
	0b10010010,	// 5
	0b10000010,	// 6
	0b11111000,	// 7
	0b10000000,	// 8
	0b10011000,	// 9
	};
volatile int buffer[SCREEN_SIZE];

/*
*/
	
void clockprescale(void)
{
	CLKPR = 0b10000000;
	CLKPR = 0b00000000;
}

int main(void)
{
	// Napis na segmencie
	SEGMENT_DDR = 0xFF;	// Ca�y port D na output
	SEGMENT_PORT = 0x00;	// Wszystkie piny na stan niski
	
	// Wyb�r segmentu
	SELECT_DDR = 0xFF;	// Ca�y port B na output
	SELECT_DDR = 0x00;	// Wszystkie piny na stan niski
	
	unsigned int i, j;
    while (1) 
	{
		for(i = 0; i < SCREEN_SIZE; i++)
		{
		//PORTB = digits[j];
			PORTC = (1<<i);	//W��czenie segmentu
			PORTB = digits[i+4];
			_delay_ms(5);
			PORTC = (0<<i);	//Wy��czenie segmentu
		}
    }
}

