#ifndef PAGING_H
#define PAGING_H
#include "config.h"
#include "interrupts.h"

void free_page(pt_entry *page);
void *allocate_page(pt_entry *page);
uint32 *allocate_blocks(const uint32 num_blocks);
void free_blocks(const uint32 *address, const uint32 num_blocks);
void deinitialize_memory_region(const uint32 base_address, const uint32 size);
void initialize_memory_region(const uint32 base_address, const uint32 size);
void initialize_memory_manager(const uint32 start_address, const uint32 size);
void set_block(const uint32 bit);
void unset_block(const uint32 bit);
uint32 *allocate_blocks(const uint32 num_blocks);
uint32 initialize_virtual_memory_manager(void);

#endif