#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>

#include "../../Memoire/AT45DB641E.h"
#include "../../UART/UART.h"

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

// Fonction test pour la mémoire, renvoie 1 par UART si la mem fonctionne et 0 sinon
int main()
{
    spi_init();
    serialInit();
    unsigned char writeData[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE };

    // Adresse à laquelle écrire et lire
    int address = 1;

    // Écriture des données dans la mémoire
    AT45DB641E_write_buffer(CS[1], writeData, sizeof(writeData), SEQ_START | SEQ_STOP);
    AT45DB641E_write_page(CS[1], address);

    // Lecture des données depuis la même adresse
    unsigned char readData[sizeof(writeData)];
    AT45DB641E_read_page(CS[1], address, readData, sizeof(readData), SEQ_START | SEQ_STOP);

    // Vérification des données lues avec celles écrites
    int i;
    while (1) {
        for (i = 0; i < sizeof(writeData); i++) {
            if (readData[i] == writeData[i]) {
                serialWrite("Cela fonctionne parfaitement!\r\n");
            } else {
                serialWrite("Coup dur....!\r\n");
            }
            _delay_ms(1000);
        }
    }

    return 0;
}
