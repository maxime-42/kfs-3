#include "io.h"
#include "interrupts.h"
#include "config.h"



/************************************
 * @brief: this function maps the Programmable Interrupt Controller (PIC)
 * 
 * @param: none
 * 
 * @return: none
 * 
 * This function configures the Programmable Interrupt Controller (PIC) 
 * to set up interrupt handling. The PIC is responsible for managing 
 * hardware interrupts on the system.
 *
 * The function follows the initialization sequence for the PIC as follows:
 * 1. Initialize master PIC (PIC1) and slave PIC (PIC2) by sending the 
 *    initialization control word (ICW) 1.
 * 2. Set interrupt vector offsets for both PICs.
 * 3. Inform the master PIC about the cascade identity.
 * 4. Inform the slave PIC about its cascade identity.
 * 5. Configure the PICs to operate in 8086/88 mode.
 * 6. Mask all interrupts.
 * 7. Enable interrupts.
*************************************/
void pic_map(void)
{
	// Send ICW1 (Initialization Control Word 1) to both PICs
	outb(0x20, 0x11); // Initialize master PIC (PIC1)
	outb(0xA0, 0x11); // Initialize slave PIC (PIC2)

	// Send ICW2 (Initialization Control Word 2) to set interrupt vector offsets
	outb(0x21, 0x20); // Set master PIC (PIC1) offset to 0x20
	outb(0xA1, 0x28); // Set slave PIC (PIC2) offset to 0x28

	// Send ICW3 (Initialization Control Word 3) to inform about the cascade identity
	outb(0x21, 0x04); // Inform master PIC (PIC1) about the cascade identity of slave PIC (IRQ2)
	outb(0xA1, 0x02); // Inform slave PIC (PIC2) about its cascade identity

	// Send ICW4 (Initialization Control Word 4) to configure PICs to operate in 8086/88 mode
	outb(0x21, 0x01); // Configure master PIC (PIC1) to operate in 8086/88 mode
	outb(0xA1, 0x01); // Configure slave PIC (PIC2) to operate in 8086/88 mode

	// Mask all interrupts
	outb(0x21, 0x0); // Mask all interrupts for master PIC (PIC1)
	outb(0xA1, 0x0); // Mask all interrupts for slave PIC (PIC2)

	// Enable interrupts
	enable_interrupts();
}
