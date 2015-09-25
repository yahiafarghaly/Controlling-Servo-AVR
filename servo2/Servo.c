#define F_CPU 1000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include "common_macros.h"
void PORT_INI(void){
	DDRA&=~(1<<PA0);
	PORTA|=(1<<PA0); /*INTERNAL pull up*/
	DDRC&=~(1<<PC0);
	PORTC|=(1<<PC0);
	DDRD|=(1<<PD6);
	CLEAR_BIT(PORTD,6);
	DDRD|=(1<<PD5);
	CLEAR_BIT(PORTD,5);
}
void TIMER16_FAST_PWM_INIT(unsigned int compare){
	TCCR1A = 1<<WGM11 | 1<<COM1A1 | 1<<COM1A0;
	TCCR1B = 1<<WGM13 | 1<<WGM12 | 1<<CS10;
	ICR1 = compare;/*Max count*/
}
int main(void)
{
	PORT_INI();
	TIMER16_FAST_PWM_INIT(19999);
	OCR1A = ICR1 - 2100;
    while(1)
    {
        if(BIT_IS_CLEAR(PINA,0)) {
			OCR1A = ICR1 - 2100;
			SET_BIT(PORTD,6);
			}
		if(BIT_IS_CLEAR(PINC,0)) {
			OCR1A = ICR1 - 500;
			CLEAR_BIT(PORTD,6);
			}

		
    }
}