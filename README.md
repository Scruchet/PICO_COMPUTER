# PICO Computer Project: Motherboard

Welcome to the repository of our PICO Computer project. This section gathers all the source files written in the C language used by our motherboard, as well as the electronic part created with KiCad.

## Part 1: Motherboard

### Plans and Schematics
You can find all the plans for our board in the **Motherboard_pico** directory.

## Part 2: Source Section (src)

This section includes all the source files written in the C language used by our motherboard. In addition to the source files, we have also included a test folder to demonstrate various evaluations performed during the project's development.

### Module Details

#### Makefile
The Makefile enables project compilation and management. Refer to this file for details on compilation, linking, and other build tasks. In each directory, you can run the code (excluding files without main.c) and upload the code using the `make upload` command.

#### Memory
The Memory directory contains files related to memory management, including handling a specific flash memory (AT45DB641E).

#### Scheduler
The Scheduler module includes files necessary for implementing a scheduler. Refer to `makefile`, `scheduler.c`, and `scheduler.h` for more details.

#### SPI
The SPI module contains the files `spi.c` and `spi.h` for managing communication via the Serial Peripheral Interface (SPI) bus.

#### Tests
The Tests directory includes several subdirectories, each containing specific tests.

- `7seg`: Tests related to 7-segment display.
- `Mat_leds`: Tests for the LED matrix.
- `Mem`: Tests for memory management.
- `UART_SPI`: Tests for UART and SPI modules.

#### UART
The UART module includes the files `UART.c` and `UART.h`, dedicated to asynchronous serial communication (UART).
