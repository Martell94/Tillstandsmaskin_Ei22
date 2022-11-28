#ifndef HEADER_H_ //Header guards.
#define HEADER_H_

#define F_CPU 16000000UL //16 MHz klock.
#include <avr/io.h> //Standardbibliotek f�r avr-chip. 
#include <avr/interrupt.h> //Inkluderar interrupt-funktionerna.
#include <util/delay.h> //Inkluderar delay-funktionen.

#define LEDG PORTB0 //Definierar lysdioerna. G/Y respektive R motsvarar f�rgen.
#define LEDY PORTB1
#define LEDR PORTB2

#define B_RESET PORTD2 //Definierar samtliga tryckknappar.
#define B_2B PORTD3
#define B_1B PORTB3
#define B_1F PORTB4
#define B_2F PORTB5

#define LEDG_ON PORTB |= (1<<LEDG) //Definierar t�nt l�ge.
#define LEDY_ON PORTB |= (1<<LEDY)
#define LEDR_ON PORTB |= (1<<LEDR)

#define LEDG_OFF PORTB &= ~(1<<LEDG) //Definierar sl�ckt l�ge.
#define LEDY_OFF PORTB &= ~(1<<LEDY)
#define LEDR_OFF PORTB &= ~(1<<LEDR)

#define LEDS_ON PORTB |= (1<<LEDG)|(1<<LEDY)|(1<<LEDR)//Definierar att alla lysdioderna lyser, eller att alla �r sl�ckta.
#define LEDS_OFF PORTB &= ~((1<<LEDG)|(1<<LEDY)|(1<<LEDR)) // Inversen av LEDS_ON


#define B_2B_PRESSED (PIND & (1<<B_2B))//Definierar intryckt l�ge p� knapparna.
#define B_1B_PRESSED (PINB & (1<<B_1B))
#define B_1F_PRESSED (PINB & (1<<B_1F))
#define B_2F_PRESSED (PINB & (1<<B_2F))

typedef enum { //H�r skapar vi en state_t-typ som anv�nds f�r att indikera vilket tillst�nd lysdioderna ska vara i. 
	STATE_OFF, //H�r ska lysdioden vara sl�ckt.
	STATE_ON, //H�r ska lysdioden vara t�nd.
	STATE_SLOW, //H�r ska lysdioderna blinka med 500ms mellanrum.
	STATE_MEDIUM, //H�r ska lysdioderna blinnka med 250ms mellanrum.
	STATE_FAST //H�r ska lysdioderna blinka med 50ms mellanrum. 
} state_t;

void setup (void); //Inkluderar samtliga headers fr�n de olika filerna.
void fsm_reset (void);
void fsm_update (void);
void fsm_update_blink_speed(void);

void led_pattern(const volatile uint16_t* blink_ms);
void delay_ms(const volatile uint16_t* blink_ms);

#endif // HEADER_H_