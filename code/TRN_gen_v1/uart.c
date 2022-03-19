#include "uart.h"


void USART_init(void)
{
    /// F_CPU = 16 MHz
    /// BAUDRATE koeficient is 103 ( 9615,38 Baud )
    /// Set UART for communication with PC

    /// For 9600 Bd: (error = +0.2%)
    //UCSR0A |= (0<<U2X0)|(0<<MPCM0);
    //UBRR0H = 0x00;/// has to be written first
    //UBRR0 = 0x67; /// this updates the prescaler.

    /// For 57600 Bd:  (error =-0.8%)
    UCSR0A |= (1<<U2X0);
    UBRR0 = 34;

    UCSR0B |= (1<<RXCIE0)|(0<<TXCIE0)|(0<<UDRIE0)|(1<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02)|(0<<RXB80)|(0<<TXB80) ;
    UCSR0C |= (0<<UMSEL01)|(0<<UMSEL00)|(0<<UPM01)|(0<<UPM00)|(0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00)|(0<<UCPOL0) ;
    /// no parity, 8bit data, 1 stop bit, RX complete interrupt, RX enabled, double speed mode DISABLED.
    /// see page 244 of ATMEGA328P datasheet.

}


void USART_RX_WAIT(uint8_t *RX_Data)
{
    while ( (UCSR0A&0x80) != 0x80 ); /// Wait until it receives something
        *RX_Data = UDR0; /// After that, read the data register
}

void USART_TX_WAIT(uint8_t TX_Data)
{
    while ( (UCSR0A&0x20) != 0x20 ); /// Wait until TX buffer ready.
    UDR0 = TX_Data;  /// Send data
}

void USART_TX_STRING_WAIT(char s[])
{
    unsigned int i=0;
    while( s[i] != '\0'){
        USART_TX_WAIT(s[i]);
        i++;
    }
    //USART_TX_WAIT('\n');
}

uint8_t USART_get_flag(void)
{
    uint16_t val = 0;
    UCSR0B &= ~(1<<RXCIE0); // disable USART RX interrupt
    val = uart_flag;
    UCSR0B |= (1<<RXCIE0); // enable
    return val;
}


void UART_RX_FCN(uint8_t *UI_flag, char *CMD_head, char *CMD_word)
{

    uint8_t i=0;
    memset(CMD_head,'\0',5);
    memset(CMD_word,'\0',33);
    for(i=0;i<4;i++){
        CMD_head[i] = rx_array[i];   /// index 0 - 3
    }
    while( rx_array[i]!='\0' ){ /// i = (4 - 35)
        if (i<=36){
            CMD_word[i-4] = rx_array[i]; /// index 0 - 31
            i++;
        }else{
            break;
        }
    }
    if(i > 36){ /// Command length invalid:
        USART_TX_STRING_WAIT(" CMD TOO LONG ");
        *UI_flag = 0; /// TEMP IDLE
    }else{ /// Command length valid: cmd recognition
        *UI_flag |= CMD_Head_lib(CMD_head);
    }
    i=0;

}


uint8_t CMD_Head_lib(char CMD_head[5])
{

    if(!strcmp(CMD_head,"SAD_")){       /// Toggle ADC periodic conversion
        return 0x01;
    }else if(!strcmp(CMD_head,"ADS_")){ /// Set ADC conversion period (ms)
        return 0x02;
    }else if(!strcmp(CMD_head,"STOT")){ /// Stop TEST 1
        return 0x04;
    }else{ /// Unknown Command
        return 0x00;
    }
}




ISR(USART_RX_vect) /// ====================== UART DATA RECEPTION ===============================================
{ /// UART RX complete Interrupt:
    cli();

    /// UART TERMINAL SETTINGS:
    /// - every message must be terminated with CR+LF (0x0D 0x0A)

    /// All the variables
    if(uart_char_idx > 99){
        uart_char_idx=0; /// Start overwriting the beginning
        rx_array[uart_char_idx] = UDR0; /// read UART buffer
    }else if(uart_char_idx == 0){
        memset(rx_array,'\0',20);
        rx_array[uart_char_idx] = UDR0; /// read UART buffer
        uart_char_idx++;
    }else{
        rx_array[uart_char_idx] = UDR0; /// read UART buffer
        if(rx_array[uart_char_idx] == 0x0A){ /// end of the CMD (CR char)
            rx_array[uart_char_idx] = 0x00; // erase 0x0A
            rx_array[--uart_char_idx] = 0x00; // erase 0x0D
            uart_flag ++; /// this variable increments each ISR. It is followed by another variable in the main.
            /// The change of "uart_flag" triggers Command recognition procedure.
            /// However, "uart_flag" can never be modified outside this ISR! It can only be read.
            uart_char_idx = 0;

        }else{
            uart_char_idx++;
        }
    }
    sei();
}


