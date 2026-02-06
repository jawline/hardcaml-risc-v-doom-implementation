.global _start
_start:
  li sp, 8388608
  call c_start
loop:
  j loop
