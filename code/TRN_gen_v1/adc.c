#include "adc.h"



void ADC_setup(void)
{
    //ADMUX |= (0<<REFS1)|(0<<REFS0)|(1<<ADLAR)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0);
    /// AREF pin = Reference, ADC0 input pin, Left Adjusted result (only 8 MSbits are valid)

    ADMUX |= (0<<REFS1)|(0<<REFS0)|(0<<ADLAR)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0);
    /// AREF pin = Reference, ADC0 input pin, Right Adjusted result (10 MSbits are valid)
    ADCSRA |= (1<<ADEN)|(0<<ADSC)|(0<<ADATE)|(1<<ADIE)|(1<<ADPS2)|(0<<ADPS1)|(1<<ADPS0);
    /// ADC Enabled,,  f_clk_adc = 500 kHz (P = 32), autotriggering OFF
    /// =============== MAXIMUM F_CLK_ADC = 1 MHz !!!! ===================================
    /// ADC Interrupt Enabled, Auto-triggering Enabled,

    ADCSRB |= (0<<ADTS2)|(0<<ADTS1)|(0<<ADTS0);
    /// ADC conversion Starts by triggering it manually
}

uint8_t ADC_get_flag(void)
{
    uint16_t val = 0;
    ADCSRA &= ~(1<<ADIE); // disable USART RX interrupt
    val = adc_flag;
    ADCSRA |= (1<<ADIE); // enable
    return val;
}


/// ================== INTERRUPT SERVICE ROUTINE ===============================


ISR(ADC_vect)
{
    /// Conversion Completed:
    //adc_value = ADCL;
    //adc_value = ADCH;

    adc_value = ADCL;
    adc_value |= ADCH<<8;

    /*
    if(adc_flag)
        adc_flag = 0;
    else
        adc_flag = 1;*/
    adc_flag++;
}
