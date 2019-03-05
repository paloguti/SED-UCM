/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "44blib.h"
/*--- funciones externas ---*/
extern void leds_switch();
/*--- declaracion de funciones ---*/
void timer_ISR(void) __attribute__ ((interrupt ("IRQ")));
void timer_ISR1(void) __attribute__ ((interrupt ("IRQ")));
void timer_ISR2(void) __attribute__ ((interrupt ("IRQ")));
void timer_init(void);
/*--- codigo de las funciones ---*/

void timer_init(void)
{
	/* Configuracion del controlador de interrupciones */	
	rINTMOD=0x0;// Configurar las lineas como de tipo IRQ	
	rINTCON=0x1;// Habilitar int. vectorizadas y la linea IRQ (FIQ no)	
	rINTMSK = rINTMSK & ~(BIT_TIMER0 | BIT_TIMER1 | BIT_GLOBAL);// Enmascarar todas las lineas excepto Timer0 y el bit global
	/* Establece la rutina de servicio para TIMER0 */
	pISR_TIMER0=(unsigned)timer_ISR;
	pISR_TIMER1=(unsigned)timer_ISR1;
	//pISR_TIMER2=(unsigned)timer_ISR2;

	/* Configurar el Timer0 (el resto de los timers se dejan a la
	configuración por defecto) */
	rTCFG0=0xFF;// pre-escalado = 255
	rTCFG0 &= 0xFFFFF0;// divisor = 1/2
	rTCNTB0=65535;
	rTCMPB0=12800;
	
	rTCNTB1 = 0;
	rTCMPB1=13000; //Comparación cuando TCNTB1 llegue a este numero para

	rTCON=rTCON| (0x01<<1);// establecer manual_update
	rTCON=rTCON & ~(0x01<<1);// DESACTIVA manual_update
	rTCON=rTCON|(0x01<<3);//activar modo auto-reload
	rTCON=rTCON|(0x01<<0);// iniciar timer

	rTCON=rTCON | (0x01<<9); //establecer manual_update en timer1
	rTCON=rTCON & ~(0x01<<9); //DESACTIVA manual_update en timer1
	rTCON=rTCON | (0x01<<11); //activar modo auto-reload
	rTCON=rTCON | (0x01<<8); //iniciar timer1
}

void timer_ISR(void)
{
	leds_switch();
	rI_ISPC = BIT_TIMER0;
}

void timer_ISR1(void)
{
	leds_off();
	rI_ISPC = BIT_TIMER1;
}
void timer_ISR2(void)
{
	rI_ISPC = BIT_TIMER2;
}
