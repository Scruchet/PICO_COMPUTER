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
    int i = 2; // Selection du CS2
    int compteur = 0; // Compteur à afficher
    spi_init();
    luminosite_ecran(LUM_MAX, CS[2]); // Mettre luminosité à fond
    while (1) {
        afficher_nombre(compteur, CS[i]); // afficher le compteur
        compteur += 1;
        if (compteur > 9999) // Si dépacement de l'affichage, réinitialiser
            compteur = 0;
        _delay_ms(200);
    }
    return 1;
}
