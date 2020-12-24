#include <mega16.h>
#asm
  .equ __lcd_port= 0x1B;
#endasm

#include <lcd.h>
#include <stdlib.h>
#define ICP_EN PINC.0

static int alpha_pointer = -1;

static unsigned int timer1_counter = 0;
const unsigned long TIMER1_VALUE = 0xE0C0;  

interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
    TCNT1=TIMER1_VALUE;
    ++timer1_counter;
}

interrupt [TIM1_CAPT] void timer1_capt_isr(void)
{
    char str_period[10];
    char str_freq[10];
    unsigned long period;
    unsigned int lcr1;  
    
    lcr1 = (ICR1H*256)+ICR1L;
    period = ((unsigned long)(((float)lcr1)/((float)(0xffff-TIMER1_VALUE)))) 
            + ((unsigned long) timer1_counter) ;
  
    
    timer1_counter = 0;         
    TCNT1=TIMER1_VALUE;
                         
    itoa(period,str_period);
    ftoa(1/((float)period/1000),3,str_freq);    
    
    lcd_clear();              
    lcd_puts("Period: ");
    lcd_puts(str_period);
    lcd_puts(" ms");
    lcd_gotoxy(0,1);     
    lcd_puts("Freq: ");       
    lcd_puts(str_freq);
    lcd_puts(" Hz");
}


void main(void)
{

DDRA= 0xFF;
DDRC= 0xF0;
PORTC.7 = 0; 

TCCR1A= 0;
TCCR1B=(1<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (1<<CS10);
TCNT1=TIMER1_VALUE;
ICR1H=0x00;
ICR1L=0x00;

TIMSK=(0<<OCIE2) | (0<<TOIE2) | (1<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);

lcd_init(16);

#asm("sei");

while (1){
 if (ICP_EN){
     TIMSK |= (1<<TICIE1) | (1<<TOIE1);
     TIMSK &= ~(1<<TOIE0);
     alpha_pointer = -1;
 } else {
     TIMSK &= ~(1<<TICIE1);
     TIMSK &= ~(1<<TOIE1);
     TIMSK |= (1<<TOIE0);
 } 
}
}
