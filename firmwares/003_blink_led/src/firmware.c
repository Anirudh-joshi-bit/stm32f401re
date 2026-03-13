#include "../include/device/stm32f401xe.h"

static void delay(volatile unsigned long count)
{
    while (count--) {}
}

int main(void)
{
    delay(1000);
    while (1);
}

