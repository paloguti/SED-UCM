/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "def.h"
/*--- variables globales ---*/
int symbol = 0;
/*--- funciones externas ---*/
//extern void D8Led_Symbol(int value);
/*--- declaracion de funciones ---*/
void Eint4567_ISR(void) __attribute__ ((interrupt ("IRQ")));
void Eint4567_init(void);
void button_init();
extern void leds_switch();
extern void D8Led_symbol(int value);
extern int contador;

void button_init(){
	/*rPCONG = rPCONG & ~(0x01<<12);
	rPCONG = rPCONG & ~(0x01<<13);
	rPCONG = rPCONG & ~(0x01<<14);
	rPCONG = rPCONG & ~(0x01<<15);*/
	rPCONG = rPCONG | 0xff00;

	rPUPG = 0;
}

/*--- codigo de funciones ---*/
void Eint4567_init(void)
{
/* Configuracion del controlador de interrupciones */
	// Borra EXTINTPND escribiendo 1s en el propio registro
	rEXTINTPND = 0Xf;
	// Borra INTPND escribiendo 1s en I_ISPC
	rI_ISPC = 0x3ffffff;
	// Configura las lineas como de tipo IRQ mediante INTMOD
	rINTMOD = 0x0;
	// Habilita int. vectorizadas y la linea IRQ (FIQ no) mediante INTCON
	rINTCON = 0x1;
	// Enmascara todas las lineas excepto Eint4567 y el bit global (INTMSK)
	rINTMSK = ~(BIT_EINT4567 | BIT_GLOBAL);
	// Establecer la rutina de servicio para Eint4567
	pISR_EINT4567 = (unsigned)Eint4567_ISR;
/* Configuracion del puerto G */
	// Establece la funcion de los pines (EINT7-EINT0)
	rPCONG = 0xff3f;
	//Habilita las resistencias de pull-up
	rPUPG = 0x0;
	// Configura las lineas de int. como de flanco de bajada mediante EXTINT
	rEXTINT = 0x22220000;
/* Por precaucion, se vuelven a borrar los bits de INTPND y EXTINTPND */
	rEXTINTPND = 0xf;
	rI_ISPC = 0x3ffffff;
}

/*
DESCOMENTAR PARA LA PARTE DEL 8-SEGMENTOS
COMENTAR PARA LA PRIMERA PARTE CON INTERRUPCIONES
*/
int which_int;
void Eint4567_ISR(void)
{
	/*Identificar la interrupcion*/
	which_int = rEXTINTPND;
	//leds_off();
	int aux2 = rPDATG & 0x00000080; //1100 0000
	int aux3 = rPDATG & 0x00000040; //1100 0000
	if ( aux2 == 0 || aux3 == 0) { // si alguno está pulsado
		while(aux2 == 0 || aux3 == 0){
			aux2 = rPDATG & 0x00000080; //1100 0000
			aux3 = rPDATG & 0x00000040; //1100 0000
		}
	}
	/* Actualizar simbolo*/
	switch (which_int) {
	//si la interr viene de bit 2 a 1 -> EINT6
	   case 4 :
		//Conmutamos LEDs
		//led1_on();
		contador++;
	    break;

		//si la interr viene de bit 3 a 1 -> EINT7
	   case 8  :
	    //statement(s);
		//led2_on();
		contador--;
	    break;

	}
	// muestra el simbolo en el display
	int num = contador;
	/*if (contador < 0) {
		num = 16 + contador;
	}
	else {
		num = contador;
	}*/
	num &= ((unsigned int)(~0x0))>>(32-4);
	D8Led_symbol(num);
	// espera 100ms para evitar rebotes
	DelayMs(100);
	// borra los bits en EXTINTPND
	// borra el bit pendiente en INTPND
	rEXTINTPND = 0xC;
	//Borramos INTPND usando ISPC
	rI_ISPC = BIT_EINT4567;
}


