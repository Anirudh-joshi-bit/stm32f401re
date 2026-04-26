#include "stm32f401xe.h"
#define TX_PIN 9
#define RX_PIN 10

extern volatile uint8_t ip_data[];
extern volatile uint32_t ip_data_size; 
extern volatile uint32_t ip_data_ind;

extern volatile uint8_t op_data [];
extern volatile uint32_t op_data_size; 
extern volatile uint32_t op_data_ind;


// usart 1 isr
void  USART1_IRQHandler (void) {
  if (USART1-> SR & USART_SR_RXNE_Msk) {
    if (ip_data_ind >= ip_data_size)
      return;
    ip_data[ip_data_ind++] = USART1->DR;
  }
  else if (USART1->SR & USART_SR_TC_Msk) {
    if (op_data_ind >= op_data_size)
      return;
    USART1-> DR = op_data [op_data_ind++];
  }
}



void __usart1_init(void) {
  // todo -> add interrupt rxnie, tcie, error control

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

  // enable interrupt
  USART1->CR1 = USART_CR1_TCIE | USART_CR1_TXEIE | USART_CR1_RXNEIE;
  // enable usart, reciever, transiever
  USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;

  NVIC_EnableIRQ (USART1_IRQn);

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




