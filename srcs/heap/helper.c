#include "heap.h"
#include "libk.h"
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
    kmemset(heap_instance->table, HEAP_BLOCK_TABLE_ENTRY_FREE, table_size);
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
		// printk("i = %d\n");
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
	printk("block start: %d\n", bs);
	printk("block counter: %d\n", bc);
    return bs;
}


// Function to convert a heap block index to an address
// Returns a pointer to the start of the block
void* heap_block_to_address(t_heap_table * heap_instance, int block)
{
    return heap_instance->table + (block * HEAP_BLOCK_SIZE);
}


static void heap_mark_blocks_taken(t_heap_table* heap_instance, int start_block, int total_blocks)
{
    int end_block = (start_block + total_blocks)-1;
    
    uint8 entry = HEAP_BLOCK_TABLE_ENTRY_TAKEN | HEAP_BLOCK_IS_FIRST;
    if (total_blocks > 1)
    {
        entry |= HEAP_BLOCK_HAS_NEXT;
    }

    for (int i = start_block; i <= end_block; i++)
    {
        entry = HEAP_BLOCK_TABLE_ENTRY_TAKEN;
        heap_instance->table[i] = entry;
        if (i != end_block -1)
        {
            entry |= HEAP_BLOCK_HAS_NEXT;
        }
    }
}

// Function to allocate a contiguous block of memory from the heap
// Returns a pointer to the start of the allocated block, or NULL on failure
static void* heap_malloc_blocks(t_heap_table * heap_instance, uint32 total_blocks)
{
    void* address = 0;

    int start_block = heap_get_start_block(heap_instance, total_blocks);
    // printk("start block : %d\n", start_block);
	if (start_block < 0)
    {
        return NULL;
    }

    address = heap_block_to_address(heap_instance, start_block);

    // Mark the blocks as taken
    heap_mark_blocks_taken(heap_instance, start_block, total_blocks);
    return address;
}


/*
    le probleme c'est que starting block n'est pas bon, on obtiens une valeur aleatoire
*/
void heap_mark_blocks_free(t_heap_table * heap_instance, int starting_block)
{
    // t_8 * table = heap_insheap_instancee->table;
    for (int i = starting_block; i < (int)heap_instance->total; i++)
    {
        uint8 entry = heap_instance->table[i];
        printk("the block1  ===>>> %d\n", heap_instance->table[i]);
     
        heap_instance->table[i] = HEAP_BLOCK_TABLE_ENTRY_FREE;
        printk("the block2  ===>>> %d", heap_instance->table[i]);
        if (!(entry & HEAP_BLOCK_HAS_NEXT))
        {
            break;
        }
    }
}  
    
/*
 l'origine du probleme est ici, la valeur retourner n'est pas la bonne
 cette fonction est sensée nous retourner l'index du block où se trouve notre adresse
 mais il retourne une valeur aleatoire
*/
int heap_address_to_block( t_heap_table * heap_instance, void* address_to_find)
{
	void *start = (void *)HEAP_ADDRESS;
	// heap_instance->table + (block * HEAP_BLOCK_SIZE);
    // return ((int)(address_to_find -  start) / HEAP_BLOCK_SIZE);
    // return ((int)(address_to_find -  start) / HEAP_BLOCK_SIZE);
	return  (address_to_find - (void *)heap_instance->table) / HEAP_BLOCK_SIZE;
	
}

void heap_free(t_heap_table * heap_instance, void* ptr)
{
    int starting_block = heap_address_to_block(heap_instance, ptr);
    printk("starting block =====>>> %d", starting_block);
    heap_mark_blocks_free(heap_instance, starting_block);
}

// Function to allocate a block of memory from the heap
// Returns a pointer to the start of the allocated block, or NULL on failure
void* heap_malloc(t_heap_table * heap_instance, size_t size)
{
    size_t nbr_bytes = get_size_of_mem_alloc(size);
	printk("nbr_bytes = %d\n", nbr_bytes);
    uint32 nbr_blocks = nbr_bytes / HEAP_BLOCK_SIZE;
	printk("nbr_blocks = %d\n", nbr_blocks);
	void *address = heap_malloc_blocks(heap_instance, nbr_blocks);
	printk("address block: %d\n", (uint32 )address);
	printk("____________________________\n");
    return address;
}

// #include <string.h>

void* kzalloc(size_t size)
{
    void* ptr = kmalloc(size);
    if (!ptr)
        return 0;

    // kmemset(ptr, 0x00, size);
    return ptr;
}