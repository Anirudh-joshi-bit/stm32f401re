#include "../include/commons.h"

#define SWITCH_PIN 13 // PC13
#define LED_PIN 5     // PA5

bool on_board_switch_falling = true;

void do_something(void) {

  while (1) {
  }
}

int main(void) {

  // enable clock for GPIOC, GPIOA, SYSCFG (for remapping gpio)
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN_Msk;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN_Msk;

  // set regs for led , switch

  GPIOA->MODER &= ~(3 << (LED_PIN * 2));
  GPIOA->MODER |= 1 << (LED_PIN * 2);

  GPIOC->MODER &= ~(3 << (SWITCH_PIN * 2));

  // enable EXIT13
  EXTI->IMR |= EXTI_IMR_MR13_Msk;

  // enable both edge detection
  EXTI->RTSR |= EXTI_RTSR_TR13_Msk;
  EXTI->FTSR |= EXTI_FTSR_TR13_Msk;

  // set GPIOC13 (switch) to use EXTI13
  SYSCFG->EXTICR[3] &= ~(SYSCFG_EXTICR4_EXTI13_Msk);
  SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;

  // enable NVIc EXTI15_10_IRQn to make the cpu recognise the interrupt
  NVIC_EnableIRQ(EXTI15_10_IRQn);       

  do_something();
}
