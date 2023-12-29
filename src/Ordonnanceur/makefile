MCU = atmega328p
FCPU = 16000000

CC = avr-gcc
FLAGS = -mmcu=$(MCU)
CFLAGS = -Wall $(FLAGS) -DF_CPU=$(FCPU) -Os
LDFLAGS = $(FLAGS)
PORT = USB0
TARGET = ordonnanceur

all: $(TARGET).hex
	
$(TARGET).o: $(TARGET).c $(TARGET).h
	$(CC) $(CFLAGS) -c -I. $< -o $@
	
spi.o: ../SPI/spi.c ../SPI/spi.h
	$(CC) $(CFLAGS) -c -I. $< -o $@
	
UART.o: ../UART/UART.c ../UART/UART.h
	$(CC) $(CFLAGS) -c -I. $< -o $@
	
$(TARGET).elf: $(TARGET).o spi.o UART.o
	$(CC) $(LDFLAGS) -g -lm -Wl,--gc-sections -o $@ $^

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -j .text -j .data -O ihex $< $@

upload: $(TARGET).hex
	stty -F /dev/tty$(PORT) hupcl
	avrdude -F -v -p $(MCU) -c stk500v1 -b 115200 -P /dev/tty$(PORT) -U flash:w:$<

clean:
	rm -f *.o $(TARGET).hex $(TARGET) *.elf

format:
	clang-format -i -style="WebKit" $(TARGET)*
