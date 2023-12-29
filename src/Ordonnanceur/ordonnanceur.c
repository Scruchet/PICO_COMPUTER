#include "ordonnanceur.h"

typedef struct InfoTache {
    void (*depart)(void);
    uint16_t SPoint;
    int delay;
    uint8_t etat;
    uint8_t raison;
} tache_t;

tache_t Tache[NOMBRE_TACHE];

uint8_t id_tache;

void init_USART(long int vitesse)
{
    UBRR0 = FREQ_CPU / (((unsigned long int)vitesse) << 4) - 1;
    UCSR0B = (1 << TXEN0 | 1 << RXEN0);
    UCSR0C = (1 << UCSZ01 | 1 << UCSZ00);
    UCSR0A &= ~(1 << U2X0);
}

int sem_ecriture = 1;

void gestion_semaphore_ecriture(int ACTION)
{
    if (ACTION == PRENDRE) {
        while (1) {
            cli();
            if (sem_ecriture > 0) // Si ressource dispo
            {
                sem_ecriture = 0;
                sei();
                break;
            } else {
                // La ressource est occupée, on endort la tache
                Tache[id_tache].etat = ENDORMI;
                Tache[id_tache].raison = ECRITURE;
                TCNT1 = 0;
                TIMER1_COMPA_vect();
            }
            sei();
            while (sem_ecriture == 0)
                ;
        }
    }
    if (ACTION == LACHER) {
        cli();
        sem_ecriture = 1;
        sei();
    }
}

int sem_lecture = 1;

void gestion_semaphore_lecture(int ACTION)
{
    if (ACTION == PRENDRE) {
        while (1) {
            cli();
            if (sem_lecture > 0) // Si ressource dispo
            {
                sem_lecture = 0;
                sei();
                break;
            } else {
                // La ressource est occupée, on endort la tache
                Tache[id_tache].etat = ENDORMI;
                Tache[id_tache].raison = LECTURE;
                TCNT1 = 0;
                TIMER1_COMPA_vect();
            }
            sei();
            while (sem_lecture == 0)
                ;
        }

    } else if (ACTION == LACHER) {
        cli();
        sem_lecture = 1;
        sei();
    }
}

void USART_ecrire_str(char* chaine)
{
    gestion_semaphore_ecriture(PRENDRE); // On passe en état occupé
    serialWrite(chaine);
    gestion_semaphore_ecriture(LACHER); // On libère aprés l'utilisation
}

void USART_lire_str(char* chaine, int taille)
{
    gestion_semaphore_lecture(PRENDRE);
    for (int i = 0; i < taille; i++)
        chaine[i] = serialRead();
    gestion_semaphore_lecture(LACHER);
}

void sleep_ms(uint16_t nb_ms)
{
    cli();
    Tache[id_tache].delay = nb_ms;
    Tache[id_tache].etat = ENDORMI;
    Tache[id_tache].raison = DELAY;
    TCNT1 = 0;
    sei();
    TIMER1_COMPA_vect();
}

void serie_envoyer(unsigned char c)
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
}

void serie_envoyer_mt(char* chaine)
{
    gestion_semaphore_ecriture(PRENDRE); // On passe en état occupé
    int i;
    for (i = 0; i < strlen(chaine); i++)
        serie_envoyer(chaine[i]);
    gestion_semaphore_ecriture(LACHER); // On libère aprés l'utilisation
}

char str[MAX_CHAINE + 1];
unsigned char chaine_prete = 0;

void Tache_EcritureSiLecture()
{
    while (1) {
        if (chaine_prete) {
            USART_ecrire_str(str);
            chaine_prete = 0;
        }
        _delay_ms(20);
    }
}

void Tache_Lire()
{
    while (1) {
        USART_lire_str(str, MAX_CHAINE);
        str[MAX_CHAINE] = '\0';
        chaine_prete = 1;
        sleep_ms(200);
    }
}

void Tache_Ecriture2()
{
    while (1) {
        USART_ecrire_str("ABC\r\n");
        sleep_ms(300);
    }
}

void tache0()
{
    DDRD |= (1 << PD4);
    while (1) {
        PORTD ^= (1 << PD4);
        sleep_ms(1000);
    }
}

void tache1()
{
    DDRD |= (1 << PD1);
    while (1) {
        PORTD ^= (1 << PD1);
        sleep_ms(1000);
    }
}

void tache2()
{
    DDRD |= (1 << PD7);
    while (1) {
        PORTD ^= (1 << PD7);
        sleep_ms(1000);
    }
}

void tache3()
{
    DDRC |= (1 << PC3);
    while (1) {
        PORTC ^= (1 << PC3);
        sleep_ms(1000);
    }
}

void tache4()
{
    DDRC |= (1 << PC0);
    while (1) {
        PORTC ^= (1 << PC0);
        _delay_ms(INTERRUPT_MS);
    }
}

void ordonnanceur()
{
    for (int i = 0; i < NOMBRE_TACHE; i++) {
        if (Tache[i].etat == ENDORMI && Tache[i].raison == DELAY) {
            uint16_t ms = INTERRUPT_MS;
            if (TCNT1 != 0) {
                ms = ((10 * TCNT1 * INTERRUPT_MS) / OCR1A) / 10;
                TCNT1 = 0;
            }
            Tache[i].delay -= ms;
            if (Tache[i].delay <= 0) {
                Tache[i].etat = EVEILLER;
            }
            if (Tache[i].etat == ENDORMI && Tache[i].raison == ECRITURE && sem_ecriture > 0)
                Tache[id_tache].etat = EVEILLER;
            if (Tache[i].etat == ENDORMI && Tache[i].raison == LECTURE && sem_lecture > 0)
                Tache[id_tache].etat = EVEILLER;
        }
    }
    do {
        id_tache++;
        if (id_tache >= NOMBRE_TACHE) {
            id_tache = 0;
        }
    } while (Tache[id_tache].etat == ENDORMI);
}

ISR(TIMER1_COMPA_vect, ISR_NAKED)
{
    /* Sauvegarde du contexte de la tâche interrompue */
    portSAVE_CONTEXT();
    Tache[id_tache].SPoint = SP;

    /* Appel à l'ordonnanceur */

    ordonnanceur();

    /* Récupération du contexte de la tâche ré-activée */
    SP = Tache[id_tache].SPoint;
    portRESTORE_CONTEXT();
    asm volatile("reti");
}

void init_taches(int pid)
{
    uint16_t sauvegarde = SP;
    SP = Tache[pid].SPoint;
    uint16_t adresse = (uint16_t)Tache[pid].depart;
    asm volatile("push %0"
                 :
                 : "r"(adresse & 0x00ff));
    asm volatile("push %0"
                 :
                 : "r"((adresse & 0xff00) >> 8));
    portSAVE_CONTEXT();
    Tache[pid].SPoint = SP;
    SP = sauvegarde;
}

void setup()
{
    id_tache = 0;
    // Initialisation des LED

    Tache[0].depart = &Tache_EcritureSiLecture;
    Tache[1].depart = &Tache_Lire;
    Tache[2].depart = &Tache_Ecriture2;
    // Tache[3].depart = &tache3;
    // Tache[4].depart = &tache4;

    Tache[0].SPoint = 0x0400;
    Tache[1].SPoint = 0x0600;
    Tache[2].SPoint = 0x0800;
    // Tache[3].SPoint = 0x0A00;
    // Tache[4].SPoint = 0x0C00;

    for (int i = 0; i < NOMBRE_TACHE; i++) {
        init_taches(i);
        Tache[i].etat = EVEILLER;
    }

    TCCR1A = 0; // No output pin connected, no PWM mode enabled
    TCCR1B = 1 << CTC1; // No input pin used, clear timer counter on compare match
#if (PRESCALER == 8)
    TCCR1B |= (1 << CS11);
#endif
#if (PRESCALER == 64)
    TCCR1B |= (1 << CS11 | 11 << CS10);
#endif
#if (PRESCALER == 256)
    TCCR1B |= (1 << CS12);
#endif
#if (PRESCALER == 1024)
    TCCR1B |= (1 << CS12 | 1 << CS10);
#endif
    OCR1A = NB_TICK;
    TCNT1 = 0;
    TIMSK1 = (1 << OCIE1A);

    init_USART(9600);
}

int main(void)
{
    setup();
    SP = Tache[id_tache].SPoint;
    sei();
    Tache_EcritureSiLecture();
}
