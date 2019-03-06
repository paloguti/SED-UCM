/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "stdio.h"
/*--- funciones externas ---*/
extern void leds_off();
extern void led1_on();
extern void keyboard_init();
extern void timer_init();

int contador;

//Declarar funciones externas de inicialización

/*--- declaracion de funciones ---*/
void Main(void);
/*--- codigo de funciones ---*/
void Main(void)
{
	contador = 0;
	/* Inicializar controladores */
	sys_init(); // Inicializacion de la placa, interrupciones y puertos
	// Inicializacion del temporizador
	// Inicialización del teclado matricial

	button_init();
	Eint4567_init();
	keyboard_init();
	timer_init();

	leds_off();
	//leds_on();

	while (1); // espera

}
