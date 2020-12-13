#include <mega16.h>
#include <delay.h>

unsigned int ledCount = 8;
unsigned int ledNum = 0;
unsigned int i = 0;

void main (void){
    DDRB=0xff; 
    DDRA=0x00;             
 
    while(1){     
        if(PINA.0==0){
             delay_ms(100);
             for(i = 0; i < ledCount * 2; i = i + 1){
                 ledNum = i % (ledCount);  
                 if(i < 8) PORTB = 1 << ledNum;
                 if(i >= 8) PORTB = 1 << ledCount - (ledNum + 2);
                 delay_ms(1000);
             }
        }
    }
}