#include "../include/commons.h"

char data[10];

void __usart2_init(void);
#define U2_TX 2

int main() {
 
    __usart2_init ();
    data[1] = 'A';

    printf ("value stored in data[1] is -> %", (uint32_t)(data+1));



    while (1);
}
