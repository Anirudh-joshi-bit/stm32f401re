#include "stm32f401xe.h"

void DMA2_Stream7_IRQHandler (void){
  if (DMA2-> HISR & DMA_HISR_TCIF7_Msk){
    DMA2-> HIFCR |= DMA_HIFCR_CTCIF7_Msk;
  }
}

void DMA2_Stream2_IRQHandler (void){
  if (DMA2-> LISR & DMA_LISR_TCIF2_Msk){
    DMA2-> LIFCR |= DMA_LIFCR_CTCIF2_Msk;
  }
}


