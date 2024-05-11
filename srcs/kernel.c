#include "kernel.h"
#include "idt.h"
#include "gdt.h"
#include "keyboard.h"
#include "interrupts.h"
#include "commands.h"
#include "shell.h"
#include "heap.h"
#include "paging.h"

extern void test_syscalls();

void	set_string()
{

	void *ptr = (void *)STRING_ADDRESS;
	char str[] = "hello world lenox-kay";    	
	kmemcpy(ptr, str, sizeof(str));


}

static struct paging_4gb_chunk* kernel_chunk = 0;


extern void enable_paging();


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

	// shell();
	kheap_init();
	// printk("hello");
	void * ptr1 = kmalloc(60);
	printk("ptr1 : %p\n", ptr1);
	void * ptr2 = kmalloc(15);
	// void * ptr3 = kmalloc(20);
	// void * ptr4 = kmalloc(30);
	// void * ptr5 = kmalloc(40);
	kfree(ptr1);
	void * tmp = kmalloc(60);
	printk("tmp : %p\n", tmp);

	(void) ptr2;
	// (void) ptr3;
	// (void) ptr4;
	// (void) ptr5;
	// int addr = 0X000007C0 - 32;
	// GET_ESP(addr);
	// kdump(&addr, 20);
	// Setup paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);

   	// paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));

    // char* ptr = kzalloc(4096);
   	// paging_set(paging_4gb_chunk_get_directory(kernel_chunk), (void*)0x1000, (uint32_t)ptr | PAGING_ACCESS_FROM_ALL | PAGING_IS_PRESENT | PAGING_IS_WRITEABLE);

    // // Enable paging
    // enable_paging();
		// char * ptr3 = (char *) 0x1000;
		// ptr3[0] = 'A';
		// ptr3[1] = 'B';
		// printk("==>> %s", 0x1000);
    // Enable paging

}
