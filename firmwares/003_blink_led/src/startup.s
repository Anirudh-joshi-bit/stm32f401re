.syntax unified
.cpu cortex-m4
.thumb


.section .isr_vector, "a", %progbits
.global g_pfnVectors
.type g_pfnVectors, %object

g_pfnVectors:
    .word _estack            
    .word Reset_Handler     

    .word Default_Handler    // NMI 
    .word Default_Handler    // HardFault 
    .word Default_Handler    // MemManage 
    .word Default_Handler    // BusFault 
    .word Default_Handler    // UsageFault 
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0                  // SVCall 
    .word 0
    .word 0
    .word 0                  // PendSV 
    .word 0                  // SysTick 


.size g_pfnVectors, . - g_pfnVectors



.section .text.Reset_Handler
.global Reset_Handler
.type Reset_Handler, %function

Reset_Handler:
    ldr r0, =_sidata
    ldr r1, =_sdata
    ldr r2, =_edata

1:
    cmp r1, r2
    bcc 2f
    b   3f
2:
    ldr r3, [r0], #4
    str r3, [r1], #4
    b   1b

3:
    ldr r0, =_sbss
    ldr r1, =_ebss
    movs r2, #0

4:
    cmp r0, r1
    bcc 5f
    b   6f
5:
    str r2, [r0], #4
    b   4b

6:
    bl main

7:
    b 7b

.size Reset_Handler, . - Reset_Handler



.section .text.Default_Handler
.global Default_Handler
.type Default_Handler, %function

Default_Handler:
    b .

.size Default_Handler, . - Default_Handler

