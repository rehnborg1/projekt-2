#ifndef HEADER_H_
#define HEADER_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//////////////////////////////////////////////////////////// LEDS ////////////////////////////////////////////////////////////
#define LED1 0 // Lysdiod 1 ansluten till pin 8 / PORTB0.
#define LED2 1 // Lysdiod 2 ansluten till pin 9 / PORTB1.
#define LED3 2 // Lysdiod 3 ansluten till pin 10 / PORTB2.

#define LED1_ON PORTB |= (1 << LED1) // Tänder lysdiod 1.
#define LED2_ON PORTB |= (1 << LED2) // Tänder lysdiod 2.
#define LED3_ON PORTB |= (1 << LED3) // Tänder lysdiod 3.

#define LED1_OFF PORTB &= ~(1 << LED1) // Släcker lysdiod 1.
#define LED2_OFF PORTB &= ~(1 << LED2) // Släcker lysdiod 2.
#define LED3_OFF PORTB &= ~(1 << LED3) // Släcker lysdiod 3.

#define LEDS_ON PORTB |= (1 << LED1) | (1 << LED2) | (1 << LED3)     // Tänder lysdioderna.
#define LEDS_OFF PORTB &= ~((1 << LED1) | (1 << LED2) | (1 << LED3)) // Släcker lysdioderna.

//////////////////////////////////////////////////////////// KNAPPAR /////////////////////////////////////////////////////////

#define ONEBACK_BUTTON 3       // Ett steg bakåt -knapp ansluten till pin 11 / PORTB3.
#define ONEFORWARD_BUTTON 4    // Ett steg framåt -knapp ansluten till pin 12 / PORTB4.
#define TWOFORWARD_BUTTON 5    // Två steg framåt -knapp ansluten till pin 13 / PORTB5.
#define RESET_BUTTON 2          // Reset -knapp ansluten till pin 2 / PORTD2.
#define TWOBACK_BUTTON  3       // Två steg bakåt -knapp ansluten till pin 3 /PORTD3.

#define ONEBACK_BUTTON_PRESSED (PINB & (1 << ONEBACK_BUTTON))       // Indikerar nedtryckning av ett steg bakåt-knappen.
#define ONEFORWARD_BUTTON_PRESSED (PINB & (1 << ONEFORWARD_BUTTON)) // Indikerar nedtryckning av ett steg framåt-knappen.
#define TWOFORWARD_BUTTON_PRESSED (PINB & (1 << TWOFORWARD_BUTTON)) // Indikerar nedtryckning av två steg framåt-knappen.
#define RESET_BUTTON_PRESSED (PIND & (1 << RESET_BUTTON))           // Indikerar nedtryckning av reset-knappen.
#define TWOBACK_BUTTON_PRESSED (PIND & (1 << TWOBACK_BUTTON))       // Indikerar nedtryckning av två steg bakåt-knappen.

//////////////////////////////////////////////////////////// BOOL ///////////////////////////////////////////////////////////

typedef enum { false, true } bool;
	
//////////////////////////////////////////////////////////// STATE ///////////////////////////////////////////////////////////

enum state
{
	STATE_OFF,      // Samtliga lysdioder hålls släckta kontinuerligt.
	STATE_SLOW,     // De tre lysdioderna blinkar i en slinga var 500:e millisekund.
	STATE_MEDIUM,   // De tre lysdioderna blinkar i en slinga var 250:e millisekund.
	STATE_FAST,     // De tre lysdioderna blinkar i en slinga var 50:e millisekund.
	STATE_ON        // Samtliga lysdioder hålls tända kontinuerligt.
};

//////////////////////////////////////////////////////////// FUNKTIONER //////////////////////////////////////////////////////


void setup(void);

void fsm_reset(void);

void fsm_update(void);

void fsm_set_output(void);

#endif /* HEADER_H_ */