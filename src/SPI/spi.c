#include "spi.h"



const uint8_t chiffre_7_seg[] = {
    0b0111111, // 0
    0b0000110, // 1
    0b1011011, // 2
    0b1001111, // 3
    0b1100110, // 4
    0b1101101, // 5
    0b1111101, // 6
    0b0000111, // 7
    0b1111111, // 8
    0b1101111 // 9
};
void spi_init()
{
    // Initialisation des ports en mode SPI (sorties et entrées)
    DDRB |= (1 << PB2);
    DDRB |= (1 << MOSI);
    DDRB &= ~(1 << MISO);
    DDRB |= (1 << SCK);
    // Initialisation des différents CS(1-6)
    DDRD|= (1 << CS1);
    DDRC |= (1 << CS2);
    DDRC |= (1 << CS3);
    DDRD |= (1 << CS4);
    DDRD |= (1 << CS5);
    DDRB |= (1 << CS6);
    // Desactiver les différents esclaves
    PORTD |= (1 << CS1);
    PORTC |= (1 << CS2);
    PORTC |= (1 << CS3);
    PORTD |= (1 << CS4);
    PORTD |= (1 << CS5);
    PORTB |= (1 << CS6);
    // Configuration des paramètres du mode de com SPI avec une fréquence de 125KHz
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);
}

// Permet de desactiver un esclave en mettant son CS à 1
void set_desactiver(cs_t cs)
{

    *(cs.port) |= (1 << cs.pin);
}

// Permet d'activer un esclave en mettant son CS à 0
void set_activer(cs_t cs)
{

    *(cs.port) &= ~(1 << cs.pin);
}

// Envoie un octet sur le bus SPI
uint8_t SPI_trans(uint8_t data)
{
    // Début de la transmission
    SPDR = data;

    // Attendre que la transmission ne finisse
    while (!(SPSR & (1 << SPIF)))
        ;
    return SPDR;
}

void nettoyerEcran(cs_t cs)
{
    set_activer(cs); // Esclave à l'écoute
    SPI_trans(C_NET); // Commande pour nettoyer l'écran
    set_desactiver(cs); // ESclave s'endort
}

void luminosite_ecran(uint8_t value, cs_t cs)
{
    set_activer(cs); // Esclave à l'écoute
    SPI_trans(C_LUM); // Commande pour choisir la luminosité de l'écran
    SPI_trans(value); // Valeur de la luminosité (0-255)
    set_desactiver(cs); // Esclave s'endort
}

void afficher_nombre(unsigned short int valeur, cs_t cs)
{
    unsigned short int mille, cent, dix, unite;
    mille = valeur / 1000;
    cent = (valeur - mille * 1000) / 100;
    dix = (valeur - mille * 1000 - cent * 100) / 10;
    unite = (valeur - mille * 1000 - cent * 100 - dix * 10);
    set_activer(cs);
    SPI_trans(C_MIL);
    SPI_trans(chiffre_7_seg[mille]);
    SPI_trans(C_CEN);
    SPI_trans(chiffre_7_seg[cent]);
    SPI_trans(C_DIX);
    SPI_trans(chiffre_7_seg[dix]);
    SPI_trans(C_UNI);
    SPI_trans(chiffre_7_seg[unite]);
    set_desactiver(cs);
}

void mettre_couleur(uint8_t couleur, cs_t cs)
{
    set_activer(cs); // Esclave à l'écoute
    SPI_trans(0x26); // Commande pour réinitialiser l'incide d'image
    for (int i = 0; i < 64; i++) {
        SPI_trans(couleur); // Transferer 64 octets pour mettre les leds en Orange
    }
    set_desactiver(cs); // Esclave s'endort
}
