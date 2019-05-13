/*
* Interrupt counter on PortB bit0 to count interrupt from sensor
*/
#define F_CPU 16000000UL // X plained Pro clock is 16MHz
#include <avr/io.h>
#include <stdint.h> // has to be added to use uint8_t
#include <avr/interrupt.h> // Needed to use interrupts
#include <avr/delay.h>
#include <stdio.h>

int duty = 10;
int count = 0;
int y = 0;
int x = 0;
int n = 0;
int digit1;
int digit2;
int digit3;
int newcount = 0; 
void ten();
void twenty();
void thirty();
void fourty();
void fifty();
void sixty();
void seventy();
void eighty();
void ninety();
int main (void)
{
	DDRE = 0XFF;
	EICRA = 0;
	EIMSK=(1<<INT1);
	sei();
	PORTB= 0x01; //activate pull up of PB0
	DDRB=0x00;
	DDRA = 0xFF;
	DDRD = 0X0;// Port B all inputs
	DDRC = 0;
	PORTD |= (1<<3);// Set Pull up resistor PD2 (INT0)
	TCNT1 = 15286; 
	TCCR1A = 0x00;
	TCCR1B  |= (1<<CS12);
	TCCR0B = 0x06;
	TCNT0 = 0; //set count to 0
	TIMSK1 = (1 << TOIE1) ;
	while (1)
	{
		n++;
		if ((n = 1500))
		{
			newcount = (int)TCNT0;
			n = 0;
		} 

				digit1 = newcount/100;
				digit2 = newcount/10;
				digit3 = newcount % 10;
				
		while ((digit2 >= 10))
		{
			digit2 = digit2 - 10;
		} 
		switch(digit1)
		{
			case 0:
			digit1 = 0x3F;
			break;
			case 1:
			digit1 = 0x06;
			break;
			case 2:
			digit1 = 0x5B;
			break;
			case 3:
			digit1 = 0x4F;
			break;
			case 4:
			digit1 = 0x66;
			break;
			case 5:
			digit1 = 0x6D;
			break;
			case 6:
			digit1 = 0x7D;
			break;
			case 7:
			digit1 = 0x07;
			break;
			case 8:
			digit1 = 0x7F;
			break;
			case 9:
			digit1 = 0x67;
			break;
		}
		switch(digit2)
		{
			case 0:
			digit2 = 0x3F;
			break;
			case 1:
			digit2 = 0x06;
			break;
			case 2:
			digit2 = 0x5B;
			break;
			case 3:
			digit2 = 0x4F;
			break;
			case 4:
			digit2 = 0x66;
			break;
			case 5:
			digit2 = 0x6D;
			break;
			case 6:
			digit2 = 0x7D;
			break;
			case 7:
			digit2 = 0x07;
			break;
			case 8:
			digit2 = 0x7F;
			break;
			case 9:
			digit2 = 0x67;
			break;
			}
		switch(digit3)
		{
			case 0:
			digit3 = 0x3F;
			break;
			case 1:
			digit3 = 0x06;
			break;
			case 2:
			digit3 = 0x5B;
			break;
			case 3:
			digit3 = 0x4F;
			break;
			case 4:
			digit3 = 0x66;
			break;
			case 5:
			digit3 = 0x6D;
			break;
			case 6:
			digit3 = 0x7D;
			break;
			case 7:
			digit3 = 0x07;
			break;
			case 8:
			digit3 = 0x7F;
			break;
			case 9:
			digit3 = 0x67;
			break;
						}	
		x++;
		if ((x == 200))
		{
			PORTA = digit1;
		}
		if ((x == 300))
		{
			PORTA = digit2;
		}
		if ((x == 400))
		{
			PORTA = digit3;
		}
		if ((x == 500))
		{
			PORTA = 0;
			x = 0;
		}
		switch(duty)
		{
			case 10: ten();
			break;
			case 20: twenty();
			break;
			case 30: thirty();
			break;
			case 40: fourty();
			break;
			case 50: fifty();
			break;
			case 60: sixty();
			break;
			case 70: seventy();
			break;
			case 80: eighty();
			break;
			case 90: ninety();
			break;
		}
		
	}
}

void ten()
{
	PORTE = 0xFF;
	_delay_ms(1);
	PORTE = 0;
	_delay_ms(9);
}

void twenty()
{

	PORTE = 0XFF;
	_delay_ms(2);
	PORTE = 0;
	_delay_ms(8);
}

void thirty()
{

	PORTE = 0XFF;
	_delay_ms(3);
	PORTE = 0;
	_delay_ms(7);
}

void fourty()
{
	PORTE = 0XFF;
	_delay_ms(4);
	PORTE = 0;
	_delay_ms(6);
}

void fifty()
{

	PORTE = 0XFF;
	_delay_ms(5);
	PORTE = 0;
	_delay_ms(5);

}

void sixty()
{

	PORTE = 0XFF;
	_delay_ms(6);
	PORTE = 0;
	_delay_ms(4);

}

void seventy()
{

	PORTE = 0XFF;
	_delay_ms(7);
	PORTE = 0;
	_delay_ms(3);

}

void eighty()
{

	PORTE = 0XFF;
	_delay_ms(8);
	PORTE = 0;
	_delay_ms(2);

}

void ninety()
{

	PORTE = 0XFF;
	_delay_ms(9);
	PORTE = 0;
	_delay_ms(1);

}

//interrupt service routine
//changes duty cycle on button press
ISR(INT1_vect)
{
	_delay_ms(500);
	duty = duty + 10;
	
	if ((duty == 100))
	{
		duty = 10;
	}
}

ISR (TIMER1_OVF_vect)
{
	count =(int)TCNT0;
	TCNT0 = 0;
}
