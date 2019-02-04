//**************************************************************
//******** FUNCIONES PARA LA COMUNICACION SERIAL USANDO LA UART *******
//**************************************************************
//Controlador:	ATmega328p (Crystal: 8Mhz)
//Compilador:		Atmel Studio 7 (AVR-GCC)
//Autor:		CC Dharmani, Chennai (India)	//Fecha:			Abril 2009
//Co-Autor:		Angel Chazaro (México)		//Fecha:			Enero 2019

//********************************************************

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "UART_routines.h"

void uart0_init(void)
{
 UCSR0C = 0x06;	//Para el ATmega32	//0x06; Para el ATmega128
 UBRR0 = 0x67; //Para 103 a 16 mhz a 9600 baudios //0x33; //Para 51 a 8 mhz a 9600 baudios
 UCSR0B = 0x98;
}
//**************************************************
//Funcion para recibir un solo byte
//*************************************************
unsigned char receiveByte( void )
{
	unsigned char data, status;
	
	while(!(UCSR0A & (1<<RXC0))); 	// Espera a un dato entrante
	
	status = UCSR0A;
	data = UDR0;
		   
	return(data);
}

//***************************************************
//Funcion para transmitir un solo byte
//***************************************************
void transmitByte( unsigned char data )
{
	while ( !(UCSR0A & (1<<UDRE0)) )
		; 			                /* Espera a transmitir un buffer vacio */
	UDR0 = data; 			        /* Inicia la transmision */
}

//***************************************************
//Funcion para transmitir una cadena
//***************************************************
void transmitString_F(char* string)
{
  while (pgm_read_byte(&(*string)))
   transmitByte(pgm_read_byte(&(*string++)));
}

//***************************************************
//Funcion para transmitir una cadena en RAM
//***************************************************
void transmitString(char* string)
{
    while (*string)
		transmitByte(*string++);
}
