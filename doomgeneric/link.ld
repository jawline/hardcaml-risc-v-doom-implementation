OUTPUT_ARCH( "riscv" )
ENTRY(_start)

MEMORY
{
    RAM (rwx) : ORIGIN = 0x0, LENGTH = 128M
}

SECTIONS
{
    .text : ALIGN(4)
    {
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
    } > RAM

    .data : ALIGN(4)
    {
        _sdata = .;   
        *(.data*)
        . = ALIGN(4);
        _edata = .; 
    } > RAM

    /* BSS still needs symbols because it must be zeroed at runtime */
    .bss : ALIGN(4)
    {
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > RAM

    . = ALIGN(4);
    _program_end = .;
}

