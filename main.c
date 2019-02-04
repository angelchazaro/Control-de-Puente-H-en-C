/*
 * Puente H con UART ATmega328p.c
 *
 * Created: 19/01/2019 06:35:53 p. m.
 * Author : dx_ch
 */ 

#define F_CPU 16000000UL
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>
#include "UART_routines.h"

void prog_init();
void port_init();
unsigned char * read_Data();

/*******************************************
Esta funcion llama a la inicializacion de funciones al comienzo del programa
*******************************************/
void prog_init(void){
	port_init();
	uart0_init();
}
/*******************************************
Esta funcion inicializa los puertos al comienzo del programa
*******************************************/
void port_init(void)
{
	PORTC = 0x00;
	DDRC  = 0xff;
}

/*******************************************
Esta funcion lee el dato entrante desde la terminal
*******************************************/
unsigned char * read_Data(){
	unsigned char data; //Variable a mantener como el dato
	static unsigned char string[10]; // Arreglo a mantener como valor entrante
	int i = 0; //Contador para el arreglo
	while((data = receiveByte()) != 0x0d)//Verifica si una tecla fue presionada
	{
		transmitByte(data); //Realiza un echo al dato en la terminal
		if(data == 0x0d)
		transmitByte(0x0a);//Transmite una nueva linea
		string[i++] = data;//El dato se guarda en un arreglo
	}
	//TX_NEWLINE;
	return string;
}

int main(void)
{
	DDRB=0xff;
	prog_init();
	unsigned char option;
	unsigned char* string;
	TX_NEWLINE;
	TX_NEWLINE;
	TX_NEWLINE;
	transmitString_F(PSTR(">- CONTROL PARA PUENTE H POR LA UART----"));
	TX_NEWLINE;
	transmitString_F(PSTR(">-------- Por Angel Chazaro ------------"));
	TX_NEWLINE;
	transmitString_F(PSTR(">---------------------------------------"));
	TX_NEWLINE;
    /* Replace with your application code */
    while (1) 
    {
		TX_NEWLINE;
		TX_NEWLINE;
		transmitString_F(PSTR("Presiona una tecla para continuar..."));
		option = receiveByte();
		TX_NEWLINE;
		TX_NEWLINE;
		transmitString_F(PSTR("> 0 : Para giro a la izquierda"));
		TX_NEWLINE;
		transmitString_F(PSTR("> 1 : Para giro a la derecha"));
		TX_NEWLINE;
		TX_NEWLINE;
		transmitString_F(PSTR("> Selecciona la opcion entre (0-1): "));
		TX_NEWLINE;
		transmitString_F(PSTR("> Si oprime un num diferente de 0 y 1, se detiene el motor"));
		TX_NEWLINE;
		
		option = receiveByte();
		transmitByte(option);
		
		switch (option)
		{
			case '0':
			TX_NEWLINE;
			transmitString_F(PSTR(" Giro a la izquierda: "));
			//string = read_Data();
			PORTB=0x05;
			//_delay_ms(3000);
			break;
			case '1':
			TX_NEWLINE;
			transmitString_F(PSTR(" Giro a la derecha: "));
			//string = read_Data();
			PORTB=0x0A;
			//_delay_ms(3000);
			break;
			default:
			TX_NEWLINE;
			transmitString_F(PSTR(" Se detiene motor :)"));
			TX_NEWLINE;
			PORTB=0x00;
			//_delay_ms(1000);
			break;
		}
		TX_NEWLINE;
		transmitString_F(PSTR("Dato enviado"));
		TX_NEWLINE;
    }
}


