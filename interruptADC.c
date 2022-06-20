#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include "uart.h"
#include <stdlib.h>

//FUNCIONES
void interrupt_INT0_Init(){
 cli(); //DESH INT
 EICRA = 0b11; // INT FLANCO DE SUBIDA
 EIMSK = 1; // HAB PIN0, para habilitar pin2 ---> 2
 sei(); //HAB INT
}
void interrupt_TIMER0_Init(){
 cli();
 TCCR0B = 0b101; //PREESCALADOR 1024
 TIMSK0 = 1; //HB TIMER POR DESBORDAMIENTO
 sei();
 TCNT0 = 12; //250ms
}
void ADC_Init(){
 ADMUX = 0b000; //ADC0 
 ADCSRA = 0b10101011; //ADC activado modo automático y preescalador 8
 //ADCSRB= 0b10; //Modo interrupción externa //ADIE(3) en 1 para habilitar la interrupción por la terminación de una conversión analógica.
 ADCSRB= 0b100; //Modo Timer0 (250ms)
}
//INTERRUPCIONES
ISR(TIMER0_OVF_vect){
 TCNT0 = 12;
}
ISR(INT0_vect){
 //EIFR &= ~(1<<INTF0);
}
ISR(ADC_vect){ 
 //PORTB =ADCL;
 //PORTC = ADCH;
float r = ADC/1023.0*5.0;
char rec1[20] ;
dtostrf(r, 2, 4, rec1);
serial_println_str(rec1);
}
//MAIN
int main()
{
 PORTD |= (1<<PD2); //Activar resistencia de PULLUP en PIN0 del puerto D
 ADC_Init();
 interrupt_INT0_Init();
 interrupt_TIMER0_Init(); //250ms de retardo
serial_begin(9600);
while(1){
;
}
return 0;
}
