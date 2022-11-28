#include "header.h"//inkluderar vår headerfil.

static volatile uint16_t blink_ms = 0; //Nollställer blinktiden vid initiering. Dessa variabler är static, då de bara används här. 
static state_t LED_state = STATE_OFF; //LEDS av vid start.


void fsm_reset (void){ //Defaultar maskinens läge till STATE_OFF.
	
	LED_state = STATE_OFF;
	LEDS_OFF;
	blink_ms = 0; //Nollställer blinktiden.
	return; 
}

void fsm_update(){ //Uppdaterar tillståndet baserat på LED_state-variabeln.

	switch (LED_state){ //Beroende på vilken knapp som trycks ned vid ett särskilt tillstånd (e.g: STATE_OFF) hoppar vi till ett annat tillstånd. 

		case STATE_OFF:{ //Denna switch/case-sats utgör grunden för tillståndsmaskinen.
			
			if (B_1F_PRESSED){ //Ifall knappen som avancerar tillståndet ett steg trycks ner, så ska dioderna börja blinka sakta, etc etc.
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
		default:{ //Skulle något inte stämma kör vi reset-funktionen.
			fsm_reset();
			break;
		}
	}
	fsm_update_blink_speed(); //Skickar oss vidare till funktionen. 
	return;
}

void fsm_update_blink_speed(){ //Denna funktion uppdaterar blinkhastigheten.

	if (LED_state == STATE_OFF){ //Sätter LED_state till OFF, släcker dioderna och nollställer blink_ms.
		LEDS_OFF;
		blink_ms = 0;
	}
	else if (LED_state == STATE_ON){ //Sätter LED_state till ON, släcker dioderna och nollställer blink_ms. 
		LEDS_ON;
		blink_ms = 0;
	}
	else if (LED_state == STATE_SLOW){
		blink_ms = 500; //Sätter blinkhastighet till 500ms.
		led_pattern(&blink_ms);
	}
	else if (LED_state == STATE_MEDIUM){
		blink_ms = 250;  //Sätter blinkhastighet till 250ms.
		led_pattern(&blink_ms);
	}
	else if (LED_state == STATE_FAST){
		blink_ms = 50;  //Sätter blinkhastighet till 50ms.
		led_pattern(&blink_ms);
	}
	return;
}

void led_pattern (const volatile uint16_t* blink_ms){//Definierar blinkmönstret. 
	
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

void delay_ms (const volatile uint16_t* blink_ms){ //Delay-funktion. Genom denna kan vi ändra delayvärdet med pekare. 
	
	for (int i= 0; i < *blink_ms; i++ ){//Enkel for-loop som använder blink_ms för att köra 1ms delay per varv. 
		_delay_ms(1);
	}
	return;
}
