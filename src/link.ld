OUTPUT_ARCH(arm)
ENTRY(_start)

SECTIONS
{
    /* Startup LOADER_ADDR. */
    . = 0x8000;

    .text :
    {
        . = ALIGN(4);
        *(.text)
        . = ALIGN(4);
    }

    __rodata_start = . ;
    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)
        . = ALIGN(4);
    }
    __rodata_end = . ;

    __data_start = . ;
    .data :
    {
        . = ALIGN(4);
        *(.data)
        . = ALIGN(4);
    }
    __data_end = . ;

    __bss_start = .;
    .bss :
    {
        . = ALIGN(4);
        *(.bss)
        . = ALIGN(4);
    }
    __bss_end = .;
}
