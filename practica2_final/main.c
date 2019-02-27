/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "stdio.h"
/*--- funciones externas ---*/
extern void leds_off();
extern void led1_on();
extern void keyboard_init();

//Declarar funciones externas de inicializaci�n

/*--- declaracion de funciones ---*/
void Main(void);
/*--- codigo de funciones ---*/
void Main(void)
{
	/* Inicializar controladores */
	sys_init(); // Inicializacion de la placa, interrupciones y puertos
	// Inicializacion del temporizador
	// Inicializaci�n del teclado matricial

	button_init();
	Eint4567_init();
	keyboard_init();
	timer_init();

	leds_off();
	led1_on();
	while (1); // espera

}