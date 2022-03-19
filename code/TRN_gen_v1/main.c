/*
 */

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>

#include "trn_sys_definitions.h"

#include "gpio.h"
#include "tim.h"
#include "adc.h"
#include "uart.h"

#define T_IDLE 500

#define T_ADC 100

/// Global variables:

volatile uint16_t timer0_cnt;
volatile uint8_t adc_flag;
volatile uint16_t adc_value;

volatile uint8_t uart_flag;
volatile uint8_t rx_array[20];
volatile uint8_t uart_char_idx;

unsigned char uart_rx_array[50];

int main(void)
{
    uint16_t ref_timer0 = 0;
    uint16_t ref_timer1 = 0;

    uint8_t uart_flag_f = 0; /// UART flag follower
    uint8_t adc_flag_f = 0; /// ADC flag follower

    uint8_t CMD_flag = 0;

    uint16_t sys_flag = 0;

    uint16_t adc_period = T_ADC;

    timer0_cnt = 0;
    adc_flag = 0;
    adc_value = 0;
    uart_flag = 0;
    uart_char_idx = 0;
    memset(rx_array,'\0',20);

    char buffer[5];
    memset(buffer,'\0',5);
    char CMD_head[5] = {0,0,0,0,0};
    char CMD_word[33];
    memset(CMD_word,'\0',33); /// clear array


    GPIO_setup();
    TIMER0_setup(); /// 1 kHz with OCRA interrupt
    ADC_setup(); /// Set ADC in ATmega324p for manual conversion start
    USART_init();



    USART_TX_STRING_WAIT("TRN Generator v1.0\n");

    sei(); /// Main interrupt enable flag SET

    while(1){

        /// LED blink process:
        if( (TIMER0_get_value() - ref_timer0) >= T_IDLE){
            ref_timer0 = TIMER0_get_value();
            PORTLED ^= (1 << LED0_PIN);
        }


        /// ADC conversion trigger process:
        if( (TIMER0_get_value() - ref_timer1) >= adc_period){
            ref_timer1 = TIMER0_get_value();

            if(sys_flag&(1<<SYS_ADC)){
                ADCSRA |= (1<<ADSC); /// A/D CONVERSION START
            }
        }


        /// ADC conversion finished process:
        if( (ADC_get_flag() - adc_flag_f)){
            adc_flag_f = ADC_get_flag();
            //USART_TX_STRING_WAIT("ADC = ");
            USART_TX_STRING_WAIT(itoa(adc_value, buffer, 10));
            //USART_TX_WAIT('\n');
            USART_TX_WAIT(',');
            /// Transmitting this message should take approx 1.4 ms (~10 chars ad 57600 Bd)
            /// T_ADC must be greater than this duration.
        }



        /// UART Message received:
        if( (USART_get_flag() - uart_flag_f)){
            uart_flag_f = USART_get_flag();

            //PORTLED ^= (1 << LED0_PIN);

            UART_RX_FCN(&CMD_flag, CMD_head, CMD_word);

            if(CMD_flag&0x01){
                /// Toggle periodic AD conversion process:
                sys_flag ^= (1<<SYS_ADC);
                USART_TX_STRING_WAIT("Toggle ADC\n");

            }else if(CMD_flag&0x02){
                /// Set new AD conversion time period:
                adc_period = atoi(CMD_word);
                if(adc_period == 0){
                    /// In case of NaN input override with default T_ADC
                    adc_period = T_ADC;
                    USART_TX_STRING_WAIT("ADPD\n");
                }else{
                    USART_TX_STRING_WAIT("ADPU\n");

                }
            }else{
                /// nothing
            }

            CMD_flag = 0;
        }

    }


    return 0;
}
