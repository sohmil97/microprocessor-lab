
#include <mega16.h>
#include <delay.h>
#define led PORTA.0

unsigned char c;

interrupt [TIM0_OVF] void timer0_ovf_isr(void){
    TCNT0=0x16;
    c++;
}
    
void main(void){ 
    DDRA=0xff; 

    TCCR0=0x05;
    TCNT0=0x16;
    OCR0=0x00;
    
    // Timer(s)/Counter(s) Interrupt(s) initialization
    TIMSK=0x01;
        
    // Global enable interrupts
    #asm("sei")

    while (1){     
        if(c>=25) {
            led=~led;
            c=0;
        }      
    }
}
    