#include "GPIO_Atmega32.h"

static boolean PollPinStatusPullUp(GPIO_Pin* wichPin);
static boolean SetOutputLow(GPIO_Pin* wichPin);
static boolean SetOutputHigh(GPIO_Pin* wichPin);
static boolean ToggleOutput(GPIO_Pin* wichPin);


uint8 Init_GPIO(GPIO_Pin* wichPin)
{	
	switch(wichPin->configuration.pinPort)
	{
		case B:
			wichPin->directionRegPtr = &DDRB;
			wichPin->inputRegPtr = &PINB;
			wichPin->outputRegPtr = &PORTB;
		break;
		case C:
			wichPin->directionRegPtr = &DDRC;
			wichPin->inputRegPtr = &PINC;
			wichPin->outputRegPtr = &PORTC;
		break;
		case D:
			wichPin->directionRegPtr = &DDRD;
			wichPin->inputRegPtr = &PIND;
			wichPin->outputRegPtr = &PORTD;
		break;
		default:
			return ERROR;
	}
	
	if (wichPin->configuration.pinBehavior == INPUT)
	{
		*(wichPin->directionRegPtr) &= ~(1U << wichPin->configuration.pinNumber);
		
		if (wichPin->configuration.resistor == PULL_UP)
		{
			*(wichPin->outputRegPtr) |= (1U << wichPin->configuration.pinNumber);
		}
		else if (wichPin->configuration.resistor == PULL_DOWN)
		{
			
		}
	}
	else if (wichPin->configuration.pinBehavior == OUTPUT)
	{
		*(wichPin->directionRegPtr) |= (1U << wichPin->configuration.pinNumber);
	}
	
								
	wichPin->self = (void*)wichPin;
	wichPin->PollPinStatusFnc = &PollPinStatusPullUp;
	wichPin->SetOutputHighFnc = &SetOutputHigh;
	wichPin->SetOutputLowFnc = &SetOutputLow;
	wichPin->ToggleOutput = &ToggleOutput;

	
	return OK;
	
	
}


static boolean PollPinStatusPullUp(GPIO_Pin* thePin)
{
	
	if ( !(*thePin->inputRegPtr & (1U << thePin->configuration.pinNumber)) )
	{	
		++thePin->debounceCnt;
	}
	
	if (thePin->debounceCnt == DEBOUNCE_COUNTER_MAX)
	{
		thePin->debounceCnt = 0U;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

static boolean SetOutputHigh(GPIO_Pin* thePin)
{
	
	if (thePin->configuration.pinBehavior != OUTPUT)
	{
		return ERROR;
	}
	
	*(thePin->outputRegPtr) |= (1U << thePin->configuration.pinNumber);
	
	return OK;
}

static boolean SetOutputLow(GPIO_Pin* thePin)
{
	
	if (thePin->configuration.pinBehavior != OUTPUT)
	{
		return ERROR;
	}
	
	*(thePin->outputRegPtr) &= ~(1U << thePin->configuration.pinNumber);
	
	return OK;
}

static boolean ToggleOutput(GPIO_Pin* thePin)
{
		
	if (thePin->configuration.pinBehavior != OUTPUT)
	{
		return ERROR;
	}
	
	*(thePin->outputRegPtr) ^= (1U << thePin->configuration.pinNumber);
	
	return OK;
}

