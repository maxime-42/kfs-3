#include "idt.h"
#include "config.h"
#include "libk.h"
#include "interrupts.h"
#include "io.h"

struct idt_entry idt_entries[TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;

/*********************************************************
 * @brief: this function sets the idt table
 * 
 * @param: num - the interrupt number
 * 		   base - the base address of the interrupt handler
 * 
 * @return: none
 * 
*  @details: 
 * 

**********************************************************/
static void idt_set(uint8 num, uint32 base)
{
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

    idt_entries[num].sel = CODE_SELECTOR;
    idt_entries[num].always0 = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    idt_entries[num].flags = 0x8E  | 0x60;
    // idt_entries[num].flags = 0x60;
}


/******************************************************
 * @brief: ths function initializes the idt table
 * 
 * @param: none
 * 
 * @return: none
*  @details:initialize the handlers and map thepic;
 * 
*******************************************************/
void	init_idt()
{
	kmemset(idt_entries, 0, sizeof(idt_entries ) );
	idtr_descriptor.limit = sizeof(struct idt_entry) * TOTAL_INTERRUPTS - 1;
	idtr_descriptor.base = (uint32) idt_entries;

	init_handlers();// initialize the handlers

	pic_map();// map the pic

	
	idt_set(0, (uint32)isr0 );
    idt_set(1, (uint32)isr1 );
    idt_set(2, (uint32)isr2 );
    idt_set(3, (uint32)isr3 );
    idt_set(4, (uint32)isr4 );
    idt_set(5, (uint32)isr5 );
    idt_set(6, (uint32)isr6 );
    idt_set(7, (uint32)isr7 );
    idt_set(8, (uint32)isr8 );
    idt_set(9, (uint32)isr9 );
    idt_set(10, (uint32)isr10);
    idt_set(11, (uint32)isr11);
    idt_set(12, (uint32)isr12);
    idt_set(13, (uint32)isr13);
    idt_set(14, (uint32)isr14);
    idt_set(15, (uint32)isr15);
    idt_set(16, (uint32)isr16);
    idt_set(17, (uint32)isr17);
    idt_set(18, (uint32)isr18);
    idt_set(19, (uint32)isr19);
    idt_set(20, (uint32)isr20);
    idt_set(21, (uint32)isr21);
    idt_set(22, (uint32)isr22);
    idt_set(23, (uint32)isr23);
    idt_set(24, (uint32)isr24);
    idt_set(25, (uint32)isr25);
    idt_set(26, (uint32)isr26);
    idt_set(27, (uint32)isr27);
    idt_set(28, (uint32)isr28);
    idt_set(29, (uint32)isr29);
    idt_set(30, (uint32)isr30);
    idt_set(31, (uint32)isr31);


    idt_set(32, (uint32)irq0);
    idt_set(33, (uint32)irq1);
    idt_set(34, (uint32)irq2);
    idt_set(35, (uint32)irq3);
    idt_set(36, (uint32)irq4);
    idt_set(37, (uint32)irq5);
    idt_set(38, (uint32)irq6);
    idt_set(39, (uint32)irq7);
    idt_set(40, (uint32)irq8);
    idt_set(41, (uint32)irq9);
    idt_set(42, (uint32)irq10);
    idt_set(43, (uint32)irq11);
    idt_set(44, (uint32)irq12);
    idt_set(45, (uint32)irq13);
    idt_set(46, (uint32)irq14);
    idt_set(47, (uint32)irq15);
		
	load_idt((uint32)&idtr_descriptor);
	// load_idt((uint32)&idtr_descriptor);
	// enable_interrupts();

	// load_idt(&idtr_descriptor);
	// pic_map();

}