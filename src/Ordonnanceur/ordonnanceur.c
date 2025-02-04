#include "ordonnanceur.h"

// Fonction pour vider le tampon de réception (RX)
void USART_FlushRX(void) {
    unsigned char dummy;
    // Lire tous les caractères reçus et les jeter jusqu'à ce que le tampon soit vide
    while (UCSR0A & (1 << RXC0)) {
        dummy = UDR0;  // Lire et ignorer le caractère
    }
}

// Fonction de réception d'une chaîne de caractères
void USART_ReceiveString(char* buffer, int maxLength) {
    int i = 0;
    char c;

    // Réception des caractères jusqu'à la fin de la chaîne ou la longueur max
    while (i < maxLength - 1) {  // Ne jamais dépasser la taille du buffer moins 1
        serialWrite("Dans la boucle à i : ");
        char i_char = i + '0';
        serialWrite(i_char);
        serialWrite("\r\n");  
        if (USART_DataAvailable()) {
            c = serialRead();  // Lire un caractère de l'USART

            // Si le caractère est une fin de chaîne (retour chariot ou NULL), on termine
            if (c == '\n' || c == '\0') {
                buffer[i] = '\0';  // Terminer la chaîne avec '\0'
                break;
            }

            // Ajouter le caractère au buffer
            buffer[i] = c;
            i++;
        }
    }

    // Ajouter un caractère de fin de chaîne si le buffer est plein
    buffer[i] = '\0';  // Garantir que la chaîne est bien terminée
}

// Fonction pour vérifier si des données sont disponibles dans le tampon de réception
int USART_DataAvailable(void) {
    // Vérifie si le bit RXC0 est à 1, ce qui signifie que des données ont été reçues
    return (UCSR0A & (1 << RXC0));
}

int main(void)
{
    serialInit();
    char receivedChar[100];  // Buffer pour stocker la chaîne reçue

    while (1) {
        if (USART_DataAvailable()) {
            // Attendre que les données arrivent et recevoir la chaîne complète
            USART_ReceiveString(receivedChar, 100);

            // Envoyer la chaîne reçue en réponse
            serialWrite(receivedChar);
            _delay_ms(10);  // Délai pour stabiliser
        }

        _delay_ms(500);  // Délai de boucle (pour éviter un polling trop rapide)
    }

    return 0;
}
