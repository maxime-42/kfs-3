#include "heap.h"
// #include "libk.h"


// Function to validate the alignment of a given pointer
// Returns 1 if the pointer is aligned, 0 otherwise
static uint32 heap_validate_alignment(void* ptr)
{
    return ((size_t)ptr % HEAP_BLOCK_SIZE) == 0;
}

// Function to create a new heap instance
// Returns 1 on success, ERROR on failure
int heap_create(void* start, void* end, t_heap_table* heap_instance)
{
    int res = 0;

    if (!heap_validate_alignment(start) || !heap_validate_alignment(end))
    {
        return ERROR;
    }


    // res = heap_validate_table(ptr, end, table);
    // if (res < 0)
    // {
    //     goto out;
    // }

    size_t table_size = sizeof(uint8) * heap_instance->total;
    memset(heap_instance->table, HEAP_BLOCK_TABLE_ENTRY_FREE, table_size);
    (void) res;
    return 1;
}

// Function to get the size of a memory allocation
// Returns the size of the memory allocation, aligned to the nearest
// multiple of HEAP_BLOCK_SIZE
static uint32 get_size_of_mem_alloc(uint32 val)
{
    if ((val % HEAP_BLOCK_SIZE) == 0)
    {
        return val;
    }

    val = (val - ( val % HEAP_BLOCK_SIZE));
    val += HEAP_BLOCK_SIZE;
    return val;
}


// Function to get the type of a heap table entry
// Returns the type of the entry as an integer
static int heap_get_entry_type(uint8 entry)
{
    return entry & 0x0f;
}


// Function to get the starting block of a heap instance
// Returns the index of the starting block, or ERROR on failure
int heap_get_start_block(t_heap_table * heap_instance, uint32 total_blocks)
{
    // struct t_heap_table* table = heap_instance->table;
    int bc = 0;
    int bs = -1;
    // (int) total_blocks;
    for (size_t i = 0; i < heap_instance->total; i++)
    {
        if (heap_get_entry_type(heap_instance->table[i]) != HEAP_BLOCK_TABLE_ENTRY_FREE)
        {
            bc = 0;
            bs = -1;
            continue;
        }

        // If this is the first block
        if (bs == -1)
        {
            bs = i;
        }
        bc++;
        if (bc == (int)total_blocks)
        {
            break;
        }
    }

    if (bs == -1)
    {
        return ERROR;
    }
    
    return bs;
}


// Function to convert a heap block index to an address
// Returns a pointer to the start of the block
void* heap_block_to_address(t_heap_table * heap_instance, int block)
{
    return heap_instance->table + (block * HEAP_BLOCK_SIZE);
}

// Function to allocate a contiguous block of memory from the heap
// Returns a pointer to the start of the allocated block, or NULL on failure
static void* heap_malloc_blocks(t_heap_table * heap_instance, uint32 total_blocks)
{
    void* address = 0;

    int start_block = heap_get_start_block(heap_instance, total_blocks);
    if (start_block < 0)
    {
        return NULL;
    }

    address = heap_block_to_address(heap_instance, start_block);

    // Mark the blocks as taken
    // heap_mark_blocks_taken(heap_instance, start_block, total_blocks);
    return address;
}

// Function to allocate a block of memory from the heap
// Returns a pointer to the start of the allocated block, or NULL on failure
void* heap_malloc(t_heap_table * heap_instance, size_t size)
{
    size_t aligned_size = get_size_of_mem_alloc(size);
    uint32 nbr_blocks = aligned_size / HEAP_BLOCK_SIZE;
    return heap_malloc_blocks(heap_instance, nbr_blocks);
}