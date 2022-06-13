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
 DDRB = 0XFF; //PuertoC salida
 PORTB = 1; //PIN0 del puerto C activado
 PORTD |= (1<<PD2); //Activar resistencia de PULLUP en PIN2 del puerto D
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


