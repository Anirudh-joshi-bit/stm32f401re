#pragma once

#include "defines.h"
#include "device/stm32f401xe.h"
#include <stdbool.h>


void __usart1_init (void);
void printf (const char* string, uint32_t addr);


