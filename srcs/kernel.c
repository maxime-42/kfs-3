#include "kernel.h"
#include "idt.h"
#include "gdt.h"
#include "keyboard.h"
#include "interrupts.h"
#include "commands.h"
#include "shell.h"
#include "heap.h"
#include "paging.h"
#include "config.h"
#include "malloc.h"
extern void test_syscalls();

void	set_string()
{

	void *ptr = (void *)STRING_ADDRESS;
	char str[] = "hello world lenox-kay";    	
	kmemcpy(ptr, str, sizeof(str));


}

// static struct paging_4gb_chunk* kernel_chunk = 0;


// extern void enable_paging();

// __attribute__ ((section ("prekernel_entry"))) void prekernel_main(void) 
// {
//     // Physical memory map entry from Bios Int 15h EAX E820h
//     typedef struct SMAP_entry {
//         uint64 base_address;
//         uint64 length;
//         uint32 type;
//         uint32 acpi;
//     } __attribute__ ((packed)) SMAP_entry_t;

//     uint32 num_SMAP_entries; 
//     uint32 total_memory; 
//     SMAP_entry_t *SMAP_entry;

//     // Set up physical memory manager
//     num_SMAP_entries = *(uint32 *)SMAP_NUMBER_ADDRESS;        
//     SMAP_entry       = (SMAP_entry_t *)SMAP_ENTRIES_ADDRESS;   
//     SMAP_entry += num_SMAP_entries - 1;

//     total_memory = SMAP_entry->base_address + SMAP_entry->length - 1;

//     // Initialize physical memory manager to all available memory, put it at some location
//     // All memory will be set as used/reserved by default
//     initialize_memory_manager(MEMMAP_AREA, total_memory);

//     // Initialize memory regions for the available memory regions in the SMAP (type = 1)
//     SMAP_entry = (SMAP_entry_t *)SMAP_ENTRIES_ADDRESS; 
//     for (uint32 i = 0; i < num_SMAP_entries; i++) {
//         if (SMAP_entry->type == 1)
//             initialize_memory_region(SMAP_entry->base_address, SMAP_entry->length);

//         SMAP_entry++;
//     }

// }
extern uint32 end;

uint32 placement_address = (uint32)&end;//uint32 end Defined in kernel/arch/i386/linker.ld

void * test_alloc(size_t size){
    return kmalloc(size);
}


void	kmain()
{
	// prekernel_main();
	terminal_initialize();
	// printk("=============12321331113566846=====");
	init_gdt();

	init_idt();
	  initialize_memory_region(placement_address, 0x1002000);
	initialize_virtual_memory_manager();// test_div();
	// printk("hello world\n");
	// set_string();

	
	init_keyboard_buffer();
	init_keyboard();

	init_syscalls();
	// test_syscalls();
  
	// shell();
	// prekernel_main();

	kheap_init();
	testeur();
	// printk("====>>> start test heap\n");
	// void * ptr1;
	// for (size_t i = 0; i < 4; i++)
	// {
	// 	ptr1 = kmalloc(2);
	// 	printk("======>>>> ptr1 : %p\n", ptr1);
	// }
	
	// printk("======>>>>ptr1 : %p\n", ptr1);
	// // // void * ptr3 = kmalloc(20);
	// // // void * ptr4 = kmalloc(30);
	// // // void * ptr5 = kmalloc(40);
	// printk("======>>>>ptr2 : %p\n", ptr2);
	// char * ptr2 = test_alloc(15);
	// for(int i = 0; i < 5 ; i++) {
	// 	ptr2[i] = i+48;
	// }
	// // ptr2[5] = '\0';
  // printk("==============>>> ptr2 = %s \n", ptr2);
	// kfree(ptr2);
  // printk(" after kfree ==============>>> ptr2 = %s \n", ptr2);
	// void * tmp = kmalloc(15);
  // void* a = malloc(9);
  // (void)a;

	// printk("======>>>>tmp : %p\n", tmp);

	// (void) ptr2;
	// (void) ptr3;
	// (void) ptr4;
	// (void) ptr5;
	// int addr = 0X000007C0 - 32;
	// GET_ESP(addr);
	// kdump(&addr, 20);
	// Setup paging
    // char* ptr = kzalloc(4096);

    // // Enable paging
    //  enable_paging();
	
		// char * ptr3 = (char *) 0x1000;
		// ptr3[0] = 'A';
		// ptr3[1] = 'B';
		// printk("==>> %s", 0x1000);
    // Enable paging

}
