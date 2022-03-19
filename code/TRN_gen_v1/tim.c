#include "tim.h"



/*
uint16_t TIMER0_get_value(void)
{
   //uint16_t val = 0;
   TIMSK0 &= ~(1<<OCIE0A);
   return timer0_cnt;
   TIMSK0 |= (1<<OCIE0A);
   //return val;
}
*/
uint16_t TIMER0_get_value(void)
{
   uint16_t val = 0;
   TIMSK0 &= ~(1<<OCIE0A);
   val = timer0_cnt;
   TIMSK0 |= (1<<OCIE0A);
   return val;
}


/*
uint16_t TIMER1_get_value(void)
{
   uint16_t val = 0;

   val = timer1_cnt;

   return val;
}
*/

/*
void TIMER1_setup(void)
{
  TCCR1A |= (0<<WGM11)|(0<<WGM10);
  TCCR1B |= (0<<WGM13)|(1<<WGM12)|(0<<CS12)|(1<<CS11)|(0<<CS10);
  /// CTC mode, N = 8, Timer resolution = 0.5 us, Timer Range = 32768 us

  TIMSK1 |= (0<<TOIE1)|(0<<OCIE1A);
  /// CTC interrupt Disabled
  OCR1A = 20010;  /// TIMEOUT for the DCC RX PIN EDGE DETECTION

}
*/
void TIMER0_setup(void)
{
    /// Timer0 used for LED blinking

    TCCR0A |= (0<<COM0A1)|(0<<COM0A0)|(0<<COM0B1)|(0<<COM0B0)|(1<<WGM01)|(0<<WGM00);
    /// No output pins enabled.
    //TCCR0B |= (0<<WGM02)|(0<<CS02)|(1<<CS01)|(0<<CS00); /// TIMER RUNNING
    TCCR0B |= (0<<WGM02)|(0<<CS02)|(1<<CS01)|(1<<CS00); /// TIMER STARTED
    /// CTC mode, (N = 64)
  /// CS02    CS01    CS00      N
  ///   0       0       0       No source
  ///   0       0       1       1
  ///   0       1       0       8
  ///   0       1       1       64
  ///   1       0       0       256
  ///   1       0       1       1024
  ///   1       1       0       Extern Falling
  ///   1       1       1       Extern Rising

    TIMSK0 |= (0<<TOIE0)|(1<<OCIE0A)|(0<<OCIE0B);/// Output Compare A ISR
    OCR0A = 249; /// ISR frequency 1.000 kHz
    //OCR0A = 231; /// for bit "0"

}

/// ================== INTERRUPT SERVICE ROUTINE ===============================


/*
ISR(TIMER1_COMPA_vect){

    timer1_cnt++;
}
*/


ISR(TIMER0_COMPA_vect)
{
    cli();
    timer0_cnt++;
    sei();
}




