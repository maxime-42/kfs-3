#ifndef _CONFIG_H
#define _CONFIG_H

#define		TOTAL_INTERRUPTS 256
#define		ISR0 0
#define		ISR1 4
#define		ISR2 2

#define		CODE_SELECTOR 0x08
#define		DATA_SELECTOR 0x10
#define		KEYBOARD_BUFFER_SIZE 1024
#define 	NUM_MAX_MSG 15
#define		MAX_HANDLERS 256
#define		NUM_EXCEPTION_MSG 19
#define		NB_EXCEPTION 32
#define		KEYBOARD_DATA_PORT      0x60
#define		OFFSET1 0x20
#define		OFFSET2 0x28
#define		IRQ0	32
#define		IRQ1	33
#define 	DECIMAL 10
#define 	HEX_BASE 16

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;

/*##############################################*/
#define INTERRUPT_MASK_ALL 0x00
#define INTERRUPT_MASK_TIMER 0xFE
#define INTERRUPT_MASK_KEYBOARD 0xFD
#define INTERRUPT_MASK_RESERVED 0xFF
#define INTERRUPT_MASK_SYSCALL 0x7F
#define PIC_1 0x20
#define PIC_2 0xA0
#define PIC_1_COMMAND PIC_1
#define PIC_1_DATA (PIC_1 + 1)
#define PIC_2_COMMAND PIC_2
#define PIC_2_DATA (PIC_2 + 1)

#define PIC_1_OFFSET 0x20
#define PIC_2_OFFSET 0x28
#define PIC_2_END (PIC_2_OFFSET + 7)
#define PIC_ICW1_ICW4 0x01
#define PIC_ICW1_SINGLE 0x02
#define PIC_ICW1_INTERVAL4 0x04
#define PIC_ICW1_LEVEL 0x08
#define PIC_ICW1_INIT 0x10
#define PIC_ICW4_8086 0x01
#define PIC_ACKNOWLEDGE 0x20
#define COM1 0x3f8          // COM1

// #define """ 

#define CLEAN_REGISTERS() asm volatile ("xor %eax, %eax"); \
                        asm volatile ("xor %ebx, %ebx"); \
                        asm volatile ("xor %ecx, %ecx"); \
                        asm volatile ("xor %edx, %edx");
#endif // !

#define ERROR -1