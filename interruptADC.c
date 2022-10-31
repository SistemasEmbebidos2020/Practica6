#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

#include <stdlib.h>

//FUNCIONES
void interrupt_INT0_Init(){
 cli(); //DESH INT
 EICRA = 0b11; // INT FLANCO DE SUBIDA
 EIMSK = 1; // HAB PIN0, para habilitar pin2 ---> 2
 sei(); //HAB INT
}
void interrupt_TIMER1_Init(){
 cli();
 TCCR1A=0;
 TCCR1B = 0b101; //PREESCALADOR 1024
 TIMSK1 = 1; //HB TIMER POR DESBORDAMIENTO
 sei();
 TCNT1 =  61630; //250ms   para 1 segundo 49911
}
void ADC_Init(){
 ADMUX = 0b000; //ADC0 
 ADCSRA = 0b10101111; //ADC activado modo automático y preescalador 8
 //ADCSRB= 0b10; //Modo interrupción externa //ADIE(3) en 1 para habilitar la interrupción por la terminación de una conversión analógica.
 ADCSRB= 0b110; //Modo Timer1 (250ms)
}
//INTERRUPCIONES
ISR(TIMER1_OVF_vect){
 TCNT1 =  61630;
}
ISR(INT0_vect){
 //EIFR &= ~(1<<INTF0);
}
ISR(ADC_vect){ 

float r = ADC/1023.0*5.0;

	 if (r<0.49) {PORTB = 0; PORTD = 0;}
else if (r<1.00) {PORTB=1; PORTD &= ~0B11110000; }
else if (r<1.50) {PORTB=3;  PORTD = 0;  }
else if (r<2.00) {PORTB=7;  PORTD = 0;  }
else if (r<2.50) {PORTB=15; PORTD = 0;  }
else if (r<3.00) {PORTB=31; PORTD = 0;  }
else if (r<3.50) {PORTB=63; PORTD = 0;  }
//else if (r>=3.50) {PORTB=63; PORTD =  0X10 ;  }	//PARA USAR ESTO, SE REQUIERE REAZILAR LA CONEXION DE PULL UP EXTERNAMENTE
else if (r<4.00) {PORTB=63; PORTD |=  0B00010000; PORTD &= ~(1<<5) ;  }
else if (r<4.50) {PORTB=63; PORTD |=  0B00110000; PORTD &= ~(1<<6) ;  }
else if (r<5.00) {PORTB=63; PORTD |=  0B01110000; PORTD &= ~(1<<7) ;  }
else 			 {PORTB=63; PORTD |=  0B11110000;  }

}
//MAIN
int main()
{
 DDRB = 0XFF;
 DDRD |= 0B11110000;
 PORTD |= (1<<PD2); //Activar resistencia de PULLUP en PIN0 del puerto D
 ADC_Init();
 interrupt_INT0_Init();
 interrupt_TIMER1_Init(); //250ms de retardo
//serial_begin(9600);
while(1){
;
}
return 0;
}
