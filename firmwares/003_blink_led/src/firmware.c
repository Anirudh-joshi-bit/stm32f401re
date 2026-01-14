#include "../include/device/stm32f401xe.h"

static void delay(volatile unsigned long count)
{
    while (count--) {}
}

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    (void)RCC->AHB1ENR;

    GPIOA->MODER &= ~(3U << (5 * 2));   
    GPIOA->MODER |=  (1U << (5 * 2));  

    GPIOA->OTYPER &= ~(1U << 5);

    GPIOA->OSPEEDR |= (1U << (5 * 2));

    GPIOA->PUPDR &= ~(3U << (5 * 2));

    while (1)
    {
        GPIOA->ODR ^= (1U << 5);
        delay(50000);
    }
}

