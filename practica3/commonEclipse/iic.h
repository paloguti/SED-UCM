/*-------------------------------------------------------------------
**
**  Fichero:
**    iic.h  17/5/2013
**
**    (c) J.M. Mendias
**    Programaci�n de Sistemas y Dispositivos
**    Facultad de Inform�tica. Universidad Complutense de Madrid
**
**  Prop�sito:
**    Contiene las definiciones de los prototipos de funciones
**    para la comunicaci�n por el bus IIC del chip S3C44BOX 
**
**  Notas de dise�o:
**
**-----------------------------------------------------------------*/

#ifndef __IIC_H__
#define __IIC_H__

#include "common_types.h"

#define S3C44B0X_SLAVE_ADDRESS (0x08)

#define	RxACK		(1)
#define NO_RxACK	(0)

/*
** Configura el controlador de IIC seg�n los siguientes par�metros 
**   Interrupciones: habilitadas
**   Transmisi�n/recepci�n: activada
**   Frecuencia de comunicaci�n: 250 KHz
**   Generaci�n de ACK: autom�tica
**   Direcci�n como esclavo: 0x08
*/
void iic_init( void );

/*
** Inicia un flujo de transmici�n en la que el microcontrolador act�a como master:
** 	 Genenera la START condition
**   Env�a la direcci�n del dispositivo esclavo
**   Espera la recepci�n de ACK 
*/
void iic_putByte_start( uint8 byte );

/*
** Actuando el microcontrolador como master, env�a el byte indicado y espera la recepci�n de ACK
*/
void iic_putByte( uint8 byte );

/*
** Finaliza un flujo de transmisi�n en la que el microcontrolador act�a como master:
** 	 Envia el byte indicado
**   Espera la recepci�n de ACK 
**   Genara la STOP condition
*/
void iic_putByte_stop( uint8 byte );

/*
** Inicia un flujo de recepci�n en la que el microcontrolador act�a como master:
** 	 Genenera la START condition
**   Env�a la direcci�n del dispositivo esclavo
**   Espera la recepci�n de ACK 
*/
void iic_getByte_start( uint8 byte );

/*
** Actuando el microcontrolador como master, espera la recepci�n de un byte, genera ACK y lo devuelve
*/
uint8 iic_getByte( void );

/*
** Finaliza un flujo de recepci�n en la que el microcontrolador act�a como master:
** 	 Espera la recepci�n de un byte
**   Genera o no ACK 
**   Genera la STOP condition
**   Devuelve el byte recibido
*/
uint8 iic_getByte_stop( int8 ack );

/* 
** Instala, en la tabla de vectores de interrupci�n, la funci�n isr como RTI de interrupciones por Tx/Rx a traves de IIC
** Desenmascara globalmente las interrupciones y espec�ficamente las interrupciones por Tx/Rx a traves de IIC
** Habilita las interrupciones por Tx/Rx a traves de IIC
*/
void iic_open( void (*isr)(void) );

/* 
** Deshabilita las interrupciones por Tx/Rx a traves de IIC
** Desinstala la RTI por Tx/Rx a traves de IIC
*/
void iic_close( void );

#endif
