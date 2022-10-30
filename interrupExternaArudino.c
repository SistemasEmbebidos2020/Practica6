#include <Arduino.h>

volatile bool abajo = true;
//FUNCIONES
void interrupt_INT0_Init(){
 cli();
 EICRA = 0b11;
 EIMSK = 1;
 sei();
}
//INTERRUPCIONES
ISR(INT0_vect){
 abajo = !abajo;
}
//MAIN
void setup()
{
 DDRB = 0XFF; //PuertoB salida
 PORTB = 1; //PIN0 del puerto B activado
 
 ////COMO EL PIN2 NO SE LO DECLARÓ COMO SALIDA, POR DEFECTO SE ENCUENTRA COMO ENTRADA
 //// POR ENDE AL UTILIZAR EL REGISTRO PORTx PARA UNA ENTRADA LO QUE SE HACE
 //// ES ACTIVAR SU RESISTENCIA PULLUP INTERNA
 ////SE PUEDE ACTIVAR LA RESISTENCIA PULLUP DE CIERTOS PINES DEL ATMEGA328P
 /////ESTO SE LO REALIZA CON EL SIGUIENTE CODIGO
 PORTD |= (1<<PD2); //Activar resistencia de PULLUP en INT0 del puerto D
 interrupt_INT0_Init();
}

void loop(){
 delay(250);
 if(abajo){
PORTB = PORTB<<1;
if(PORTB == 64) PORTB = 1;
 }
 else{
PORTB = PORTB>>1;
if(PORTB == 0) PORTB = 32;
 }

}
