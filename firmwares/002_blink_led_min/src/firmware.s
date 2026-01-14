.syntax unified
.cpu cortex-m3
.thumb

.section .text
.global app_entry
.type app_entry, %function

app_entry:
    /* Enable GPIOA clock */
    LDR     R0, =0x40023830      /* RCC_AHB1ENR */
    LDR     R1, [R0]
    ORR     R1, R1, #(1 << 0)    /* GPIOAEN */
    STR     R1, [R0]

    /* Configure PA5 as output */
    LDR     R0, =0x40020000      /* GPIOA base */
    LDR     R1, [R0]             /* GPIOA_MODER */
    BIC     R1, R1, #(3 << 10)   /* clear MODER5 */
    ORR     R1, R1, #(1 << 10)   /* output mode */
    STR     R1, [R0]

loop:
    /* Toggle PA5 */
    LDR     R2, =0x40020014      /* GPIOA_ODR */
    LDR     R3, [R2]
    EOR     R3, R3, #(1 << 5)
    STR     R3, [R2]

    BL      delay
    B       loop

delay:
    LDR     R4, =800000
delay_loop:
    SUBS    R4, R4, #1
    BNE     delay_loop
    BX      LR
