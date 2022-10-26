#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
static volatile bool abajo = true; // static variable global // volatile diferentes hilos o interrupciones + programa principal
//FUNCIONES
void isPress(){
 if(!(PIND&(1<<PIND2))){ //si está presionado entra al if
 while(!(PIND&(1<<PIND2))){} //espera a que se suelte la botonera
 abajo = !abajo;
 }
}
//MAIN
int main()
{
 DDRB = 0XFF; //PuertoB salida
 PORTB = 1; //PIN0 del puerto B activado

 ////COMO EL PIN2 NO SE LO DECLARÓ COMO SALIDA, POR DEFECTO SE ENCUENTRA COMO ENTRADA
 //// POR ENDE AL UTILIZAR EL REGISTRO PORTx PARA UNA ENTRADA LO QUE SE HACE
 //// ES ACTIVAR SU RESISTENCIA PULLUP INTERNA
  ////SE PUEDE ACTIVAR LA RESISTENCIA PULLUP DE CIERTOS PINES DEL ATMEGA328P
 /////ESTO SE LO REALIZA CON EL SIGUIENTE CODIGO
 PORTD |= (1<<PD2); //Activar resistencia de PULLUP en INT0 del puerto D
 while (1){
 _delay_ms(250);
 if(abajo){
PORTB = PORTB<<1;
if(PORTB == 64) PORTB = 1;
 }
 else{
PORTB = PORTB>>1;
if(PORTB == 0) PORTB = 32;
 }
 isPress();
 }
 return 0;
}


