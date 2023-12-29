#include "UART.h"

unsigned char serialCheckTxReady(void)
{
    return (UCSR0A & _BV(UDRE0)); // nonzero if transmit register is ready to receive new data.
}

void serialsend(unsigned char DataOut)
{
    while (serialCheckTxReady() == 0) // while NOT ready to transmit
    {
        ;
        ;
    }
    UDR0 = DataOut;
}

void serialWrite(char* Data)
{
    for (int i = 0; i < strlen(Data); i++) {
        serialsend((unsigned char)Data[i]);
    }
}

unsigned char serialCheckRxComplete(void)
{
    return (UCSR0A & _BV(RXC0)); // nonzero if serial data is available to read.
}

unsigned char serialRead(void)
{
    while (serialCheckRxComplete() == 0) // While data is NOT available to read
    {
        ;
        ;
    }
    return UDR0;
}

void serialInit(void)
{
    // Serial Initialization
    /*Set baud rate 9600 */
    UBRR0H = (unsigned char)((MYUBRR) >> 8);
    UBRR0L = (unsigned char)MYUBRR;
    /* Enable receiver and transmitter */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    /* Frame format: 8data, No parity, 1stop bit */
    UCSR0C = (3 << UCSZ00);
}

// Permet d'afficher des chaines de caractères sur le bus UART
//  int main(){
//      serialInit();
//      spi_init();
//      char *phrase = "Bonjour le monde\r\n";
//      while(1){
//              serialWrite(phrase);
//              _delay_ms(1000);
//      }
//      return 0;
//  }
// Permet d'afficher 2222 si sur a sur le port serie 9999 si autre caractère
//  int main(){
//      serialInit();
//      spi_init();
//
//      unsigned char receivedChar;
//
//      while(1){
//          receivedChar = serialRead();
//          if (receivedChar == 'a'){
//                  afficher_nombre(2222, CS[2]);
//          }
//          else
//              afficher_nombre(9999, CS[2]);
//      }
//
//  }
