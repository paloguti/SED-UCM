/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "stdio.h"

/*--- funciones externas ---*/
extern void leds_off();
extern void led1_on();
//extern void leds_switch();
extern void sys_init();
extern void button_init();
extern void Eint4567_init(void);

int contador;


/*--- declaracion de funciones ---*/
//void Main(void);

//DESCOMENTAR PARA PROBAR EN APARTADO1
/*--- codigo de funciones ---*/
/*--- MAIN AP: 1 ---*/
/*void Main(void)
{
	/* Inicializar controladores */
	/*sys_init(); // Inicializacion de la placa, interrupciones y puertos
	/*button_init(); // Inicializar botones
	/* Establecer valor inicial de los LEDs */
	/*leds_off();
	led1_on();
	while (1){
		int aux2 = rPDATG & 0x00000080; //1100 0000
		int aux3 = rPDATG & 0x00000040; //1100 0000
		if ( aux2 == 0 || aux3 == 0) { // si alguno está pulsado
			while(aux2 == 0 || aux3 == 0){
				aux2 = rPDATG & 0x00000080; //1100 0000
				aux3 = rPDATG & 0x00000040; //1100 0000
			}
			leds_switch();
		}
		DelayMs(100);
	}
}*/


/*--- MAIN AP: 2 ---*/
/*void Main(void)
{
	/* Inicializar controladores */
	/*sys_init(); // Inicializacion de la placa, interrupciones y puertos
	button_init(); // Inicializar botones
	Eint4567_init();
	/* Establecer valor inicial de los LEDs */
	/*leds_off();
	led1_on();
	while (1){}
}*/

/*--- MAIN AP: 3 ---*/
void Main(void)
{
	/* Inicializar controladores */
	contador = 0;
	sys_init(); // Inicializacion de la placa, interrupciones y puertos
	D8Led_init();
	button_init(); // Inicializar botones
	Eint4567_init();
	/* Establecer valor inicial de los LEDs */
	leds_off();
	while (1){}
}
