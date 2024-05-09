#ifndef IO_H
#define IO_H
#include "config.h"


extern unsigned char inb(uint16 port);
extern unsigned short insw(unsigned short port);
extern void outb(unsigned short port, uint8 val);
extern void outw(uint16 port, uint16  val);



// uint8 inb(uint16 port);
// void outb(uint16 port, uint8 value);
// void outw(uint16 port, uint16 value);

#endif