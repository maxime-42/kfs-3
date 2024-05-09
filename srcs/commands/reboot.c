#include "config.h"
#include "io.h"

void reboot(void)
{
    uint8 good = 0x02;

    asm volatile ("cli");
    while (good & 0x02)
        good = inb(0X64);
    
    outb(0X64, 0xFE);
    asm volatile ("hlt");
}