.syntax unified
.cpu cortex-m3
.thumb

/* 
================= VECTOR TABLE ================= 

.section -> this tells the "as" to create a section with the following 
porperties
properties ->
name ----- .isr_vector
"a"  -----  section flag
    this flag says that this section must allocated in memory at runtime
    it means it must appear in FLASH / ROM 

    if "a" is removed -> this section only exit in .o file 


some other flags -> 
"x"   ----- executible
"w"   ----- writable 


still there is no "x" mentioned in .txt section as GNU assembler has 
default flags for popular names (you dont need to tell the GAS in some
cases) 

*/





.section .isr_vector, "a", %progbits
.global _vectors
_vectors:
    .word   _estack          /* Initial MSP value */
    .word   Reset_Handler    /* Reset */
    .word   Default_Handler  /* NMI */
    .word   Default_Handler  /* HardFault */
    .word   Default_Handler  /* MemManage */
    .word   Default_Handler  /* BusFault */
    .word   Default_Handler  /* UsageFault */
    .word   0
    .word   0
    .word   0
    .word   0
    .word   Default_Handler  /* SVCall */
    .word   Default_Handler  /* Debug */
    .word   0
    .word   Default_Handler  /* PendSV */
    .word   Default_Handler  /* SysTick */

/* ================= RESET HANDLER ================= */

// there is "a" because what ever is written is to be placed in the ROM
// withoput "a" the code never be loaded into the FLASH or RAM 
//      it will be limited to .o file

.section .text   // similar to => .section .text, "ax", %progbits
.global Reset_Handler  
.type Reset_Handler, %function

Reset_Handler:
    bl app_entry        /* jump to your app */
hang:
    b hang              /* never return */

/* ================= DEFAULT HANDLER ================= */

/*

default handler just calles current address (meaning it does not call the same function infinite time but it calles the same instruction infinite time) 

. meaning the current instruction address 
b .  ----- > when cpu execute this instruction pc does not effectively change !!! meaning this creates an infinite loop 

 
in real system, these default handler should be set to some resonable 
subroutine (not just some randome infinite loop)

*/

.type Default_Handler, %function
Default_Handler:
    b .

