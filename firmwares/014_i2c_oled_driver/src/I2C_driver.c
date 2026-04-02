#include "../include/commons.h"

void __i2c1_init(void) {

  // enable gpioB
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

  // set pb6, pb7 to alternate mode
  GPIOB->MODER &= ~((3 << 12) | (3 << 14));
  GPIOB->MODER |= ((2 << 12) | (2 << 14));

  // open drain
  GPIOB->OTYPER |= (1 << 6) | (1 << 7);

  // pull up ( both SDA, SDL)
  GPIOB->PUPDR &= ~((3 << 12) | (3 << 14));
  GPIOB->PUPDR |= ((1 << 12) | (1 << 14));

  // high speed
  GPIOB->OSPEEDR |= (3 << 12) | (3 << 14);

  // configure afr for i2c
  GPIOB->AFR[0] &= ~((7 << 24) | (7 << 28));
  GPIOB->AFR[0] |= (4 << 24) | (4 << 28);

  // enable i2c1
  RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

  // I2C setup
  I2C1->CCR = (1 << 15) | 13; // fast mode
  I2C1->TRISE = 5;

  // set clock freq
  I2C1->CR2 |= 16; // 16 MHz
  I2C1->CR1 |= I2C_CR1_PE_Msk;
}

int8_t __i2c1_print(const uint8_t *string, uint32_t size, uint16_t dev_addr) {
  if (dev_addr > ((1 << 7) - 1))
    return -1;

  uint16_t i = 0;

  // BUSY -> bus is captured
  while (I2C2->SR2 & I2C_SR2_BUSY_Msk)
    ;
  // start sequence
  I2C1->CR1 |= I2C_CR1_START_Msk;

  while (!(I2C1->SR1 & I2C_SR1_SB_Msk))
    ;

  // write address to DR register
  I2C1->DR = dev_addr << 1; // lsb is 0 for controller transmitter

  // wait until addr is sent
  while (!(I2C1->SR1 & I2C_SR1_ADDR_Msk))
    ;

  // read sr1, sr2 to continue
  (void)I2C1->SR1;
  (void)I2C1->SR2;

  while (i < size) {

    // send the data
    I2C1->DR = string[i++];

    // wait for txe bit to set
    while (!(I2C1->SR1 & I2C_SR1_TXE_Msk))
      ;
  }
  I2C1->CR1 |= I2C_CR1_STOP_Msk;
  while (I2C2->SR2 & I2C_SR2_BUSY_Msk)
    ;
}

