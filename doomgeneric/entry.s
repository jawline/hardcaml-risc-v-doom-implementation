.global _start
_start:
  lui  sp, 25600 

  # 2. Clear the BSS section
  la t0, _sbss       # Start of BSS (from linker script)
  la t1, _ebss       # End of BSS (from linker script)

bss_loop:
  bge t0, t1, bss_done # If current address >= end address, exit loop
  sw x0, 0(t0)         # Write zero to memory
  addi t0, t0, 4       # Move to next 4-byte word
  j bss_loop

bss_done:
  call c_start

loop:
  j loop
