/*	Author: lab
 *  Partner(s) Name: Jaired
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum States {SET_C, Start, Wait, Add, AfterAdd} state;
void SM_Tick() {
	switch (state) {
		case SET_C:
			state = Start;
			break;
		case Start:
			state = Wait;
			break;
		case Wait:
			if ((PINA & 0x01) == 0x01) {
				state = Add;
			}
			else {
				state = Wait;
			}
			break;
		case Add:
			state = AfterAdd;
			break;
		case AfterAdd:
			if (PINA == 0x00) {
				state = Wait;
			}
			break;
		default:
			state = Wait;
	}

	switch (state) {
		case SET_C:
		case Start:
			PORTC = 0x07;
			break;
		case Wait:
			break;
		case Add:
			if (PORTC < 0x09) {
				PORTC = PORTC + 1;
			}
			break;
	}	
}


int main(void) {
    /* Insert DDR and PORT initializations */

    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
    while (1) {
	SM_Tick();
    }
    return 1;
}
