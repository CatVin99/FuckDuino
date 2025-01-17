#ifndef GPIO_ATMEGA32_H
#define GPIO_ATMEGA32_H

#define DEBOUNCE_COUNTER_MAX 100U

#include "PlatformTypes.h"
#include "GeneralDefines.h"
#include <avr/io.h>

typedef struct
{
}GPIO_Atmega32_Mem;

typedef enum
{
	INPUT = 0U,
	OUTPUT,
	BEHAVIOR_PIN_CNT
}Behavior;

typedef enum
{
	PULL_UP = 0U,
	PULL_DOWN,
	NONE,
	PULL_UP_ENUM_CNT
}PullUpPullDOwn;

typedef enum
{
	B = 0U,
	C,
	D,
	PORT_PIN_CNT
}Port;


typedef enum
{
	N1 = 1U,
	N2,
	N3,
	N4,
	N5,
	N6,
	N7,
	NUMBER_PIN_CNT
}Number;

typedef struct
{
	Behavior pinBehavior;
	Port pinPort;
	Number pinNumber;
	PullUpPullDOwn resistor;
}PinConf;


typedef struct
{
	// Interface
	void* self;
	PinConf configuration;
	pFunc_voidP_voidP PollPinStatusFnc;
	pFunc_voidP_voidP SetOutputHighFnc;
	pFunc_voidP_voidP SetOutputLowFnc;
	
	
	// Private
	uint8* directionRegPtr;
	uint8* inputRegPtr;
	uint8* outputRegPtr;
	uint8 debounceCnt;
	
}GPIO_Pin;

uint8 Init_GPIO(GPIO_Pin* wichPin);


#endif // GPIO_ATMEGA32_H