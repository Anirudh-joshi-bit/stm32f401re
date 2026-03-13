#include "../include/commons.h"


int main(void){
    __usart1_init();

     // enable bus fault 
    SCB->SHCSR |= SCB_SHCSR_BUSFAULTENA_Msk;

    // bfsr =>
//    SCB->CFSR |= SCB_CFSR_BFARVALID_Msk; // precise bus fault 
    

    // access an invalid address ->
    uint32_t address = 0xffffffff;
    *(uint32_t *) (address) = 0x5;
    
    printf ("%\n\r", address);

    while (1);

}

void busfault_handler (void){
    
    printf ("busfault error...\n\r", 0x0);
    printf ("busfault status -> %\n\r",(uint32_t) &SCB->CFSR);

    if (SCB->CFSR & SCB_CFSR_BFARVALID_Msk)
        printf ("busfault address -> %\n\r",(uint32_t) &SCB->BFAR);

    else {
        printf ("imprecise bus fault !!\n\r", 0x0);
    }
    while (1);
}



