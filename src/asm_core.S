
.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.global reset_handler

.type reset_handler, %function
reset_handler:
    /* move the stack pointer to the end of the stack */
    LDR     r0,     =_estack
    MOV     sp,     r0

    /* copy initialized data */
    MOV     r0,     #0
    LDR     r1,     =_sdata 
    LDR     r2,     =_edata 
    LDR     r3,     =_sidata 

    B       copy_sidata_loop

    copy_sidata:
            /* offset the data init section by the progress so far */
            LDR     r4,     [r3, r0]
            /* copy the current word into data */
            STR     r4,     [r1, r0]
            /* increment the counter */
            ADDS    r0,     r0,     #4

    copy_sidata_loop:
            ADDS    r4,     r0,     r1
            CMP     r4,     r2
            BCC     copy_sidata

    /* zero out the bss section */
    MOVS    r0,     #0
    LDR     r1,     =_sbss
    LDR     r2,     =_ebss
    B reset_bss_loop

    reset_bss:
            /* store a zero and increment by a word */
            STR     r0,     [r1]
            ADDS    r1,     r1,     #4

    reset_bss_loop:
            /* loop until r1 gets to _ebss */
            CMP     r1,     r2
            BCC     reset_bss

/* initialize the system clock */
BL  System_Clock_Init

/* branch to main */
B   main
.size reset_handler, .-reset_handler
