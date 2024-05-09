#include "heap.h"
#include "config.h"
#include "libk.h"

struct heap_table heap_table;

void kheap_init()
{
    heap_table.entries = (uint8 *)(HEAP_TABLE_ADDRESS);
    heap_table.total = HEAP_TOTAL_ENTRIES;

    void* end = (void*)(HEAP_ADDRESS + HEAP_SIZE_BYTES);
    int res = heap_create((void *)(HEAP_ADDRESS), end, &heap_table);
    if (res < 0)
    {
        kprintf("Failed to create heap\n");
    }

}

void* mmap(size_t size)
{
	return heap_malloc(&heap_table, size);
}