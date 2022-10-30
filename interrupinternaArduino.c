#include <Arduino.h>

volatile bool abajo = true;

//FUNCIONES
void interrupt_TIMER1_Init(){
 cli(); //deshabilitar momentáneamente las interrupciones
 TCCR1A = 0;//El registro de control A queda todo en 0, pines OC1A y OC1B deshabilitados
 TCCR1B = 0b101; //preescalador 1024
 TIMSK1 = 1; // habilitar interrupcion por desbordamiento
 sei(); //habilitar las interrupciones
 TCNT1 = 49911; //1 s // tiempo de la interrupcion
}


ISR(TIMER1_OVF_vect){ //INTERRUPCIONES //se hace el desplazamiento

if(abajo){
 PORTB = PORTB<<1;
 if(PORTB == 64) PORTB = 1;
 }
 else{
 PORTB = PORTB>>1;
 if(PORTB == 0) PORTB = 32;
 }
 TCNT1 = 49911;

}


void setup()
{
 DDRB = 0XFF; //PuertoB salida
 PORTB = 1; //PIN0 del puerto B activado
 interrupt_TIMER1_Init(); //250ms de retardo
PORTD |= (1<<PD2); //Activar resistencia de PULLup en PIN2 del puerto D
}

void loop(){
 if(!(PIND&(1<<PIND2))){ //si está presionado entra al if 
while(!(PIND&(1<<PIND2))){} //espera a que se suelte la botonera
abajo = !abajo;
 }
}

