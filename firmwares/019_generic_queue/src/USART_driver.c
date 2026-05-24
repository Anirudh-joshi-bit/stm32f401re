#include "stm32f401xe.h"
#define TX_PIN 9
#define RX_PIN 10
#define U2_TX 2
#define U2_RX 3

void __usart1_init(void) {

  RCC->APB2ENR |= RCC_APB2ENR_USART1EN_Msk;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  // alternate function mode
  GPIOA->MODER &= ~((3 << (2 * TX_PIN)) | (3 << (2 * RX_PIN)));
  GPIOA->MODER |= 2 << (2 * TX_PIN) | 2 << (2 * RX_PIN);
  // high speed
  GPIOA->OSPEEDR |= (3 << (TX_PIN * 2)) | (3 << (RX_PIN * 2));
  // clear the bits in AFR register
  GPIOA->AFR[1] &= ~((0xf << 4) | (0xf << 8));
  // set for af7
  GPIOA->AFR[1] |= (7 << 4) | (7 << 8);

  // set the baud rate (115200 in this case)
  USART1->BRR = 16000000 / 115200;

  // enable usart dmat , dmar
  USART1->CR3 |= USART_CR3_DMAT_Msk | USART_CR3_DMAR_Msk;

  // enable usart, reciever, transiever
  USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;

  NVIC_EnableIRQ(USART1_IRQn);
}

void __usart2_init(void) {

  RCC->APB1ENR |= RCC_APB1ENR_USART2EN_Msk;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  // alternate function mode
  GPIOA->MODER &= ~((3 << (2 * U2_TX)) | (3 << (2 * U2_RX)));
  GPIOA->MODER |= 2 << (2 * U2_TX) | 2 << (2 * U2_RX);
  // high speed
  GPIOA->OSPEEDR |= (3 << (U2_TX * 2)) | (3 << (U2_RX * 2));
  // clear the bits in AFRL register
  GPIOA->AFR[0] &= ~((0xf << 12) | (0xf << 8));
  // set for af7
  GPIOA->AFR[0] |= (7 << 12) | (7 << 8);

  // set the baud rate (115200 in this case)
  USART2->BRR = 0x08B;

  // enable usart, reciever, transiever
  USART2->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;

  USART2->CR1 |= USART_CR1_UE;

  // enable usart1 interrupt via NVIC
  NVIC_EnableIRQ(USART2_IRQn);
}

void __usart2_print(const char *msg, uint32_t size) {

  int i = 0;
  while (i < size && msg[i] != '\0') {
    while (!(USART2->SR & USART_SR_TXE))
      ;
    USART2->DR = msg[i++];
  }
  while (!(USART2->SR & USART_SR_TC)) {
  }
}

void __usart1_print(const char *msg, uint32_t size) {

  int i = 0;
  while (i < size && msg[i] != '\0') {
    while (!(USART1->SR & USART_SR_TXE))
      ;
    USART1->DR = msg[i++];
  }
  while (!(USART1->SR & USART_SR_TC)) {
  }
}
