#include "header.h"

//////////////////////////////////////////////////////////// FUNKTIONER ///////////////////////////////////////////////////////////

static void leds_blink(const volatile uint16_t* blink_speed_ms);
static void delay_ms(const volatile uint16_t* delay_time_ms);

//////////////////////////////////////////////////////////// ENUMERATIONER ///////////////////////////////////////////////////////////

static enum state state = STATE_OFF;         // Lagrar tillstånden
static uint16_t speed_ms = 0;                // Lysdiodernas blinkhastighet i ms.



void fsm_reset(void)
{
	state = STATE_OFF;
	speed_ms = 0;
	LEDS_OFF;
	return;
}

void fsm_update(void)
{
	switch (state)
	{
		case STATE_OFF:
		{
			if (ONEBACK_BUTTON_PRESSED)
			{
				state = STATE_ON;
			}
			else if (ONEFORWARD_BUTTON_PRESSED)
			{
				state = STATE_SLOW;
			}
			else if (TWOFORWARD_BUTTON_PRESSED)
			{
				state = STATE_MEDIUM;
			}
			else if (TWOBACK_BUTTON_PRESSED)
			{
				state = STATE_FAST;
			}
			else if (RESET_BUTTON_PRESSED)
			{
				fsm_reset();
			}
			
			break;
		}
		
		case STATE_SLOW:
		{
			if (ONEBACK_BUTTON_PRESSED)
			{
				state = STATE_OFF;
			}
			else if (ONEFORWARD_BUTTON_PRESSED)
			{
				state = STATE_MEDIUM;
			}
			else if (TWOFORWARD_BUTTON_PRESSED)
			{
				state = STATE_FAST;
			}
			else if (TWOBACK_BUTTON_PRESSED)
			{
				state = STATE_ON;
			}
			else if (RESET_BUTTON_PRESSED)
			{
				fsm_reset();
			}
			
			break;
		}
		
		case STATE_MEDIUM:
		{
			if (ONEBACK_BUTTON_PRESSED)
			{
				state = STATE_SLOW;
			}
			else if (ONEFORWARD_BUTTON_PRESSED)
			{
				state = STATE_FAST;
			}
			else if (TWOFORWARD_BUTTON_PRESSED)
			{
				state = STATE_ON;
			}
			else if (TWOBACK_BUTTON_PRESSED)
			{
				state = STATE_OFF;
			}
			else if (RESET_BUTTON_PRESSED)
			{
				fsm_reset();
			}
			
			break;
		}
		
		case STATE_FAST:
		{
			if (ONEBACK_BUTTON_PRESSED)
			{
				state = STATE_MEDIUM;
			}
			else if (ONEFORWARD_BUTTON_PRESSED)
			{
				state = STATE_ON;
			}
			else if (TWOFORWARD_BUTTON_PRESSED)
			{
				state = STATE_OFF;
			}
			else if (TWOBACK_BUTTON_PRESSED)
			{
				state = STATE_SLOW;
			}	
			else if (RESET_BUTTON_PRESSED)
			{
				fsm_reset();
			}
			
			break;
		}
		
		case STATE_ON:
		{
			if (ONEBACK_BUTTON_PRESSED)
			{
				state = STATE_FAST;
			}
			else if (ONEFORWARD_BUTTON_PRESSED)
			{
				state = STATE_OFF;
			}
			else if (TWOFORWARD_BUTTON_PRESSED)
			{
				state = STATE_SLOW;
			}
			else if (TWOBACK_BUTTON_PRESSED)
			{
				state = STATE_MEDIUM;
			}
			else if (RESET_BUTTON_PRESSED)
			{
				fsm_reset();
			}
			
			break;
		}
		
		default:               // om något går fel så sker en återställning.	
		{
			fsm_reset();
			break;
		}
	}
	
	                           // Om vi går till ett tillstånd utan blinkning så avbryts eventuell blinkning direkt (delay-tiden sätts till 0).
	if (state == STATE_OFF || state == STATE_ON) 
	{
		speed_ms = 0;
	}
	
	fsm_set_output();          // uppdaterar lysdioderna efter det nya tillståndet
	return;
}


void fsm_set_output(void)
{
	LEDS_OFF;
	
	if (state == STATE_OFF)
	{
		LEDS_OFF;
	}
	else if (state == STATE_ON)
	{
		LEDS_ON;
	}
	else if (state == STATE_SLOW)
	{
		speed_ms =	500;
		leds_blink(&speed_ms);
	}
	else if (state == STATE_MEDIUM)
	{
		speed_ms = 250;
		leds_blink(&speed_ms);
	}
	else if (state == STATE_FAST)
	{
		speed_ms = 50;
		leds_blink(&speed_ms);
	}
	return;
}


static void leds_blink(const volatile uint16_t* blink_speed_ms) // Blinkfunktionen.
{	
	LED1_ON;
	LED2_OFF;
	LED3_OFF;
	delay_ms(blink_speed_ms);

	LED1_OFF;
	LED2_ON;
	LED3_OFF;
	delay_ms(blink_speed_ms);

	LED1_OFF;
	LED2_OFF;
	LED3_ON;
	delay_ms(blink_speed_ms);
	
	LED3_OFF;
	return;
}

static void delay_ms(const volatile uint16_t* delay_time_ms) // delayfunktionen.
{
	for (uint16_t i = 0; i < *delay_time_ms; ++i)
	{
		_delay_ms(1);
	}
	return;
}