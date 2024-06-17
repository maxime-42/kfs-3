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
            kfree(zone);
            // munmap(zone, zone->size);
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
static void free_block(t_meta_block *meta_block, t_zone_type zone_type)
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
            // munmap(zone, zone->size);
            printk("111>>>> \n");
            printk("zone = %p\n", zone);
            kmemset(zone, 0, zone->size);
            kfree(zone);
            // kfreeSize(zone, zone->size);
            printk("after kfree zone = %p\n", zone);

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
    if ((meta_block = search_in_zone(ptr, TINY_ZONE)))
        free_block(meta_block, TINY_ZONE);
    else if ((meta_block = search_in_zone(ptr, SMALL_ZONE)))
        free_block(meta_block, SMALL_ZONE);
    else
        free_large_block(ptr);
}

void free(void *ptr)
{
    //pthread_mutex_lock(&g_mutex);
    ft_free(ptr);
    //pthread_mutex_unlock(&g_mutex);
}