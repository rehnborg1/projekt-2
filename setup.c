#include "header.h"

//////////////////////////////////////////////////////////// FUNKTIONER ///////////////////////////////////////////////////////////

static inline void init_ports(void);          
static inline void init_interrupts(void);


void setup(void)
{
	init_ports();
	init_interrupts();
	fsm_reset();
	return;
}


								//Sätter lysdiodernas pinnar till utportar och sätter tryckknapparnas
								//pinnar till aktiva inportar (insignalerna blir alltid 0 eller 1).
static inline void init_ports(void)
{
	DDRB = (1 << LED1) | (1 << LED2) | (1 << LED3);
	PORTB = (1 << ONEFORWARD_BUTTON ) | (1 << ONEBACK_BUTTON) | (1 << TWOFORWARD_BUTTON);
	PORTD = (1 << TWOBACK_BUTTON) | (1 << RESET_BUTTON);
	return;
}

                                // Aktiverar PCI-avbrott på pin 12 - 13,
                                // externt avbrott INT0 och INT1 på pin 2 och 3 på fallande respektive stigande flank
static inline void init_interrupts(void)
{
	asm("SEI");
	PCICR = (1 << PCIE0);
	PCMSK0 = (1 << PCINT3) |(1 << PCINT4) | (1 << PCINT5);
	
	EICRA = (1 << ISC01) | (1 << ISC10) | (1 << ISC11);
	EIMSK = (1 << INT0) | (1 << INT1);
	return;
}