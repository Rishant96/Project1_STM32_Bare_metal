TARGET = main
MCU = cortex-m3

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

CFLAGS = -mcpu=$(MCU) -mthumb -O2 -Wall -Wextra -nostdlib -ffreestanding
LDFLAGS = -T linker.ld -nostdlib

UNITY_SRC = unity.c

ELF = $(TARGET).elf
BIN = $(TARGET).bin

all: $(BIN) size

$(UNITY_SRC): startup.c main.c
	@echo "/* Unity Build File */" > $(UNITY_SRC)
	@echo '#include "startup.c"' >> $(UNITY_SRC)
	@echo '#include "main.c"' >> $(UNITY_SRC)

$(ELF): $(UNITY_SRC) linker.ld MCU_STM32.h
	$(CC) $(CFLAGS) $(UNITY_SRC) -o $(ELF) $(LDFLAGS)

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $(ELF) $(BIN)

size:
	$(SIZE) $(ELF)

flash: $(BIN)
	st-flash write $(BIN) 0x08000000

clean:
	rm -f $(UNITY_SRC) $(ELF) $(BIN)

.PHONY: all flash clean size

