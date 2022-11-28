#include "header.h" //Inkluderar v�r headerfil.

static inline void init_ports (void); //H�r anv�nder vi "inline"-nyckelordet f�r att dessa funktioner ska k�ras i serie.
static inline void init_interrupts (void);

void setup (void){ //Kallar p� v�ra init-funktioner.
	
	init_ports();
	init_interrupts();
	return;
}

static inline void init_ports (void){//Initierar vi samtliga portar.
	
	DDRB = (1<<LEDG)|(1<<LEDY)|(1<<LEDR); //Ettst�ller portarna f�r lysdioderna.
	PORTD = (1<<B_RESET)|(1<<B_2B); //Aktiverar pullup-resistorer p� pin 2 och 3
	PORTB = (1<<B_1B)|(1<<B_1F)|(1<<B_2F); //Aktiverar pullup-resistorer p� pin 11-13.
	return;
}

static inline void init_interrupts(){ //Initierar interrupts.
	
		asm("SEI"); // H�r anv�nder vi ett assembler-kommando f�r att aktivera interrupts globalt.
		PCICR = (1<<PCIE0); //Initierar interrupts p� fr�n PCINT0-7. 
		PCMSK0 = (1<<PCINT3) | (1<<PCINT4) | (1<<PCINT5); //Initierar interrupts 3-5, motsvarande knapparna p� pin 11-13.
		
		EICRA = (1<<ISC01) | (1<<ISC10) | (1<<ISC11); //Initierar interrupts p� stigande flank.
		EIMSK = (1<<INT0) | (1<<INT1); //Initierar interrupts p� pin 2 och 3.
		return;
}