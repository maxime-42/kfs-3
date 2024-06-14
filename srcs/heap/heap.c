#include "heap.h"
#include "config.h"
#include "libk.h"
#include "paging.h"
// #include "config.h"
// #include "libk.h"
// #include "../../include/heap.h"
static t_heap_table heap_instance;
// #include "malloc.h"

/*
 * Function: kheap_init()
 * ----------------------
 * Initializes the kernel heap.
 * Sets the heap_instance table to the HEAP_TABLE_ADDRESS and total to HEAP_TOTAL_ENTRIES.
 * Attempts to create a heap at the specified address and size, and stores the result in res.
 * If the heap creation fails, it prints an error message.
 */
void kheap_init()
{
    heap_instance.table = (uint8 *)(HEAP_TABLE_ADDRESS);
    heap_instance.total = HEAP_TOTAL_ENTRIES;
	heap_instance.table = (unsigned char *)allocate_blocks(HEAP_TOTAL_ENTRIES);

    void* end = (void*)(HEAP_ADDRESS + HEAP_SIZE_BYTES);
    int res = heap_create((void *)(HEAP_ADDRESS), end, &heap_instance);
    if (res < 0)
    {
        printk("Failed to create heap\n");
    }

}



/*
 * Function: kmalloc()
 * ------------------
 * Allocates memory of the specified size from the kernel heap.
 * Returns a pointer to the allocated memory.
 */
void* kmalloc(size_t size)
{
	return heap_malloc(&heap_instance, size);
}


void kfree(void* ptr)
{
    heap_free(&heap_instance, ptr);
}

void kfreeSize(void* ptr, size_t size)
{
    heap_free(&heap_instance, ptr);
    
}