.global _start
_start:
  li sp, 0x1800000
  call c_start
loop:
  j loop
