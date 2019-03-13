#include "44b.h"
#include "iic.h"

extern uint32 mclk;			   // Frecuencia actual del reloj (Hz)

extern void DelayMs(int ms_time);

void iic_init( void )
{
	// Enable IIC & GPIO & BDMA blocks (si no se activa BDMA, el controlador IIC no es accesible)
	rCLKCON |= 1<<13 | 1<<10 | 1<<7;
	
	// PF[1] = IICSDA, PF[0] = IICSCL
	rPCONF &= ~(0x1<<0 | 0x1<<2);
	rPCONF |= 0x1<<1 | 0x1<<3 ;
	
	// Pull-up enable
	rPUPF &= ~(0x1<<0 | 0x1<<1);
	
    //Configurar la dirección del slave
	rIICADD = S3C44B0X_SLAVE_ADDRESS;

    //Generación ACK habilitada, interrupciones habilitadas
	rIICCON |= (0x1<<7); //habiltar ACK
	rIICCON |= (0x1<<5); //habilita interrupciones
	
    rIICCON = rIICCON | ((mclk / 4000000 - 1) & 0xf); 	//Valor de preescalado, PREESCALER = mclk/16/250000 -1
	
    // Activa Tx/Rx
    rIICSTAT |= 0x1<<4;

}

void iic_putByte_start( uint8 byte )
{
	// Escribe el dato
	rIICDS = byte;
	// Máster Tx, start condition, Tx/Rx habilitada
	rIICSTAT |= (0x1<<4 | 0x1<<5 | 0x1<<6 | 0x1<<7 );
	// Comienza la transmisión (borrando pending bit del IICCON)
	rIICCON &= ~(0x1<<4);

    // Espera la recepción de ACK  
	while ((rIICCON & 0x1<<4 ) == 0){}
}

void iic_putByte( uint8 byte )
{
    // Escribe el dato
	rIICDS = byte;
	// Comienza la transmisión del dato (borrando pending bit del IICCON)
	rIICCON &= ~(0x1<<4);

    // Espera la recepción de ACK  
	while ((rIICCON & 0x1<<4 ) == 0){}
};

void iic_putByte_stop( uint8 byte )
{
    // Escribe el dato
	rIICDS = byte;
	// Comienza la trasmisión del dato (borrando pending bit del IICCON)
	rIICCON &= ~(0x1<<4);
    // Espera la recepción de ACK  
	while ((rIICCON & 0x1<<4 ) == 0){}
    
    // Máster Tx, stop condition, Tx/Rx habilitada
	rIICSTAT &= ~(0x1<<5);
    // Comienza la trasmisión de STOP (borrando pending bit del IICCON)
	rIICCON &= ~(0x1<<4);
    // Espera a que la stop condition tenga efecto (5 ms para la at24c04)
	DelayMs(5);
}

void iic_getByte_start( uint8 byte )
{
	// Escribe el dato
	rIICDS = byte;
    // Máster Rx, start condition, Tx/Rx habilitada
	rIICSTAT |= (0x1<<4 | 0x1<<5 | 0x1<<7 );
	rIICSTAT &= ~(0x1<<6);
    // Comienza la transmisión (borrando pending bit del IICCON)
	rIICCON &= ~(0x1<<4);
    // Espera la rececpión de ACK
	while ((rIICCON & 0x1<<4 ) == 0){}
}

uint8 iic_getByte( void )
{
    // Reanuda la recepción (borrando pending bit del IICCON)
	rIICCON &= ~(0x1<<4);
	// Espera la recepción del dato
	while ((rIICCON & 0x1<<4 ) == 0){}

    return rIICDS;// Lee el dato
}

uint8 iic_getByte_stop( int8 ack )
{
	uint8 byte;

    rIICCON = (rIICCON & ~(1 << 7)) | (ack << 7); // Habilita/deshabilita la generación de ACK

    // Reanuda la recepción (borrando pending bit del IICCON)
    rIICCON &= ~(0x1<<4);
	// Espera la recepción del dato
    while ((rIICCON & 0x1<<4 ) == 0){}

    byte = rIICDS;	// Lee el dato

   	// Máster Rx, stop condition, Tx/Rx habilitada
    rIICSTAT |= (0x1<<4 | 0x1<<5 | 0x1<<7 );
    rIICSTAT &= ~(0x1<<6);
    rIICSTAT &= ~(0x1<<5);

   	// Comienza la trasmisión de STOP (borrando pending bit del IICCON)
    rIICCON &= ~(0x1<<4);
   	// Espera a que la stop condition tenga efecto (5 ms para la at24c04)
    DelayMs(5);

	rIICCON |= (1<<7); // Habilita la generación de ACK
   	return byte;
}
