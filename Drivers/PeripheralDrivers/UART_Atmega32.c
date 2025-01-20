#include "UART_Atmega32.h"

//default to Arduino oscillator
#ifndef F_CPU
#define F_CPU 16000000UL
#warning "F_CPU not defined! Assuming 16MHz."
#endif

#ifndef BAUD
#define BAUD 9600
#warning "BAUD not defined! Assuming 9600"
#endif

#include <util/setbaud.h>   //BAUD registers calculations


static boolean SendChar(UART_Peripheral* UartPeripheral, uint8 character);


boolean Init_UART(UART_Peripheral* uart)
{
	uart->UCSR0A_RegPtr = &UCSR0A;
	uart->UCSR0B_RegPtr = &UCSR0B;
	uart->UCSR0C_RegPtr = &UCSR0C;
	uart->UBRR0L_H_RegPtr->UBRR0_L = &UBRR0L;
	uart->UBRR0L_H_RegPtr->UBRR0_H = &UBRR0H;
	uart->Buffer_RegPtr = &UDR0;
	
//	// Making sure i'm off
//	uart->UCSR0B_RegPtr->inBits.TXEN0_Fld = OFF;
//	uart->UCSR0B_RegPtr->inBits.RXEN0_Fld = OFF;
	
	
	

	// char size
	if (uart->configuration.SizeOfChar == EIGHT_BIT_CHAR)
	{
		uart->UCSR0C_RegPtr->inBits.UCSZ00_Alias_UCPHA0_Fld = ON;
		uart->UCSR0C_RegPtr->inBits.UCSZ01_Alias_UDORD0_Fld = ON;
		uart->UCSR0B_RegPtr->inBits.UCSZ02_Fld = OFF;
	}
	
	// Double speed
//	if (uart->configuration.speedDouble == NORMAL_SPEED)
//	{
//		uart->UCSR0A_RegPtr->inBits.U2X0_Fld = OFF;
//	}
	
	// Stop bit
	if (uart->configuration.stopBit == JUST_ONE)
	{
		uart->UCSR0C_RegPtr->inBits.USBS0_Fld = OFF;
	}
	else if (uart->configuration.stopBit == TWO)
	{
		uart->UCSR0C_RegPtr->inBits.USBS0_Fld = ON;
	}
	
	// Parity
//	if (uart->configuration.parity == NONE_P )
//	{
//		uart->UCSR0C_RegPtr->inBits.UPM0_0_1_Fld = NONE_P;
//	}
//	else if (uart->configuration.parity == ODD)
//	{
//		uart->UCSR0C_RegPtr->inBits.UPM0_0_1_Fld = ODD;
//	}
//	else if (uart->configuration.parity == EVEN )
//	{
//		uart->UCSR0C_RegPtr->inBits.UPM0_0_1_Fld = EVEN;
//	}
	
	// Uart or usart or master SPI
//	if (uart->configuration.SyncroAsyncroOrSPI == ASYNCRONUS )
//	{
//		uart->UCSR0C_RegPtr->inBits.UMSEL0_0_1_Fld = ASYNCRONUS;
//	}
//	else if (uart->configuration.SyncroAsyncroOrSPI == SYNCRONUS)
//	{
//		uart->UCSR0C_RegPtr->inBits.UMSEL0_0_1_Fld  = SYNCRONUS;
//	}
//	else if (uart->configuration.SyncroAsyncroOrSPI == MASTER_SPI)
//	{
//		uart->UCSR0C_RegPtr->inBits.UMSEL0_0_1_Fld  = MASTER_SPI;
//	}
	
	
	
	// baudrate
	
	//uart->UBRR0L_H_RegPtr->UBRR0_L = UBRRH_VALUE;   // Low byte
	//uart->UBRR0L_H_RegPtr->UBRR0_L = UBRRL_VALUE;  // High byte
	
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	
	  #if USE_2X
	  UCSR0A |= (1 << U2X0);
	  #endif

	
	
//	// interrupt management
//	if (uart->configuration.mode == INTERRUPT)
//	{
//		uart->UCSR0B_RegPtr->inBits.RXCIE0_Fld = ON;
//		uart->UCSR0B_RegPtr->inBits.TXCIE0_Fld = ON;
//		uart->UCSR0B_RegPtr->inBits.UDRIE0_Fld = ON;
//	}
//	else if (uart->configuration.mode == POLLED)
//	{
//		uart->UCSR0B_RegPtr->inBits.RXCIE0_Fld = OFF;
//		uart->UCSR0B_RegPtr->inBits.TXCIE0_Fld = OFF;
//		uart->UCSR0B_RegPtr->inBits.UDRIE0_Fld = OFF;
//	}
	
	// enableing
	uart->UCSR0B_RegPtr->inBits.TXEN0_Fld = ON;
	uart->UCSR0B_RegPtr->inBits.RXEN0_Fld = ON;
	
	
	uart->self = (void*)uart;
	uart->TransmitBuffer = &SendChar;
	
}





static boolean SendChar(UART_Peripheral* UartPeripheral, uint8 character)
{
	while (!(UartPeripheral->UCSR0A_RegPtr->inBits.UDRE0_Fld))
	{
		
	}
	
	*UartPeripheral->Buffer_RegPtr = character;
	
	return TRUE;
	
}


