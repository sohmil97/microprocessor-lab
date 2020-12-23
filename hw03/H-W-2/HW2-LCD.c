

#include <mega16.h>
#include <alcd.h>


int TimerOverFlowCounter;
int x;
int y;
int character;

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
      ++ TimerOverFlowCounter;

      if(TimerOverFlowCounter ==1000){

          lcd_putchar(character);
          character +=1;
          x=x+1;

            if(x==20){
            x=0;
            y=1;
             }

            lcd_gotoxy(x,y);
            TimerOverFlowCounter=0;

            if(character == 0x5b){
              TCCR0=0x00;
              TIMSK=0x00;
            }

       }

      TCNT0=0x00;

}


void main(void)
{

    DDRA=0x00;
    PORTA=0x00;
    x=0;
    y=0;
    TimerOverFlowCounter=0;
    character=0x41;
    TCCR0=0x01;
    TCNT0=0x00;
    OCR0=0x00;
    TIMSK=0x01;
    lcd_init(20);
    #asm("sei")

while (1)
      {


      }


}
