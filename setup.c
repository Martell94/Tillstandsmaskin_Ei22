#include "header.h" //Inkluderar vår headerfil.

static inline void init_ports (void); //Här använder vi "inline"-nyckelordet för att dessa funktioner ska köras i serie.
static inline void init_interrupts (void);

void setup (void){ //Kallar på våra init-funktioner.
	
	init_ports();
	init_interrupts();
	return;
}

static inline void init_ports (void){//Initierar vi samtliga portar.
	
	DDRB = (1<<LEDG)|(1<<LEDY)|(1<<LEDR); //Ettställer portarna för lysdioderna.
	PORTD = (1<<B_RESET)|(1<<B_2B); //Aktiverar pullup-resistorer på pin 2 och 3
	PORTB = (1<<B_1B)|(1<<B_1F)|(1<<B_2F); //Aktiverar pullup-resistorer på pin 11-13.
	return;
}

static inline void init_interrupts(){ //Initierar interrupts.
	
		asm("SEI"); // Här använder vi ett assembler-kommando för att aktivera interrupts globalt.
		PCICR = (1<<PCIE0); //Initierar interrupts på från PCINT0-7. 
		PCMSK0 = (1<<PCINT3) | (1<<PCINT4) | (1<<PCINT5); //Initierar interrupts 3-5, motsvarande knapparna på pin 11-13.
		
		EICRA = (1<<ISC01) | (1<<ISC10) | (1<<ISC11); //Initierar interrupts på stigande flank.
		EIMSK = (1<<INT0) | (1<<INT1); //Initierar interrupts på pin 2 och 3.
		return;
}