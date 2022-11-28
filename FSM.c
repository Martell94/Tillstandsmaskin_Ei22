#include "header.h"//inkluderar v�r headerfil.

static volatile uint16_t blink_ms = 0; //Nollst�ller blinktiden vid initiering. Dessa variabler �r static, d� de bara anv�nds h�r. 
static state_t LED_state = STATE_OFF; //LEDS av vid start.


void fsm_reset (void){ //Defaultar maskinens l�ge till STATE_OFF.
	
	LED_state = STATE_OFF;
	LEDS_OFF;
	blink_ms = 0; //Nollst�ller blinktiden.
	return; 
}

void fsm_update(){ //Uppdaterar tillst�ndet baserat p� LED_state-variabeln.

	switch (LED_state){ //Beroende p� vilken knapp som trycks ned vid ett s�rskilt tillst�nd (e.g: STATE_OFF) hoppar vi till ett annat tillst�nd. 

		case STATE_OFF:{ //Denna switch/case-sats utg�r grunden f�r tillst�ndsmaskinen.
			
			if (B_1F_PRESSED){ //Ifall knappen som avancerar tillst�ndet ett steg trycks ner, s� ska dioderna b�rja blinka sakta, etc etc.
				LED_state = STATE_SLOW;
			}
			else if (B_2F_PRESSED){
				LED_state = STATE_MEDIUM;
			}
			else if (B_1B_PRESSED){
				LED_state = STATE_ON;
			}
			else if (B_2B_PRESSED){
				LED_state = STATE_FAST;
			}			
			break;
		}
		case STATE_ON:{
			
			if (B_1F_PRESSED){
				LED_state = STATE_OFF;
			}
			else if (B_2F_PRESSED){
				LED_state = STATE_SLOW;
			}
			else if (B_1B_PRESSED){
				LED_state = STATE_FAST;
			}
			else if (B_2B_PRESSED){
				LED_state = STATE_MEDIUM;
			}
			break;
		}
		
		case STATE_SLOW:{
			
			if (B_1F_PRESSED){
				LED_state = STATE_MEDIUM;
			}
			else if (B_2F_PRESSED){
				LED_state = STATE_FAST;
			}
			else if (B_1B_PRESSED){
				LED_state = STATE_OFF;
			}
			else if (B_2B_PRESSED){
				LED_state = STATE_ON;
			}
			break;
		}
		
		case STATE_MEDIUM:{
			
			if (B_1F_PRESSED){
				LED_state = STATE_FAST;
			}
			else if (B_2F_PRESSED){
				LED_state = STATE_ON;
			}
			else if (B_1B_PRESSED){
				LED_state = STATE_SLOW;
			}
			else if (B_2B_PRESSED){
				LED_state = STATE_OFF;
			}
			break;
		}
		
		case STATE_FAST:{
				
			if (B_1F_PRESSED){
				LED_state = STATE_ON;
			}
			else if (B_2F_PRESSED){
				LED_state = STATE_OFF;
			}
			else if (B_1B_PRESSED){
				LED_state = STATE_MEDIUM;
			}
			else if (B_2B_PRESSED){
				LED_state = STATE_SLOW;
			}
			break;
		}
		default:{ //Skulle n�got inte st�mma k�r vi reset-funktionen.
			fsm_reset();
			break;
		}
	}
	fsm_update_blink_speed(); //Skickar oss vidare till funktionen. 
	return;
}

void fsm_update_blink_speed(){ //Denna funktion uppdaterar blinkhastigheten.

	if (LED_state == STATE_OFF){ //S�tter LED_state till OFF, sl�cker dioderna och nollst�ller blink_ms.
		LEDS_OFF;
		blink_ms = 0;
	}
	else if (LED_state == STATE_ON){ //S�tter LED_state till ON, sl�cker dioderna och nollst�ller blink_ms. 
		LEDS_ON;
		blink_ms = 0;
	}
	else if (LED_state == STATE_SLOW){
		blink_ms = 500; //S�tter blinkhastighet till 500ms.
		led_pattern(&blink_ms);
	}
	else if (LED_state == STATE_MEDIUM){
		blink_ms = 250;  //S�tter blinkhastighet till 250ms.
		led_pattern(&blink_ms);
	}
	else if (LED_state == STATE_FAST){
		blink_ms = 50;  //S�tter blinkhastighet till 50ms.
		led_pattern(&blink_ms);
	}
	return;
}

void led_pattern (const volatile uint16_t* blink_ms){//Definierar blinkm�nstret. 
	
	LEDS_OFF;

	LEDG_ON;
	delay_ms(blink_ms);
	LEDG_OFF;
	delay_ms(blink_ms);
	
	LEDY_ON;
	delay_ms(blink_ms);
	LEDY_OFF;
	delay_ms(blink_ms);
	
	LEDR_ON;
	delay_ms(blink_ms);
	LEDR_OFF;
	delay_ms(blink_ms);
	
	return;
}

void delay_ms (const volatile uint16_t* blink_ms){ //Delay-funktion. Genom denna kan vi �ndra delayv�rdet med pekare. 
	
	for (int i= 0; i < *blink_ms; i++ ){//Enkel for-loop som anv�nder blink_ms f�r att k�ra 1ms delay per varv. 
		_delay_ms(1);
	}
	return;
}
