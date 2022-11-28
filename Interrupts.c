#include "header.h" //inkluderar vår headerfil.

ISR (INT0_vect){ //Vid avbrott på pin 2 ska denna funktion köras.
	fsm_reset();
}

ISR (INT1_vect){ //Vid avbrott på pin 3 ska denna funktion köras.
	fsm_update();
}

ISR (PCINT0_vect){ //Vid avbrott på pin 11-13 ska denna funktion köras.
	
	if (B_1B_PRESSED || B_1F_PRESSED || B_2F_PRESSED){
		fsm_update();
	}
}
