#include "kernel.h"
#include "idt.h"
#include "gdt.h"
#include "keyboard.h"
#include "interrupts.h"
#include "commands.h"
#include "shell.h"

extern void test_syscalls();

void	set_string()
{

	void *ptr = (void *)STRING_ADDRESS;
	char str[] = "hello world lenox-kay";    	
	kmemcpy(ptr, str, sizeof(str));


}
void	kmain()
{

	terminal_initialize();

	init_gdt();


	init_idt();	
	// test_div();
	// printk("hello world\n");
	set_string();

	
	init_keyboard_buffer();
	init_keyboard();
	// qemu_shutdown();
	// uint16 n = 12/0;

	init_syscalls();
	// test_syscalls();

	shell();
	// int addr = 0X000007C0 - 32;
	// GET_ESP(addr);
	// kdump(&addr, 20);

}
