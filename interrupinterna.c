#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
volatile bool abajo = true;
//FUNCIONES
void interrupt_TIMER0_Init(){
 cli(); //deshabilitar momentáneamente las interrupciones
 TCCR0B = 0b101; //preescalador 1024
 TIMSK0 = 1; // habilitar interrupcion por desbordamiento
 sei(); //habilitar las interrupciones
 TCNT0 = 12; //250ms // tiempo de la interrupcion
}
ISR(TIMER0_OVF_vect){ //INTERRUPCIONES //se hace el desplazamiento
 if(abajo){
 PORTB = PORTB<<1;
 if(PORTB == 64) PORTB = 1;
 }
 else{
 PORTB = PORTB>>1;
 if(PORTB == 0) PORTB = 32;
 }
 TCNT0 = 12;
}
int main()
{
 DDRB = 0XFF; //PuertoC salida
 PORTB = 1; //PIN0 del puerto C activado
 interrupt_TIMER0_Init(); //250ms de retardo
PORTD |= (1<<PD2); //Activar resistencia de PULLDOWN en PIN0 del puerto D
 while (1){
 if(!(PIND&(1<<PIND2))){ //si está presionado entra al if 
while(!(PIND&(1<<PIND2))){} //espera a que se suelte la botonera
abajo = !abajo;
 }
 } return 0;
}
