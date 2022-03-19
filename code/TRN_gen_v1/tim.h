#ifndef TIM_H_INCLUDED
#define TIM_H_INCLUDED

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>

/// Following variables must be defined in main as global:
extern volatile uint16_t timer0_cnt; /// driven by TIMER0
//extern volatile uint16_t timer1_cnt; /// driven by TIMER1


uint16_t TIMER0_get_value(void);

//uint16_t TIMER1_get_value(void)

//void TIMER1_setup(void);

void TIMER0_setup(void);


#endif // TIM_H_INCLUDED
