/*
 *  physical_memory_manager.h: Provide functions to allocate/free or handle blocks of physical
 *      memory
 */
#include "config.h"
#include "paging.h"
#include "libk.h"
#include "heap.h"

#define BLOCK_SIZE      4096     // Size of 1 block of memory, 4KB
#define BLOCKS_PER_BYTE 8        // Using a bitmap, each byte will hold 8 bits/blocks

typedef struct s_info_addr
{
	uint32 addr;
	uint32 size;
}			t_info_addr;

// Global variables
static uint32 *memory_map = 0;
static uint32 max_blocks  = 0;
static uint32 used_blocks = 0;
static t_info_addr info_addr[1023];
static	uint32 count_addr = 0;
// Sets a block/bit in the memory map (mark block as used)
void set_block(const uint32 bit)
{
    // Divide bit by 32 to get 32bit "chunk" of memory containing bit to be set;
    // Shift 1 by remainder of bit divided by 32 to get bit to set within the
    //   32 bit chunk
    // OR to set that bit
    memory_map[bit/32] |= (1 << (bit % 32));
}

// Unsets a block/bit in the memory map (mark block as free)
void unset_block(const uint32 bit)
{
    // Divide bit by 32 to get 32bit "chunk" of memory containing bit to be set;
    // Shift 1 by remainder of bit divided by 32 to get bit to set within the
    //   32 bit chunk
    // AND with the inverse of those bits to clear the bit to 0
    memory_map[bit/32] &= ~(1 << (bit % 32));
}

// Test if a block/bit in the memory map is set/used
//uint8_t test_block(const uint32 bit)
//{
    // Divide bit by 32 to get 32bit "chunk" of memory containing bit to be set;
    // Shift 1 by remainder of bit divided by 32 to get bit within the 32bit chunk;
    // AND and return that bit (will be 1 or 0)
 //   return memory_map[bit/32] & (1 << (bit % 32));
//}

// Find the first free blocks of memory for a given size
int32 find_first_free_blocks(const uint32 num_blocks)
{
    if (num_blocks == 0) return -1; // Can't return no memory, error

    // Test 32 blocks at a time
    for (uint32 i = 0; i < max_blocks / 32;  i++) {
        if (memory_map[i] != 0xFFFFFFFF) {
            // At least 1 bit is not set within this 32bit chunk of memory,
            //   find that bit by testing each bit
            for (int32 j = 0; j < 32; j++) {
                int32 bit = 1 << j;

                // If bit is unset/0, found start of a free region of memory
                if (!(memory_map[i] & bit)) {
                    for (uint32 count = 0, free_blocks = 0; count < num_blocks; count++) {
                        if ((j+count > 31) && (i+1 <= max_blocks / 32)) {
                            if (!(memory_map[i+1] & (1 << ((j+count)-32))))
                                free_blocks++;
                        } else {
                            if (!(memory_map[i] & (1 << (j+count))))
                                free_blocks++;
                        }

                        if (free_blocks == num_blocks) // Found enough free space
                            return i*32 + j;
                    }
                }
            }
        }
    }

    return -1;  // No free region of memory large enough
}

// Initialize memory manager, given an address and size to put the memory map
void initialize_memory_manager(const uint32 start_address, const uint32 size)
{
    memory_map = (uint32 *)start_address;
    max_blocks  = size / BLOCK_SIZE;
    used_blocks = max_blocks;       // To start off, every block will be "used/reserved"

    // By default, set all memory in use (used blocks/bits = 1, every block is set)
    // Each byte of memory map holds 8 bits/blocks
    kmemset(info_addr, 0, 1023);
    kmemset(memory_map, 0xFF, max_blocks / BLOCKS_PER_BYTE);
}

// Initialize region of memory (sets blocks as free/available)
void initialize_memory_region(const uint32 base_address, const uint32 size)
{
    int32 align      = base_address / BLOCK_SIZE;  // Convert memory address to blocks
    int32 num_blocks = size / BLOCK_SIZE;          // Convert size to blocks

    for (; num_blocks > 0; num_blocks--) {
        unset_block(align++);
        used_blocks--;
    }

    // Always going to set the 1st block, ensure we can't alloc 0, and can't overwrite
    //   interrupt tables IDT/IVT, Bios data areas, etc.
    set_block(0);
}

// De-initialize region of memory (sets blocks as used/reserved)
// void deinitialize_memory_region(const uint32 base_address, const uint32 size)
// {
//     int32 align      = base_address / BLOCK_SIZE;  // Convert memory address to blocks
//     int32 num_blocks = size / BLOCK_SIZE;          // Convert size to blocks

//     for (; num_blocks > 0; num_blocks--) {
//         set_block(align++);
//         used_blocks++;
//     }
// }


// void	add_info(uint32 addr, uint32 size)
// {
// 	info_addr[count_addr].addr = addr;
// 	info_addr[count_addr].size = size;
// 	count_addr++;
// }

// static void	remove_info(uint32 addr)
// {
// 	for (uint32 i = 0; i < count_addr; i++)
// 	{
// 		if (info_addr[i].addr == addr)
// 		{
// 			info_addr[i].addr = 0;
// 			info_addr[i].addr = 0;
// 			count_addr--;
// 			return;
// 		}
// 	}
	
// }

uint32	get_size_physical(uint32 addr)
{
	for (uint32 i = 0; i < count_addr; i++)
	{
		if (info_addr[i].addr == addr)
		{
			return info_addr[i].addr;
		}
	}
	return 0;
}

// Allocate blocks of memory
uint32 *allocate_blocks(const uint32 num_blocks)
{
    // If # of free blocks left is not enough, we can't allocate any more, return
    if ((max_blocks - used_blocks) <= num_blocks) return 0;   

    int32 starting_block = find_first_free_blocks(num_blocks);
    if (starting_block == -1) return 0;     // Couldn't find that many blocks in a row to allocate

    // Found free blocks, set them as used
    for (uint32 i = 0; i < num_blocks; i++)
        set_block(starting_block + i);

    used_blocks += num_blocks;  // Blocks are now used/reserved, increase count

    // Convert blocks to bytes to get start of actual RAM that is now allocated
    uint32 address = starting_block * BLOCK_SIZE; 
	if (kmalloc(8) == 0)
	{
		printk("=== Not Null\n");

	}
	else
	{
		printk("==== Null\n");
	}
    return (uint32 *)address;  // Physical memory location of allocated blocks
}

// Free blocks memory
void free_blocks(const uint32 *address, const uint32 num_blocks)
{
    int32 starting_block = (uint32)address / BLOCK_SIZE;   // Convert address to blocks 

    for (uint32 i = 0; i < num_blocks; i++) 
        unset_block(starting_block + i);    // Unset bits/blocks in memory map, to free

    used_blocks -= num_blocks;  // Decrease used block count
}

