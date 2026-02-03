OUTPUT_ARCH( "riscv" )
ENTRY( _start )

MEMORY {
  RAM (rwx) : ORIGIN = 0x0, LENGTH = 64M
}

SECTIONS {
    .init : { *(.init) } > RAM
    .text : { *(.text .text.*) } > RAM
    .rodata : { *(.rodata) } > RAM
    .bss : { *(.bss) } > RAM
    .sbss : { *(.sbss) } > RAM
    .data : { *(.data) } > RAM
    . = ALIGN(4);
}
