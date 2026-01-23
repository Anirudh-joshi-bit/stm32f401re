#include "../include/commons.h"
#define TX_PIN 9
#define RX_PIN 10

void delay(int count) {
  while (count--)
    ;
}

char data[11];

int main() {

  RCC->APB2ENR |= RCC_APB2ENR_USART1EN_Msk;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  // pa9 TX, pa10 RX, pa11 cts (AF7), pa12 rts (AF7)

  GPIOA->MODER &= ~((3 << (2 * TX_PIN)) | (3 << (2 * RX_PIN)));
  GPIOA->MODER |= 2 << (2 * TX_PIN) | 2 << (2 * RX_PIN);
  GPIOA->OTYPER &= ~((1 << TX_PIN) | 1 << (RX_PIN));
  GPIOA->OSPEEDR |=
      (3 << (TX_PIN * 2)) | (3 << (RX_PIN * 2)); // ospeed takes 2 bits

  GPIOA->AFR[1] &= ~((0xf << 4) | (0xf << 8)); // clear the previous values
  GPIOA->AFR[1] |= (7 << 4) | (7 << 8);        // move 4 places at once

  USART1->CR1 |= USART_CR1_RE | USART_CR1_UE | USART_CR1_TE;
  USART1->BRR = 0x08B;

  int i = 0;

  while (i < 11) {

    while (!(USART1->SR & USART_SR_RXNE)) {
    }
    data[i++] = USART1->DR;
  }
  delay(500000);
  while (1) {
    i = 0;
    while (i < 11) {
      while (!(USART1->SR & USART_SR_TXE)) {
      }
      USART1->DR = data[i++];
    }
    delay (500000);
  }

}
