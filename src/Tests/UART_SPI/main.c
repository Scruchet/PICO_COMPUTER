#include "../../SPI/spi.h"
#include "../../UART/UART.h"
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>

#define CS_PIN 4 // Chip Select sur PD4

const cs_t CS[] = {
    { 0, NULL },
    { CS1, &PORTD },
    { CS2, &PORTC },
    { CS3, &PORTC },
    { CS4, &PORTD },
    { CS5, &PORTD },
    { CS6, &PORTB },
};

int main()
{
    serialInit();
    spi_init();

    unsigned char receivedChar;

    while (1) {
        receivedChar = serialRead();
        if (receivedChar == 'a') {
            afficher_nombre(2442, CS[2]);
        } else
            afficher_nombre(9999, CS[2]);
    }
}
