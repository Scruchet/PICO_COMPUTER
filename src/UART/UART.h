#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
// #define F_CPU 16000000	// 16 MHz oscillator.
#define BaudRate 9600
#define MYUBRR (F_CPU / 16 / BaudRate) - 1

unsigned char serialCheckRxComplete(void);
unsigned char serialCheckTxReady(void);
unsigned char serialRead(void);
void serialsend(unsigned char DataOut);
void serialInit(void);
void serialWrite(char* Data);
