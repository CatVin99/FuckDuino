#include <avr/io.h>
#include "GeneralDefines.h"
#include "GPIO_Atmega32.h"

int main(void)
{

	
	GPIO_Pin Button;
	GPIO_Pin LED;
	
	
	Button.configuration.pinBehavior = INPUT;
	Button.configuration.pinPort = D;
	Button.configuration.pinNumber = N2;
	Button.configuration.resistor = PULL_UP;
	
	LED.configuration.pinBehavior = OUTPUT;
	LED.configuration.pinPort = B;
	LED.configuration.pinNumber = N5;
	LED.configuration.resistor = NONE;
	
	Init_GPIO(&Button);
	Init_GPIO(&LED);

    while (TRUE) 
    {
		if ( Button.PollPinStatusFnc(Button.self) == TRUE)
		{
			LED.ToggleOutput(LED.self);
		}
    }
}

