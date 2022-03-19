#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>


//extern unsigned char uart_rx_array[50];
extern volatile uint8_t uart_flag;
extern volatile uint8_t rx_array[20];
extern volatile uint8_t uart_char_idx;


void USART_init(void);

void USART_RX_WAIT(uint8_t *RX_Data);

void USART_TX_WAIT(uint8_t TX_Data);

void USART_TX_STRING_WAIT(char s[]);

uint8_t USART_get_flag(void);

void UART_RX_FCN(uint8_t *UI_flag, char *CMD_head, char *CMD_word);

uint8_t CMD_Head_lib(char CMD_head[5]);

#endif // UART_H_INCLUDED
