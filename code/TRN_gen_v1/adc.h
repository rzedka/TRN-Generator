#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>

/// Following variables must be defined in main as global:
extern volatile uint8_t adc_flag; /// driven by TIMER0
extern volatile uint16_t adc_value; /// driven by TIMER1


void ADC_setup(void);

uint8_t ADC_get_flag(void);

#endif // ADC_H_INCLUDED
