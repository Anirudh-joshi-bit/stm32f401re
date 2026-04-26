#include "commons.h"
#include "USART.h"
#include "USART_config.h"
#include "stm32f401xe.h"


volatile uint8_t ip_data [10];
volatile uint32_t ip_data_ind = 0;
volatile uint32_t ip_data_size = 10;

volatile uint8_t op_data [] = {
  'h', 'e', 'l', 'l', 'o', 't', 'h', 'e', 'r', 'e', '\n', '\r'
};
volatile uint32_t op_data_size = 12;


int main() {

  __usart1_init();


  RCC -> AHB1ENR |=  RCC_AHB1ENR_DMA2EN_Msk;

  // dma config for usart1 tx

  // wait for te dma stream7 to complete the transfer
  while (DMA2_Stream7 -> CR & DMA_SxCR_EN_Msk);

  // dissable stream 0;
  DMA2_Stream7 -> CR &= ~DMA_SxCR_EN_Msk;

  DMA2_Stream7 -> PAR = (uint32_t) &USART1-> DR;
  DMA2_Stream7 -> M0AR = (uint32_t)op_data;
  DMA2_Stream7 -> NDTR = op_data_size;
  DMA2_Stream7 -> CR  &=  ~(7 << DMA_SxCR_CHSEL_Pos);
  DMA2_Stream7 -> CR  |= 4 << DMA_SxCR_CHSEL_Pos;
  DMA2_Stream7 -> CR &= ~(3 << DMA_SxCR_DIR_Pos);
  DMA2_Stream7 -> CR |= 1 << DMA_SxCR_DIR_Pos;
  DMA2_Stream7 -> FCR &= ~(DMA_SxFCR_DMDIS_Msk);
  DMA2_Stream7 -> CR  &= ~DMA_SxCR_PINC_Msk;
  DMA2_Stream7 -> CR  |= DMA_SxCR_MINC_Msk;
  // set PSIZE , MSIZE = 1B
  DMA2_Stream7 -> CR &= ~(3 << DMA_SxCR_MSIZE_Pos);
  DMA2_Stream7 -> CR &= ~(3 << DMA_SxCR_PSIZE_Pos);
  // there is no burst transfer for usart (only one address)
  // enable transfer complete interrupt
  DMA2_Stream7 -> CR |= DMA_SxCR_TCIE;
  NVIC_EnableIRQ (DMA2_Stream7_IRQn);

  // enable the stream
  DMA2_Stream7 -> CR |= DMA_SxCR_EN;


  // dma config for usart2 rx

  // wait for te dma stream2 to complete the transfer
  while (DMA2_Stream2 -> CR & DMA_SxCR_EN_Msk);

  // dissable stream;
  DMA2_Stream2 -> CR &= ~DMA_SxCR_EN_Msk;

  DMA2_Stream2 -> PAR = (uint32_t) &USART1-> DR;
  DMA2_Stream2 -> M0AR = (uint32_t)ip_data;
  DMA2_Stream2 -> NDTR = 10;
  DMA2_Stream2 -> CR  &=  ~(7 << DMA_SxCR_CHSEL_Pos);
  DMA2_Stream2 -> CR  |= 4 << DMA_SxCR_CHSEL_Pos;
  DMA2_Stream2 -> CR &= ~(3 << DMA_SxCR_DIR_Pos);
  DMA2_Stream2 -> FCR &= ~(DMA_SxFCR_DMDIS_Msk);
  DMA2_Stream2 -> CR  &= ~DMA_SxCR_PINC_Msk;
  DMA2_Stream2 -> CR  |= DMA_SxCR_MINC_Msk;
  // set PSIZE , MSIZE = 1B
  DMA2_Stream2 -> CR &= ~(3 << DMA_SxCR_MSIZE_Pos);
  DMA2_Stream2 -> CR &= ~(3 << DMA_SxCR_PSIZE_Pos);
  // there is no burst transfer for usart (only one address)
  // enable transfer complete interrupt
  DMA2_Stream2 -> CR |= DMA_SxCR_TCIE;
  NVIC_EnableIRQ (DMA2_Stream2_IRQn);

  // enable the stream
  DMA2_Stream2 -> CR |= DMA_SxCR_EN;


  // do something
  while (1)
    ;
}
