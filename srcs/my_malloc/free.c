#include "malloc.h"
/**
 * Merge two adjacent free meta blocks into one if they are free.
 * 
 * @param first_block The first meta block to merge.
 * @param second_block The second meta block to merge.
 */
static void merge_meta_blocks(t_meta_block *first_block, t_meta_block *second_block)
{
    if (first_block->is_free == false || second_block->is_free == false)
        return ;
    first_block->size += second_block->size + sizeof(t_meta_block);
    *GET_BLOCK_FOOTER(first_block) = first_block->size;
}

/**
 * Free a large block of memory.
 * 
 * @param ptr The pointer to the memory block to free.
 */
static void free_large_block(void *ptr)
{
    t_vm_page *zone;
    t_vm_page **zone_tail;

    zone_tail = GET_ZONE_TAIL_ADDR(LARGE_ZONE);
    kmemset(zone, 0, zone->size);

    for (t_vm_page **curr_zone = GET_ZONE_ADDR(LARGE_ZONE); *curr_zone; curr_zone = &(*curr_zone)->next)
    {
        if((void *)GET_L_MEMORY_BLOCK(*curr_zone) == ptr)
        {
            zone = *curr_zone;
            if (GET_ZONE_ADDR(LARGE_ZONE) == curr_zone)
            {
                *curr_zone = (*curr_zone)->next;
                *zone_tail = *curr_zone;
            }
            else if (*zone_tail == zone)
            {
                *zone_tail = (*curr_zone)->prev;
                (*zone_tail)->next = NULL;
            }
            else
            {
                (*curr_zone)->prev->next = (*curr_zone)->next;
                zone->next->prev = zone->prev;
            }
            kmemset(zone, 0, zone->size);
            zone->size = 0;
            kfree(ptr);
            // kfree(zone);
            break;
        }
    }
}

/**
 * Free a block of memory in a specific zone.
 * If the zone if now empty i return it to the kernel
 * 
 * @param meta_block The header of the block to free.
 * @param zone_type The type of zone the block belongs to.
 */
static void free_block(t_meta_block *meta_block, t_zone_type zone_type, void *ptr)
{
    t_vm_page *zone;
    t_vm_page **zone_tail;
    zone_tail = GET_ZONE_TAIL_ADDR(zone_type);
    meta_block->is_free = true;

    for (t_vm_page **curr_zone = GET_ZONE_ADDR(zone_type); *curr_zone; curr_zone = &(*curr_zone)->next)
    {

        if (IS_ADDR_IN_ZONE((*curr_zone), meta_block))
        {
            if (IS_ADDR_IN_ZONE((*curr_zone), GET_NEXT_META_BLOCK(meta_block, meta_block->size)))
                merge_meta_blocks(meta_block, GET_NEXT_META_BLOCK(meta_block, meta_block->size));
            if (IS_ADDR_IN_ZONE((*curr_zone), GET_PREV_HEADER(meta_block)))
                merge_meta_blocks(GET_PREV_HEADER(meta_block), meta_block);
        }
        //if the current meta block is egal to the first meta block that mean my zone is empty
        if (FIRST_BLOCK_SIZE(zone_type) == GET_ZONE_FIRST_META_BLOCK(*curr_zone)->size)
        {
            zone = *curr_zone;
            if (GET_ZONE_ADDR(zone_type) == curr_zone)
            {
                if (zone == NULL){
                    break;
                }
                // *zone_tail = (*curr_zone)->next; //easy way
                *curr_zone = (*curr_zone)->next;
                *zone_tail = *curr_zone;
            }
            else if (*zone_tail == zone)
            {
                *zone_tail = (*curr_zone)->prev;
                (*curr_zone)->prev->next = NULL;
                // (*zone_tail)->next = NULL;
            }
            else
            {
                (*curr_zone)->prev->next = (*curr_zone)->next;
                zone->next->prev = zone->prev;
            }
            kmemset(ptr, 0, zone->size);
            zone->size = 0;
            kfree(ptr);
            break;
        }
    }
}

/**
 * Free a block of memory.
 * 
 * @param ptr The pointer to the memory block to free.
 */
void ft_free(void *ptr)
{
    t_meta_block *meta_block;

    if (ptr == NULL)
        return ;
    if ((meta_block = search_in_zone(ptr, TINY_ZONE))){
        free_block(meta_block, TINY_ZONE, ptr);
    }
    else if ((meta_block = search_in_zone(ptr, SMALL_ZONE))){
        free_block(meta_block, SMALL_ZONE, ptr);
    }
    else{
        free_large_block(ptr);
    }
}

void vfree(void *ptr)
{
    ft_free(ptr);
    kfree(ptr);
}


uint64_t ksize(void * ptr)
{
    t_meta_block *meta_block;

    if (ptr == NULL)
        return 0;
    if (search_in_zone(ptr, TINY_ZONE))
        meta_block = search_in_zone(ptr, TINY_ZONE);
    else if (search_in_zone(ptr, SMALL_ZONE))
        meta_block = search_in_zone(ptr, SMALL_ZONE);
    else{
        t_vm_page * vm_page = search_in_large_zone(ptr);
        uint64_t size_large = vm_page->size;
        if ((size_large % HEAP_BLOCK_SIZE) == 0)
            return (uint64_t)HEAP_BLOCK_SIZE;
        size_large = (size_large - ( size_large % HEAP_BLOCK_SIZE));
        size_large += HEAP_BLOCK_SIZE;
        return size_large;
    }

    uint64_t size = meta_block->size;
    if ((size % HEAP_BLOCK_SIZE) == 0)
    {
        return (uint64_t)HEAP_BLOCK_SIZE;
    }

    size = (size - ( size % HEAP_BLOCK_SIZE));
    size += HEAP_BLOCK_SIZE;
    return size;
}


uint64_t vsize(void * ptr)
{
    t_meta_block *meta_block;
    t_vm_page *vm_page;

    if (ptr == NULL)
        return 0;
    if (search_in_zone(ptr, TINY_ZONE)){
        meta_block = search_in_zone(ptr, TINY_ZONE);
    }
    else if (search_in_zone(ptr, SMALL_ZONE)){
        meta_block = search_in_zone(ptr, SMALL_ZONE);
    }
    else{
        vm_page = search_in_large_zone(ptr);
        return vm_page->size;
    }

    uint64_t size = meta_block->size;
    return (size - sizeof(t_meta_block));
}


int new_get_size(void * ptr){
    t_meta_block *meta_block;
    t_vm_page *vm_page;

    if (ptr == NULL)
        return 0;
    if (search_in_zone(ptr, TINY_ZONE)){
        meta_block = search_in_zone(ptr, TINY_ZONE);
    }
    else if (search_in_zone(ptr, SMALL_ZONE)){
        meta_block = search_in_zone(ptr, SMALL_ZONE);
    }
    else{
        vm_page = search_in_large_zone(ptr);
        return vm_page->size/4096;
    }

    uint64_t size = meta_block->size;
    return (size - sizeof(t_meta_block)) / 4096;
}