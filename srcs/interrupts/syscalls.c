
#include "interrupts.h"
#include "libk.h"
#include "io.h"
#include "config.h"


void syscall_handler( t_interrupt_frame frame)
{
	printk("syscall number %d called\n", frame.eax);

	// acknowledge(frame.i)

}

void init_syscalls(void)
{
	 int ret = add_handler(0x80, &syscall_handler);

	(void)ret;
}