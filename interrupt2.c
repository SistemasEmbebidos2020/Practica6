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
 DDRC = 0XFF; //PuertoC salida
 PORTC = 1; //PIN0 del puerto C activado
 PORTD |= (1<<PD2); //Activar resistencia de PULLUP en PIN0 del puerto D
 interrupt_INT0_Init();
 while (1){
 _delay_ms(250);
 if(abajo){
PORTC = PORTC<<1;
if(PORTC == 64) PORTC = 1;
 }
 else{
PORTC = PORTC>>1;
if(PORTC == 0) PORTC = 32;
 }
 }
return 0;
}
