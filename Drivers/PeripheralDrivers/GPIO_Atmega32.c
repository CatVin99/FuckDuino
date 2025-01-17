#include "GPIO_Atmega32.h"



uint8 Init_GPIO(GPIO_Pin* wichPin)
{
	uint8* directionReg;
	uint8* inputReg;
	uint8* outputReg;
	
	switch(wichPin->configuration.pinPort)
	{
		case B:
			directionReg = DDRB;
			inputReg = PINB;
			outputReg = PORTB;
		break;
		case C:
			directionReg = DDRC;
			inputReg = PINC;
			outputReg = PORTC;
		break;
		case D:
			directionReg = DDRD;
			inputReg = PIND;
			outputReg = PORTD;
		break;
		default:
			return ERROR;
	}

	
}