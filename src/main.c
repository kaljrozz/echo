#include "stm32f4xx.h"
#include <stdint.h>

void usart2_init(){
    //enable clock on PA and USART2
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    //set PA2 and PA3 to alt func mode
    GPIOA->MODER |= (10 << 4);
    //map PA2 to USART2 Tx and PA3 to USART2 Rx
    GPIOA->AFR[0] |= (0x77 << 8);
    //set PA2 Tx output to push pull
    GPIOA->OTYPER |= ~(1 << 2);
    //set PA2 Tx output speed to very high
    GPIOA->OSPEEDR |= (3 << 2);
    //set PA3 Rx input to pull up
    GPIOA->PUPDR |= (1 << 6);

    //start USART2
    USART2->CR1 |= (1 << 13);
    //set baud rate divider
    //DIV = PCLK/(8*(2-OVER8)*BR)
    //BR = 9600, PCLK = 16MHz, OVER8 = 0
    //DIV = 104.166667
    //MANTISSA = 104
    //FRACTION = 0.166667*8*(2-OVER8) = 2.66667 = 3
    USART2->BRR |= (104 << 4) | 3;
    //enable Rx and Tx on USART2
    USART2->CR1 |= (3 << 2);

    //enable USART2 interrupts on the NVIC
    //NVIC->ISER[1] = (1 << (USART2_IRQn - 32));
    __NVIC_EnableIRQ(USART2_IRQn);
    //enable interrupts for Rx
    USART2->CR1 |= (1 << 5);
}
void USART2_IRQHandler(void){
    //make sure RXNE bit is set 
    if(USART2->SR & (1 << 5)){
        //getting data from DR clears the RXNE bit
        uint8_t c = USART2->DR;
        //wait for TC bit to get set
        while(!(USART2->SR & (1 << 6)));
        //place data on to DR to send it out
        USART2->DR = c;
    }
}
int main(void){
    usart2_init();
    while(1);
    return 0;
}
