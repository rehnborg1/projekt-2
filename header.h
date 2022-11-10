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

#define LED1_ON PORTB |= (1 << LED1) // T�nder lysdiod 1.
#define LED2_ON PORTB |= (1 << LED2) // T�nder lysdiod 2.
#define LED3_ON PORTB |= (1 << LED3) // T�nder lysdiod 3.

#define LED1_OFF PORTB &= ~(1 << LED1) // Sl�cker lysdiod 1.
#define LED2_OFF PORTB &= ~(1 << LED2) // Sl�cker lysdiod 2.
#define LED3_OFF PORTB &= ~(1 << LED3) // Sl�cker lysdiod 3.

#define LEDS_ON PORTB |= (1 << LED1) | (1 << LED2) | (1 << LED3)     // T�nder lysdioderna.
#define LEDS_OFF PORTB &= ~((1 << LED1) | (1 << LED2) | (1 << LED3)) // Sl�cker lysdioderna.

//////////////////////////////////////////////////////////// KNAPPAR /////////////////////////////////////////////////////////

#define ONEBACK_BUTTON 3       // Ett steg bak�t -knapp ansluten till pin 11 / PORTB3.
#define ONEFORWARD_BUTTON 4    // Ett steg fram�t -knapp ansluten till pin 12 / PORTB4.
#define TWOFORWARD_BUTTON 5    // Tv� steg fram�t -knapp ansluten till pin 13 / PORTB5.
#define RESET_BUTTON 2          // Reset -knapp ansluten till pin 2 / PORTD2.
#define TWOBACK_BUTTON  3       // Tv� steg bak�t -knapp ansluten till pin 3 /PORTD3.

#define ONEBACK_BUTTON_PRESSED (PINB & (1 << ONEBACK_BUTTON))       // Indikerar nedtryckning av ett steg bak�t-knappen.
#define ONEFORWARD_BUTTON_PRESSED (PINB & (1 << ONEFORWARD_BUTTON)) // Indikerar nedtryckning av ett steg fram�t-knappen.
#define TWOFORWARD_BUTTON_PRESSED (PINB & (1 << TWOFORWARD_BUTTON)) // Indikerar nedtryckning av tv� steg fram�t-knappen.
#define RESET_BUTTON_PRESSED (PIND & (1 << RESET_BUTTON))           // Indikerar nedtryckning av reset-knappen.
#define TWOBACK_BUTTON_PRESSED (PIND & (1 << TWOBACK_BUTTON))       // Indikerar nedtryckning av tv� steg bak�t-knappen.

//////////////////////////////////////////////////////////// BOOL ///////////////////////////////////////////////////////////

typedef enum { false, true } bool;
	
//////////////////////////////////////////////////////////// STATE ///////////////////////////////////////////////////////////

enum state
{
	STATE_OFF,      // Samtliga lysdioder h�lls sl�ckta kontinuerligt.
	STATE_SLOW,     // De tre lysdioderna blinkar i en slinga var 500:e millisekund.
	STATE_MEDIUM,   // De tre lysdioderna blinkar i en slinga var 250:e millisekund.
	STATE_FAST,     // De tre lysdioderna blinkar i en slinga var 50:e millisekund.
	STATE_ON        // Samtliga lysdioder h�lls t�nda kontinuerligt.
};

//////////////////////////////////////////////////////////// FUNKTIONER //////////////////////////////////////////////////////


void setup(void);

void fsm_reset(void);

void fsm_update(void);

void fsm_set_output(void);

#endif /* HEADER_H_ */