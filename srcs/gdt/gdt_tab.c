#include "gdt.h"
#include "libk.h"
/*


*/

t_gdt_entry	gdt_entries[GDT_ENTRIES];
t_gdt_ptr	*gdt_ptr = (t_gdt_ptr *)GDT_ADDRESS;

static void create_descriptor(int num, uint32 base, uint32 limit, uint8 access, uint8 flags)
{
	gdt_entries[num].limit_low = (limit & 0xFFFF);
	gdt_entries[num].base_low = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].access = access;
	gdt_entries[num].attributes = (limit >> 16) & 0x0F;
	gdt_entries[num].attributes |= ((flags << 4) & 0xF0);
	gdt_entries[num].base_high = (base >> 24) & 0xFF;
}

void	init_gdt()
{
	gdt_ptr->limit = (sizeof(t_gdt_entry) * GDT_ENTRIES) - 1;
	gdt_ptr->base = ((uint32)(&gdt_entries));

	create_descriptor(0, 0, 0, 0, 0);				// null
	create_descriptor(1, FLAT_MEMORY, 0xFFFFF, (uint8)(GDT_CODE_PL0),  FLAG_D_32);	// kernel code (kernel binary)
	create_descriptor(2, FLAT_MEMORY, 0xFFFFF, (uint8)(GDT_DATA_PL0),  FLAG_D_32);	// kernel data (kernel heap)
	create_descriptor(3, FLAT_MEMORY, 0xFFFFF, (uint8)(GDT_STACK_PL0), FLAG_D_32);	// kernel stack
	create_descriptor(4, FLAT_MEMORY, 0xBFFFF, (uint8)(GDT_CODE_PL3),  FLAG_D_32);	// user code (user-executed binaries)
	create_descriptor(5, FLAT_MEMORY, 0xBFFFF, (uint8)(GDT_DATA_PL3),  FLAG_D_32);	// user data (user heap)
	create_descriptor(6, FLAT_MEMORY, 0xBFFFF, (uint8)(GDT_STACK_PL3), FLAG_D_32);	// user stack

	gdt_flush(((uint32)gdt_ptr));
}
