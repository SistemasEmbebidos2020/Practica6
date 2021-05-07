#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
//FUNCIONES
void interrupt_INT0_Init(){
 cli();
 EICRA = 0b11;
 EIMSK = 1;
 sei();
}
void interrupt_TIMER0_Init(){
 cli();
 TCCR0B = 0b101;
 TIMSK0 = 1;
 sei();
 TCNT0 = 12; //250ms
}
void ADC_Init(){
 ADMUX = 0b110;
 ADCSRA = 0b10101011; //ADC activado modo automático y preescalador 8
 //ADCSRB= 0b10; //Modo interrupción externa
 ADCSRB= 0b100; //Modo Timer0 (250ms)
}
//INTERRUPCIONES
ISR(TIMER0_OVF_vect){
 TCNT0 = 12;
}
ISR(INT0_vect){
}
ISR(ADC_vect){
 PORTB =ADCL;
 PORTC = ADCH;
}
//MAIN
int main()
{
 DDRB = 0XFF; //PuertoB salida
 DDRC = 0b11; //Pines0y 1 del puerto C como salida
 PORTD |= (1<<PD2); //Activar resistencia de PULLUP en PIN0 del puerto D
 ADC_Init();
 interrupt_INT0_Init();
 interrupt_TIMER0_Init(); //250ms de retardo
 while (1){
 //Lazo principal vacío
 }
 return 0;
}
