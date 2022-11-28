#include "header.h" //Inkluderar vår headerfil.

int main(void){ //Programmets startpunkt

	setup(); //Denna funktion initierar samtliga portar, variabler etc.
	
    while (1)
    {
		fsm_update_blink_speed();
    }
	
}

