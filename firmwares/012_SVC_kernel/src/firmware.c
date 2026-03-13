#include "../include/commons.h"
extern void syscall (void);

void syscall_1 (char* c, uint32_t num){

}

uint32_t syscall_table [10];

void helper (uint8_t imm){
    uint8_t val = imm;
}

int main () {
    
    syscall_table [0] = (uint32_t) syscall_1;

    syscall ();
}




