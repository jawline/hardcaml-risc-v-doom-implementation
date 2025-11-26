CC=riscv32-unknown-elf-gcc
AR=riscv32-unknown-elf-ar
C_FILES := $(wildcard *.c)
O_FILES := $(patsubst %.c,%.o,$(C_FILES))
LIBRARY := libminlibc.a

all: $(LIBRARY)

clean:
	$(RM) $(O_FILES) $(LIBRARY)

$(LIBRARY): $(O_FILES)
	$(AR) cr $(LIBRARY) $(O_FILES)

%.o: %.c
	$(CC) -c -nostdinc -ffreestanding -nostdlib -nostartfiles -march=rv32i -mabi=ilp32 -Iinclude/ -o $@ -L/home/ubuntu/gcc-riscv/riscv32-unknown-elf/lib/ -lm -lgcc $<
