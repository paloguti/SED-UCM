/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "44blib.h"
/*--- funciones externas ---*/
extern void leds_switch();
extern void D8Led_symbol(int value);

int led_state;
/*--- declaracion de funciones ---*/
void timer_ISR(void) __attribute__ ((interrupt ("IRQ")));
void timer_ISR1(void) __attribute__ ((interrupt ("IRQ")));
void timer_ISR2(void) __attribute__ ((interrupt ("IRQ")));
void timer_init(void);
void timer0_init(void);
void timer1_init(void);
void timer2_init(void);
/*--- codigo de las funciones ---*/

void timer0_init(void){

	rINTMOD=0x0;// Configurar las lineas como de tipo IRQ	
	rINTCON=0x1;// Habilitar int. vectorizadas y la linea IRQ (FIQ no)	
	rINTMSK = rINTMSK & ~(BIT_TIMER0 | BIT_GLOBAL);// Enmascarar todas las lineas excepto Timer0 y el bit global
	/* Establece la rutina de servicio para TIMER0 */
	pISR_TIMER0=(unsigned)timer_ISR;

	rTCFG0=0xFF;// pre-escalado = 255
	rTCFG1 &= 0xFFFFF1;// divisor = 1/4
	rTCNTB0=65535;
	rTCMPB0=12800;

	rTCON=rTCON| (0x01<<1);// establecer manual_update
	rTCON=rTCON & ~(0x01<<1);// DESACTIVA manual_update
	rTCON=rTCON|(0x01<<3);//activar modo auto-reload
	rTCON=rTCON|(0x01<<0);// iniciar timer
}

void timer1_init(void){
	rINTMOD=0x0;// Configurar las lineas como de tipo IRQ
	rINTCON=0x1;// Habilitar int. vectorizadas y la linea IRQ (FIQ no)
	rINTMSK = rINTMSK & ~(BIT_TIMER1 | BIT_GLOBAL);// Enmascarar todas las lineas excepto Timer0 y el bit global
		/* Establece la rutina de servicio para TIMER1 */
	pISR_TIMER1=(unsigned)timer_ISR1;

	rTCFG0=0xFF;// pre-escalado = 255
	rTCFG1 &= 0xFFFF1F;// divisor = 1/2
	rTCNTB1=65535;
	rTCMPB1=45200;

	rTCON=rTCON | (0x01<<9); //establecer manual_update en timer1
	rTCON=rTCON & ~(0x01<<9); //DESACTIVA manual_update en timer1
	rTCON=rTCON | (0x01<<11); //activar modo auto-reload
	rTCON=rTCON | (0x01<<8); //iniciar timer1
}

void timer2_init()
{
	rINTMOD=0x0;// Configurar las lineas como de tipo IRQ
	rINTCON=0x1;// Habilitar int. vectorizadas y la linea IRQ (FIQ no)
	rINTMSK = rINTMSK & ~(BIT_TIMER2 | BIT_GLOBAL);// Enmascarar todas las lineas excepto Timer0 y el bit global

	pISR_TIMER2=(unsigned)timer_ISR2;

	rTCFG0=0xFFF;// pre-escalado = 255
	rTCFG1 &= 0xFFF1FF;// divisor = 1/2
	rTCNTB2=65535;
	rTCMPB2=45200;

	rTCON=rTCON | (0x01<<13); //establecer manual_update en timer1
	rTCON=rTCON & ~(0x01<<13); //DESACTIVA manual_update en timer1
	rTCON=rTCON | (0x01<<15); //activar modo auto-reload
	rTCON=rTCON | (0x01<<12); //iniciar timer2

}

void timer_init(void)
{

	/* Configurar el Timer0 (el resto de los timers se dejan a la
	configuración por defecto) */

	timer0_init();
	timer1_init();
	timer2_init();

}

void timer_ISR(void)
{

	if (led_state == 1 || led_state == 0) { // si está apagado lo enciendes
		led2_on();
	}
	else {
		led2_off();
	}

	rI_ISPC = BIT_TIMER0;
}

void timer_ISR1(void)
{

	int h = led_state;

	if (led_state == 2 || led_state == 0) { // si está apagado lo enciendes
		led1_on();
	}
	else {
		led1_off();
	}

	rI_ISPC = BIT_TIMER1;
}

void timer_ISR2(void)
{
	D8Led_symbol(0);
	rI_ISPC = BIT_TIMER2;
}
