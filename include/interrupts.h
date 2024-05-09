#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H
#include "libk.h"
#include "config.h"

/* ************************************************************************** */
/* 			Structs                                               */
/* ************************************************************************** */

/*
	this ructure provides a convenient way to access the CPU register 
	values and other relevant information during interrupt or exception 
	handling 
*/
typedef struct __attribute__((packed)) interrupt_frame
{
    uint32 ds; 
    uint32 edi;
    uint32 esi;
    uint32 ebp;
    uint32 esp;
    uint32 ebx;
    uint32 edx;
    uint32 ecx;
    uint32 eax;
    uint32 int_no;
    uint32 err_code; 
    uint32 eip;
    uint32 cs;
    uint32 eflags;
    uint32 useresp;
    uint32 ss; 
} t_interrupt_frame; 

// typedef struct  __attribute__((packed)) interrupt_frame{
//     uint32 cr2;
//     uint32 ds;
//     uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
//     uint32 int_no, err_code;
//     uint32 eip, csm, eflags, useresp, ss;
// }t_interrupt_frame;

/* ************************************************************************** */
/* 			Prototy                                               */
/* ************************************************************************** */


typedef  void (*t_interrupt_handler)(t_interrupt_frame);

void						pic_map(void);
extern	void				panic();
void						init_handlers(void);
int							add_handler(uint32 n, t_interrupt_handler handler);
t_interrupt_handler 		get_interrupt_handler(uint32 n);
extern void 				halt(void);
extern void					enable_interrupts(void);
extern	void				kpanic();

void						pic_remap(uint8 offset1, uint8 offset2);

void						init_pit(uint32 hz);
void						isr_handler(t_interrupt_frame frame);
void						irq_handler(t_interrupt_frame frame);
void						acknowledge(unsigned int interrupt);
void						init_syscalls(void);


/* ************************************************************************** */
/* 			Prototy isr                                               */
/* ************************************************************************** */




extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);
// extern void isr32(void);


/* ************************************************************************** */
/* 			Prototy irq                                               */
/* ************************************************************************** */
extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);
#endif // !_INTERRUPTS_H
