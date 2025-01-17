#include "GPIO_Atmega32.h"

GPIO_Atmega32_Mem GPIO_Mem;

static boolean PollPinStatusPullUp(void* wichPin);
static boolean SetOutputLow(void* wichPin);
static boolean SetOutputHigh(void* wichPin);
static boolean ToggleOutput(void* wichPin);


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


static boolean PollPinStatusPullUp(void* wichPin)
{
	
	GPIO_Pin* thePin = (GPIO_Pin*)wichPin;
	

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

static boolean SetOutputHigh(void* wichPin)
{

	GPIO_Pin* thePin = (GPIO_Pin*)wichPin;
	
	if (thePin->configuration.pinBehavior != OUTPUT)
	{
		return ERROR;
	}
	
	*(thePin->outputRegPtr) |= (1U << thePin->configuration.pinNumber);
	
	return OK;
}

static boolean SetOutputLow(void* wichPin)
{
	
	GPIO_Pin* thePin = (GPIO_Pin*)wichPin;
	
	if (thePin->configuration.pinBehavior != OUTPUT)
	{
		return ERROR;
	}
	
	*(thePin->outputRegPtr) &= ~(1U << thePin->configuration.pinNumber);
	
	return OK;
}

static boolean ToggleOutput(void* wichPin)
{
	
	GPIO_Pin* thePin = (GPIO_Pin*)wichPin;
	
	if (thePin->configuration.pinBehavior != OUTPUT)
	{
		return ERROR;
	}
	
	*(thePin->outputRegPtr) ^= (1U << thePin->configuration.pinNumber);
	
	return OK;
}

