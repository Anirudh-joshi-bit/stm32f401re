.syntax unified
.cpu cortex-m3
.thumb

.section .text
.global app_entry
.type app_entry, %function

app_entry:

    // add two numbers 12 and a
    MOV R0, #0x12
    MOV R1, #0xA
    
    ADD R2, R1, R0
    
    // by the end, r2 contains the result

loop:
    nop
    b loop

