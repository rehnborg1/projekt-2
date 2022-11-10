#include "header.h"


                  // Avbrottsrutin, som anropas vid nedtryckning av reset-knappen ansluten till pin 2 (PORTD2). 
                  // Vid reset så återställstillståndsmaskinen till startläget (lysdioderna släcks).
ISR (INT0_vect)
{
	fsm_reset();
	return;

}


                  // Avbrottsrutin, som anropas vid nedtryckning av TWO_BACK_BUTTON ansluten till pin 3 (PORTD2).
                  // Vid nedtryckning uppdateras aktuellt tillstånd två steg bakåt.
ISR (INT1_vect)
{
	fsm_update();
	return;		
}
                   
				   
				   // Avbrottsrutin för PCI-avbrott på I/O-port B, som anropas vid uppsläppning eller nedtryckning av tryckknappar 
				   // anslutna till pin 12 - 13 (PORTB4 - PORTB4). 
                   // Om någon av dessa knappar trycks ned så uppdateras tillståndsmaskinen.
ISR (PCINT0_vect)
{
	if (ONEFORWARD_BUTTON_PRESSED || ONEBACK_BUTTON_PRESSED || TWOFORWARD_BUTTON_PRESSED)
	{
		fsm_update();
		
	}
}