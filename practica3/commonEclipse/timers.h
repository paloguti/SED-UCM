/*-------------------------------------------------------------------
**
**  Fichero:
**    timers.h  26/4/2013
**
**    (c) J.M. Mendias
**    Programaci�n de Sistemas y Dispositivos
**    Facultad de Inform�tica. Universidad Complutense de Madrid
**
**  Prop�sito:
**    Contiene las definiciones de los prototipos de las funciones
**    para la generaci�n de retardos y la medida de tiempos
**
**  Notas de dise�o:
**
**-----------------------------------------------------------------*/

#ifndef __TIMERS_H__
#define __TIMERS_H__

#include "common_types.h"

/*
** Pone a 0 los registros de configuraci�n
** Pone a 0 todos los b�fferes y registros de cuenta y comparaci�n
** Para todos los temporizadores
** Inicializa las variables para retardos software
*/
void timers_init( void );

/*
** Realiza una espera de n milisegundos usando el timer3
*/
void timer3_delay_ms( uint16 n );

/*
** Realiza una espera de n milisegundos sin usar temporizadores
*/
void sw_delay_ms( uint16 n );

/*
** Realiza una espera de n segundos usando el timer3
*/
void timer3_delay_s( uint16 n );

/*
** Realiza una espera de n segundos sin usar temporizadores
*/
void sw_delay_s( uint16 n );

/*
** Arranca el timer3 a una frecuencia de 0,01 MHz 
** Permitir� medir tiempos con una resoluci�n de 0,1 ms (100 us) hasta un m�ximo de 6.55s
*/
void timer3_start( void );

/*
** Detiene el timer3, devolviendo el n�mero de d�cimas de milisegundo transcurridas desde que arranc�
** Devuelve 0 si han transcurrido m�s de 6.55 s
*/
uint16 timer3_stop( void );

/*
** Arranca el timer3 a una frecuencia de 0,01 MHz para que cuente n d�cimas de milisegundo hasta un m�ximo de 6.55s
*/
void timer3_start_timeout( uint16 n );

/*
** Indica si el timer3 ha finalizado su cuenta
*/
uint16 timer3_timeout( void );

/* 
** Para cada uno de los timers:
** Instala, en la tabla de vectores de interrupci�n, la funci�n isr como RTI de interrupciones por fin de timer
** Desenmascara globalmente las interrupciones y espec�ficamente las interrupciones por fin de timer
** Habilita las interrupciones por fin de timer
*/
void timer0_open( void (*isr)(void) );
void timer1_open( void (*isr)(void) );
void timer2_open( void (*isr)(void) );
void timer3_open( void (*isr)(void) );
void timer4_open( void (*isr)(void) );
void timer5_open( void (*isr)(void) );

/* 
** Para cada uno de los timers:
** Deshabilita las interrupciones por fin de timer
** Desinstala la RTI por fin de timer
*/
void timer0_close( void );
void timer1_close( void );
void timer2_close( void );
void timer3_close( void );
void timer4_close( void );
void timer5_close( void );

#endif 
