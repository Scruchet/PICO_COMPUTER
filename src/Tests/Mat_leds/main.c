#include "../../SPI/spi.h"
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
    spi_init();
    while (1) {
        mettre_couleur(MAT_LOBSTER, CS[2]);
        _delay_ms(500);
        mettre_couleur(MAT_VERT, CS[2]);
        _delay_ms(500);
    }
    return 1;
}
