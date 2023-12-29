MMCU = atmega328p
FCPU = 16000000

CC = avr-gcc
FLAGS = -mmcu=$(MMCU)
CFLAGS = -Wall $(FLAGS) -DF_CPU=$(FCPU) -Os
LDFLAGS = $(FLAGS)
OUTPUT = ttyUSB0
TARGET = main

all: $(TARGET).hex

clean:
	rm -f *.o $(TARGET).hex $(TARGET).elf $(TARGET).asm $(TARGET)

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c -I. $< -o $@

spi.o: ../../SPI/spi.c ../../SPI/spi.h
	$(CC) $(CFLAGS) -c -I. $< -o $@

$(TARGET).elf: $(TARGET).o spi.o
	$(CC) $(LDFLAGS) -g -lm -Wl,--gc-sections -o $@ $^

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -j .text -j .data -O ihex $< $@

upload: $(TARGET).hex
	stty -F /dev/$(OUTPUT) hupcl
	avrdude -F -v -p $(MMCU) -c stk500v1 -b 115200 -P /dev/$(OUTPUT) -U flash:w:$<

format:
	clang-format -i -style="WebKit" $(TARGET)*

asm:
	avr-objdump -D -m avr -b ihex $(TARGET).hex > $(TARGET).asm
