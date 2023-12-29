/*****************************
* AT45DB641E memory handling *
*****************************/

#include <stdio.h>
#include <stdint.h>

#include "AT45DB641E.h"

// AT45DB641E page mode
void AT45DB641E_page_size(cs_t cs,int size){

set_activer(cs);
if(size!=256 && size!=264) return;
SPI_trans(0x3D);
SPI_trans(0x2A);
SPI_trans(0x80);
if(size==256) SPI_trans(0xA6); else SPI_trans(0xA7);
set_desactiver(cs);
}

// AT45DB641E command

void AT45DB641E_cmd(cs_t cs,int cmd,uint8_t *result,int len){
set_activer(cs);
SPI_trans(cmd);
int i;
for(i=0;i<len;i++) result[i]=SPI_trans(0);
set_desactiver(cs);
}

// AT45DB641E test busy

unsigned char AT45DB641E_busy(cs_t cs){
unsigned char status[2];
AT45DB641E_cmd(cs,AT45DB641E_Status,status,2);
return status[0]&0x80?0:1;
}

// AT45DB641E write into first buffer

void AT45DB641E_write_buffer(cs_t cs,unsigned char *data,int len,unsigned char synfin){
int i;
if(synfin&SEQ_START){
  set_activer(cs);
  SPI_trans(0x84);
  for(i=0;i<3;i++) SPI_trans(0x00);
  }
if(data!=NULL && len>0)
  for(i=0;i<len;i++) SPI_trans(data[i]);
if(synfin&SEQ_STOP){
  set_desactiver(cs);
  while(AT45DB641E_busy(cs));
  }
}

// AT45DB641E write first buffer into a flash page

void AT45DB641E_write_page(cs_t cs,int address){
set_activer(cs);
SPI_trans(0x83);
SPI_trans((address>>8)&0x7f);
SPI_trans(address&0xff);
SPI_trans(0x00);
set_desactiver(cs);
while(AT45DB641E_busy(cs));
}

// AT45DB641E read

void AT45DB641E_read_page(cs_t cs,int address,unsigned char *data,int len,unsigned char synfin){
int i;
if(synfin&SEQ_START){
  set_activer(cs);
  SPI_trans(0x1B);
  SPI_trans((address>>8)&0x7f);
  SPI_trans(address&0xff);
  for(i=0;i<3;i++) SPI_trans(0x00);
  }
if(data!=NULL && len>0)
  for(i=0;i<len;i++) data[i]=SPI_trans(0x00);
if(synfin&SEQ_STOP){
  set_desactiver(cs);
   while(AT45DB641E_busy(cs));
  }
}
