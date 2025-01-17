#ifndef GPIO_ATMEGA32_H
#define GPIO_ATMEGA32_H
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
	B = 0U,
	C,
	D,
	PORT_PIN_CNT
}Port;

typedef enum
{
	N1 = 0U,
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
}PinConf;


typedef struct
{
	uint8* self;
	PinConf configuration;
	uint8 debounceCnt;
	pFunc_voidP_voidP PollPinStatus;
}GPIO_Pin;

uint8 Init_GPIO(GPIO_Pin* wichPin);


#endif // GPIO_ATMEGA32_H