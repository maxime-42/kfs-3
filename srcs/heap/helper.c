#include "heap.h"
#include "libk.h"

static uint32 heap_validate_alignment(void* ptr)
{
    return ((unsigned int)ptr % HEAP_BLOCK_SIZE) == 0;
}

int heap_create(void* start, void* end, struct heap_table* table)
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

    size_t table_size = sizeof(uint8) * table->total;
    kmemset(table->entries, HEAP_BLOCK_TABLE_ENTRY_FREE, table_size);

}