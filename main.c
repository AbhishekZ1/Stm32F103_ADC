# include "gpio_driver.h"
#include "stm32f10x.h" 
#include "systick_timer.h"
#include "uart.h"
#include "adc_driver.h"

 

char adc_channels[17] = {PB1, PA4, PA0, PA1};
int analog_rx[17];
char channels = 4;

int main(void)
{
    systick_init_timer(); // Initialize the delay function
    adc_multi_ch_init(adc1, channels, adc_channels);

    while (1)
    {
        adc_multi_ch_rx(adc1, channels, adc_channels, analog_rx);
    }
}
