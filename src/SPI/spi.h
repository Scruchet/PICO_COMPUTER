#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <util/delay.h>

#ifndef SPI_H
#define SPI_H

// Différents ports et leurs attributions
#define MOSI PB3
#define SCK PB5
#define MISO PB4
#define CS1 PD4
#define CS2 PC2
#define CS3 PC3
#define CS4 PD7
#define CS5 PD1
#define CS6 PB2

// Différentes commandes pour la transmission SPI
#define C_NET 0X76
#define C_LUM 0x7A
#define C_MIL 0x7B
#define C_CEN 0x7C
#define C_DIX 0x7D
#define C_UNI 0x7E
#define LUM_MAX 255

// Différentes couleur pour la matrice

#define MAT_BLACK 0x00
#define MAT_ROUGE 0xE0
#define MAT_VERT 0x1C
#define MAT_BLEU 0x03
#define MAT_VIOLET 0xE3
#define MAT_LOBSTER 0x1F
#define BLANC 0xFF

// Structure pour les différents esclaves
typedef struct cs {
    uint8_t pin;
    volatile uint8_t* port;
} cs_t;





// Prototype des fonctions
void spi_init();
void set_desactiver(cs_t tab_cs);
void set_activer(cs_t tab_cs);
uint8_t SPI_trans(uint8_t data);
void nettoyerEcran(cs_t tab_cs);
void luminosite_ecran(uint8_t value, cs_t cs);
void afficher_nombre(unsigned short int valeur, cs_t cs);
void mettre_couleur(uint8_t couleur, cs_t cs);
//
#endif // SPI_H
