#include "header.h" //inkluderar v�r headerfil.

ISR (INT0_vect){ //Vid avbrott p� pin 2 ska denna funktion k�ras.
	fsm_reset();
}

ISR (INT1_vect){ //Vid avbrott p� pin 3 ska denna funktion k�ras.
	fsm_update();
}

ISR (PCINT0_vect){ //Vid avbrott p� pin 11-13 ska denna funktion k�ras.
	
	if (B_1B_PRESSED || B_1F_PRESSED || B_2F_PRESSED){
		fsm_update();
	}
}
