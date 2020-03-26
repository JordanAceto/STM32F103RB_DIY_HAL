ENTRY(reset_handler)

/* RAM start + 20k = 0x20000000 + (20*1024) = 0x20000000 + 0x5000 */
_estack = 0x20005000;

/* force error if less than 1kb RAM left (1024 = 0x400) */
_min_leftover_RAM = 0x400;

/* stm32f103 has 128k flash, 20k sram */
MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 128k
    RAM   (rxw) : ORIGIN = 0x20000000, LENGTH = 20k
}

SECTIONS
{
    /* vector table goes at the start of flash */
    .vector_table :
    {
        . = ALIGN(4);
        KEEP (*(.vector_table))
        . = ALIGN(4);
    } >FLASH

    /* main program code */
    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        . = ALIGN(4);
    } >FLASH

    /* read only data */
    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } >FLASH

    /* variables */
    _sidata = .;
    .data : AT(_sidata)
    {
        . = ALIGN(4);
        _sdata = .; /* start of data */
        *(.data)
        *(.data*)
        _edata = .; /* end of data */
        . = ALIGN(4);
    } >RAM

    /* bss variables are initialized to zero */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .; /* start of bss */
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .; /* end of bss */
    } >RAM

    /* space for the application heap/stack */
    .dynamic_allocations :
    {
        . = ALIGN(4);
        _ssystem_ram = .; /* start of system ram */
        . = . + _min_leftover_RAM;
        . = ALIGN(4);
        _esystem_ram = .; /* end of system ram */
    } >RAM

    /DISCARD/ :
    {
        *(*)
    }
}
