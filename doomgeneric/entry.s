.global _start
_start:
  lui sp, 0x10000
  call c_start
loop:
  j loop
