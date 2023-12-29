# PICO Computer Project: Motherboard

Welcome to my PICO Computer project repository. This section consolidates all the source files written in the C language used by my motherboard, as well as the electronic components created with KiCad. The primary goal of this project is to create a motherboard that can be connected to other boards (screen, keyboard, network) to build a Pico Computer.

## Part 1: Motherboard
You can find all the plans for my board in the **Motherboard_pico** directory.

### Features
This board is composed of multiple components. The main IC is the Atmega328p, which acts as the processor. The FTDI serves as the connection between the USB port and the Atmega328p (it does not include USB). The AT45DB641E is the storage component of the computer. As this component works with 3.3V signals, a buffer is needed to convert the 5V signals from the Atmega328p to 3.3V. To connect all the other cards, there are 5 HE10 connectors. All the different cards communicate using SPI (MOSI, MISO, SS, SCK).

## Part 2: Source Section (src)

This section includes all the source files written in the C language used by my motherboard. In addition to the source files, there is also a test folder to demonstrate various evaluations performed during the project's development.

### Module Details

#### Makefile
The Makefile enables project compilation and management. Refer to this file for details on compilation, linking, and other build tasks. In each directory, you can run the code (excluding files without main.c) and upload the code using the `make upload` command.

#### Memory
The Memory directory contains files related to memory management, including handling a specific flash memory (AT45DB641E).

#### Scheduler
The Scheduler module includes files necessary for implementing a scheduler. Refer to `makefile`, `scheduler.c`, and `scheduler.h` for more details.

#### SPI
The SPI module contains the files `spi.c` and `spi.h` for managing communication via the Serial Peripheral Interface (SPI) bus.

#### UART
The UART module includes the files `UART.c` and `UART.h`, dedicated to asynchronous serial communication (UART).

#### Tests
The Tests directory includes several subdirectories, each containing specific tests.

- `7seg`: Tests related to the 7-segment display (https://www.sparkfun.com/products/11441).
- `Mat_leds`: Tests for the LED matrix (https://www.sparkfun.com/products/retired/760).
- `Mem`: Tests for memory management.
- `UART_SPI`: Tests for UART and SPI modules.

# Contact
Thank you for visiting my project. If you have any comments or questions, please feel free to contact me via email at the following address: cruchetsimon@gmail.com
