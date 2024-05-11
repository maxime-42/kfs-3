#ifndef _HEAP_H
#define _HEAP_H
#include "config.h"
#include <stddef.h>

#define HEAP_BLOCK_TABLE_ENTRY_TAKEN 0x01
#define HEAP_BLOCK_TABLE_ENTRY_FREE 0x00

#define HEAP_BLOCK_HAS_NEXT 0b10000000
#define HEAP_BLOCK_IS_FIRST  0b01000000
#define HEAP_SIZE_BYTES 104857600
#define HEAP_BLOCK_SIZE 4096
#define HEAP_ADDRESS 0x01000000 
#define HEAP_TABLE_ADDRESS 0x00007E00 
#define HEAP_TOTAL_ENTRIES HEAP_SIZE_BYTES / HEAP_BLOCK_SIZE

typedef struct	s_heap_table
{
    uint8 *	  table;
    size_t		total;
}				t_heap_table;

int heap_create(void* ptr, void* end, t_heap_table* table);
void* kmalloc(size_t size);
void* heap_malloc(t_heap_table* heap, size_t size);
void kheap_init();
void heap_free(t_heap_table * heap_instance, void* ptr);
void kfree(void* ptr);
void* kzalloc(size_t size);

#endif // DEBUG