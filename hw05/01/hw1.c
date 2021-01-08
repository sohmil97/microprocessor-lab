#include <mega16.h>
#include <delay.h>

bit flag=0;
int states[4] = {0b00001001 , 0b000001010 , 0b00000110 , 0b00000101};
int currentPosition=0;
int TimerOverFlowCounter =0;
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{

    TimerOverFlowCounter++;
    if(TimerOverFlowCounter == 20){

        if(currentPosition < 4 && flag ==0){

       PORTA =  states[currentPosition];
       currentPosition = currentPosition +1;
       flag =1;
       if(currentPosition == 4)
        {
         currentPosition = 0;

        }

    } else if(flag==1){

           PORTA = 0b00000000;
        flag = 0;
        if(currentPosition == 4)
        {
         currentPosition = 0;

        }

        }


          TimerOverFlowCounter=0;

        }

    TCNT0 = 6;

  
}

void main(void)
{

DDRA=0xff;
PORTA=0x00;

DDRC=0x00;
PINC=0x00;



TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (1<<CS00);
TCNT0 = 6;
OCR0=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);


while (1)
      {
        if(PINC.2 == 0)
        {
              #asm("sei")


         // Global enable interrupts
       }

      }
}
