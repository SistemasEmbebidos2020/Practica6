#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
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
int main()
{
 DDRB = 0XFF; //PuertoB salida
 PORTB = 1; //PIN0 del puerto B activado
 PORTD |= (1<<PD2); //Activar resistencia de PULLUP en INT0 del puerto D
 interrupt_INT0_Init();
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
 }
return 0;
}
