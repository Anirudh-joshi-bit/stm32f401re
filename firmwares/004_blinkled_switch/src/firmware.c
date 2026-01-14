#include "../include/device/stm32f401xe.h"
#define LED_PIN 5
#define BOTTON_PIN 13

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    (void)RCC->AHB1ENR;

    GPIOA->MODER &= ~(3U << (LED_PIN * 2));   
    GPIOA->MODER |=  (1U << (LED_PIN * 2));  
    GPIOA->OTYPER &= ~(1U << LED_PIN);
    GPIOA->OSPEEDR |= (1U << (LED_PIN * 2));
    GPIOA->PUPDR &= ~(3U << (LED_PIN * 2));



    GPIOC-> MODER &= ~(3 << (2* BOTTON_PIN));
    GPIOC-> OSPEEDR &= ~(3 << (2* BOTTON_PIN));
    GPIOC-> PUPDR &= ~(3 << (2* BOTTON_PIN));



    while (1)
    {
        if (GPIOC-> IDR & (1<< BOTTON_PIN))
            GPIOA->ODR &= ~(1<<LED_PIN);
        else 
            GPIOA->ODR |= 1<<LED_PIN;
    }
}

