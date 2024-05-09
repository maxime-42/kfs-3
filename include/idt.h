#ifndef _IDT_H
#define _IDT_H

// #include <.h>
// #include <.h>
#include "config.h"

/* ************************************************************************** */
/* 			Structs                                               */
/* ************************************************************************** */

// struct idt_entry
// {
// 	uint16 offset_1; // Offset bits 0 - 15
// 	uint16 selector; // Selector thats in our GDT
// 	uint8 zero; // Does nothing, unused set to zero
// 	uint8 flags; // Descriptor type and attributes
// 	uint16 offset_2; // Offset bits 16-31
// } __attribute__((packed));

struct idt_entry
{
    uint16 base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
    uint16 sel;                 // Kernel segment selector.
    uint8  always0;             // This must always be zero.
    uint8  flags;               // More flags. See documentation.
    uint16 base_hi;             // The upper 16 bits of the address to jump to.

}__attribute__((packed));

// struct   idt_entry
// {
//     uint16 base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
//     uint16 sel;                 // Kernel segment selector.
//     uint8  always0;             // This must always be zero.
//     uint8  flags;               // More flags. See documentation.
//     uint16 base_hi;             // The upper 16 bits of the address to jump to.
// } __attribute__((packed));

struct idtr_desc
{
	uint16 limit; // Size of descriptor table -1
	uint32 base; // Base address of the start of the interrupt descriptor table
} __attribute__((packed));







/* ************************************************************************** */
/*				Prototype                                     */
/* ************************************************************************** */


void		init_idt();
extern void	load_idt(uint32 ptr);
// extern void load_idt(uint32 idt_ptr);
#endif // !
