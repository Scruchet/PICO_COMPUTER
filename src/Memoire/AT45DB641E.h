/********************************
* AT45DB641E memory definitions *
*********************************/

// Constants

#define AT45DB641E_Manufacturer	0x9f
#define AT45DB641E_Status	0xd7

#define SEQ_START		1
#define SEQ_STOP		2
#include "../SPI/spi.h"
// Prototypes 

void AT45DB641E_page_size(cs_t cs,int size);
void AT45DB641E_cmd(cs_t cs,int cmd,uint8_t *result,int len);
unsigned char AT45DB641E_busy(cs_t cs);
void AT45DB641E_write_buffer(cs_t cs,unsigned char *data,int len,unsigned char synfin);
void AT45DB641E_write_page(cs_t cs,int address);
void AT45DB641E_read_page(cs_t cs,int address,unsigned char *data,int len,unsigned char synfin);

