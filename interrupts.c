#include "header.h"


                  // Avbrottsrutin, som anropas vid nedtryckning av reset-knappen ansluten till pin 2 (PORTD2). 
                  // Vid reset s� �terst�llstillst�ndsmaskinen till startl�get (lysdioderna sl�cks).
ISR (INT0_vect)
{
	fsm_reset();
	return;

}


                  // Avbrottsrutin, som anropas vid nedtryckning av TWO_BACK_BUTTON ansluten till pin 3 (PORTD2).
                  // Vid nedtryckning uppdateras aktuellt tillst�nd tv� steg bak�t.
ISR (INT1_vect)
{
	fsm_update();
	return;		
}
                   
				   
				   // Avbrottsrutin f�r PCI-avbrott p� I/O-port B, som anropas vid uppsl�ppning eller nedtryckning av tryckknappar 
				   // anslutna till pin 12 - 13 (PORTB4 - PORTB4). 
                   // Om n�gon av dessa knappar trycks ned s� uppdateras tillst�ndsmaskinen.
ISR (PCINT0_vect)
{
	if (ONEFORWARD_BUTTON_PRESSED || ONEBACK_BUTTON_PRESSED || TWOFORWARD_BUTTON_PRESSED)
	{
		fsm_update();
		
	}
}