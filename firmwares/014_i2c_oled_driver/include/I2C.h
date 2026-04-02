#pragma once


void __i2c1_init(void);
int8_t __i2c1_print(const uint8_t *string, uint32_t size, uint16_t dev_addr);
