#ifndef UART_ATMEGA32_H
#define UART_ATMEGA32_H

#ifndef F_CPU 
#pragma message(" Undefined F_CPU assuming 8MHZ")
#define F_CPU 8000000U
#endif

#include "PlatformTypes.h"
#include "GeneralDefines.h"
#include <avr/io.h>

// Config typedefs
typedef enum
{
	BAUD_9600 = 9600U,
	BAUD_ENUM_CNT
}Baud;


typedef enum
{
	NORMAL_SPEED = 0,
	DOUBLE_SPEED,
	SPEED_ENUM_CNT
}DblSpeed;


typedef enum
{
	
	NONE_P = 0U,
	EVEN = 2U,
	ODD = 3U,
	PARITYCHECK_ENUM_CNT
}ParityCheck;

typedef enum
{
	ASYNCRONUS = 0U,
	SYNCRONUS = 1U,
	MASTER_SPI = 3U,
	OPERATION_ENUM_CNT
}Operation;

typedef enum
{
	JUST_ONE = 0,
	TWO,
	STOPBIT_ENUM_CNT	
}StopBit;

typedef enum
{
	FIVE_BIT_CHAR = 0,
	SIX_BIT_CHAR,
	SEVEN_BIT_CHAR,
	EIGHT_BIT_CHAR,
	NINE_BIT_CHAR,
	CHAR_SIZE_ENUM_CNT
}CharSize;

typedef enum
{
	INTERRUPT = 0,
	POLLED,
	APPROACH_ENUM_CNT
}Approach;


typedef struct
{
	Baud baudRate;
	Approach mode;
	CharSize SizeOfChar;
	Operation SyncroAsyncroOrSPI;
	StopBit stopBit;
	ParityCheck parity;
	DblSpeed speedDouble;
}UartConf;


// Registers typedefs
typedef union
{
	struct
	{
		uint8 MPCM0C_Fld : 1;
		uint8 U2X0_Fld  : 1;
		uint8 UPE0_Fld  : 1;
		uint8 DOR0_Fld  : 1;
		uint8 FE0_Fld : 1;
		uint8 UDRE0_Fld : 1;
		uint8 TXC0_Fld : 1;
		uint8 RXC0_Fld : 1;
	}inBits;	
	
	uint8 inByte;
	
}UCSR0A_Def;

typedef union
{
	struct
	{
		uint8 TXB80_Fld   : 1;
		uint8 RXB80_Fld   : 1;
		uint8 UCSZ02_Fld  : 1;
		uint8 TXEN0_Fld   : 1;
		uint8 RXEN0_Fld   : 1;
		uint8 UDRIE0_Fld  : 1;
		uint8 TXCIE0_Fld  : 1;
		uint8 RXCIE0_Fld  : 1;
	}inBits;
	
	uint8 inByte;
}UCSR0B_Def;

typedef union
{
	struct
	{
		uint8 UCPOL0_Fld   : 1;
		uint8 UCSZ00_Alias_UCPHA0_Fld   : 1;
		uint8 UCSZ01_Alias_UDORD0_Fld  : 1;
		uint8 USBS0_Fld  : 1;
		uint8 UPM0_0_1_Fld   : 2;
		uint8 UMSEL0_0_1_Fld   : 2;
	}inBits;
	uint8 inByte;
}UCSR0C_Def;

typedef union
{
	uint16 UBRR0L_H   : 12;
	uint8 inByte[2];
}UBRR0L_H_Def;

typedef struct
{
	// Interface
	void* self;
	UartConf configuration;
	boolean (*ReceiveBuffer)(void* self);
	boolean (*TransmitBuffer)(void* self, uint8 character);
	
	
	 
	// Private
	uint8 receiveCnt;
	uint8 transmitCnt;
	uint8* Buffer_RegPtr;
	UCSR0A_Def* UCSR0A_RegPtr;
	UCSR0B_Def* UCSR0B_RegPtr;
	UCSR0C_Def* UCSR0C_RegPtr;
	UBRR0L_H_Def* UBRR0L_H_RegPtr;
	
}UART_Peripheral;


boolean Init_UART(UART_Peripheral* uart);


#endif //UART_ATMEGA32_H