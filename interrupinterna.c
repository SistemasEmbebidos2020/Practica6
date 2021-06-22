#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
volatile bool abajo = true;
//FUNCIONES
void interrupt_TIMER0_Init(){
 cli();
 TCCR0B = 0b101;
 TIMSK0 = 1;
 sei();
 TCNT0 = 12; //250ms
}
ISR(TIMER0_OVF_vect){ //INTERRUPCIONES
 if(abajo){
 PORTC = PORTC<<1;
 if(PORTC == 64) PORTC = 1;
 }
 else{
 PORTC = PORTC>>1;
 if(PORTC == 0) PORTC = 32;
 }
 TCNT0 = 12;
}
int main()
{
 DDRC = 0XFF; //PuertoC salida
 PORTC = 1; //PIN0 del puerto C activado
 PORTD |= (1<<PD2); //Activar resistencia de PULLDOWN en PIN0 del puerto D
 interrupt_TIMER0_Init(); //250ms de retardo
 while (1){
 if((PIND&(1<<PIND2))==0){ //si está presionado entra al if
while((PIND&(1<<PIND2))==0){} //espera a que se suelte la botonera
abajo = !abajo;
 }
 } return 0;
}
