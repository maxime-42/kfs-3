#include "interrupts.h"
#include "libk.h"
#include "config.h"
#include "libk.h"

//https://wiki.osdev.org/Exceptions


t_interrupt_handler  handlers[MAX_HANDLERS];

// Initializes the handlers array with zeroes.
void init_handlers(void)
{
    // handlers is the array being initialized.
    // Its size is defined by the sizeof(handlers) function.
    kmemset(&handlers, 0, sizeof(handlers) );

    // kmemset is a kernel memory set function, which sets
    // a block of memory to a specified value.
    // In this case, it sets the handlers array to zeroes.
}

// Function to add a handler to the interrupt vector table
// n: The index of the interrupt vector table where the handler will be added
//  handler: The interrupt handler function to be added
int add_handler(uint32 n, t_interrupt_handler handler)
{
    // Check if the index is within the bounds of the interrupt vector table
    if (n >= 256) {
        // If the index is out of bounds, do nothing and return
        return 1;
    }
    // Add the handler to the specified index of the interrupt vector table
    handlers[n] = handler;
	return  0;
}



t_interrupt_handler get_interrupt_handler(uint32 n)
{
	// ft_putstr("hello");
    // Check if the handler index is within the valid range
    if  (n < MAX_HANDLERS)
        // If it is, return the corresponding handler
        return handlers[n];
    // If the index is out of range, return NULL
    else
        return NULL;
}