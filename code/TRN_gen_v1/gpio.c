#include "gpio.h"

void GPIO_setup(void)
{
    DDRLED0 |= (1<<LED0_PIN);   // output
    PORTLED &= ~(1<<LED0_PIN); // LED0 OFF

    //DDRLED1 |= (1<<LED1_PIN);   // output
    //PORTLED0 &= ~(1<<LED1_PIN); // LED0 OFF

    //led_flag = 0;
}


/*
void LED_toggle(uint8_t led_bit)
{   /// led_bit = 0x01, 0x02, 0x04, 0x08, ...
    uint8_t bitshift = 0;

    switch(led_bit){
    case 0x01: /// LED0
            bitshift = LEDz_PIN;
        break;
    case 0x02: /// LED1
            bitshift = LEDy_PIN;
        break;
    case 0x04: /// IDLE process LED
            bitshift = LEDx_PIN;
        break;
    default:   /// LED0
            bitshift = LEDx_PIN;

    }// end switch

    if(led_flag&led_bit){
        led_flag &= ~led_bit;
        PORTB &= ~(1<<bitshift);
    }else{ /// The LED is off
        led_flag |= led_bit;
        PORTB |= (1<<bitshift);
    }
}
*/

/*
void BTN_Debounc( uint8_t *btn_flag, uint8_t *btn_edge)
{
    uint8_t btn_reg = 0x00; // GPIO read register
    static uint8_t debounc_cnt = 0x00; // Needs to be static, otherwise it is erased every time the function is called...
    static uint16_t ref_time = 0x0000;

    if((timer_cnt - ref_time) >= 1){ /// every 1 ms
        ref_time = timer_cnt;
        btn_reg = ~((1<<BTN0_PIN)|(1<<BTN1_PIN))|BTNPIN; // Read the BTN pins
        if( btn_reg != 0xFF ){ // IF at least one BTN is pressed:
            if (debounc_cnt >= BTN_DEBOUNC_MS){
                if( (*btn_flag&(~btn_reg)) == 0x00){
                    // this is the first CLK cycle the BTN is pressed:
                    *btn_flag |= ~btn_reg; /// Set BTNx bit flag
                    *btn_edge |= ~btn_reg; /// Set BTNx EDGE bit
                }else{
                    *btn_edge = 0x00;
                }
            }else{ // if it is not pressed long enough, Debounc_CNT is not overflowed to 0 yet...
                debounc_cnt = debounc_cnt + 1; // keep counting
            }
        }else{ // if No BTN is pressed anymore / a glitch has occurred
           debounc_cnt = 0x00; /// Reset counter,
           *btn_flag = 0x00;
           *btn_edge = 0x00;
        }// end if
    }else{
        *btn_edge = 0x00;
    } // end if debounc TICK flag
}

*/

