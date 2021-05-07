#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
bool abajo = true;
//FUNCIONES
void isPress(){
 if((PIND&(1<<PIND2))==0){ //si está presionado entra al if
 while((PIND&(1<<PIND2))==0){} //espera a que se suelte la botonera
 abajo = !abajo;
 }
}
//MAIN
int main()
{
 DDRC = 0XFF; //PuertoC salida
 PORTC = 1; //PIN0 del puerto C activado
 PORTD |= (1<<PD2); //Activar resistencia de PULLUP en PIN2 del puerto D
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
 isPress();
 }
 return 0;
}
