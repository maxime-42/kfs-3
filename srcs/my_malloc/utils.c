#include "malloc.h"
// extern t_memory_zones          g_zones;

inline size_t  get_alligned_size(size_t size)
{
    return (ALLIGN(size) + sizeof(t_ftr_block));
}

void set_block_metadata(t_meta_block *memory_block, t_bool is_free, size_t size)
{
    *memory_block = (t_meta_block){.is_free = is_free, .size = size};
    *GET_BLOCK_FOOTER(memory_block) = size;
}

t_meta_block *search_in_zone(void *ptr, t_zone_type zone_type)
{
    t_meta_block *curr_block;
    t_vm_page      *zone;

    zone = GET_ZONE_BY_TYPE(zone_type);
    for (t_vm_page *zone_head = zone; zone_head; zone_head = zone_head->next)
    {
        curr_block = GET_ZONE_FIRST_META_BLOCK(zone_head);
        while (IS_ADDR_IN_ZONE(zone_head, curr_block))
        {
            if(GET_VM_PAGE(curr_block) == ptr)
                return (curr_block);
            curr_block = GET_NEXT_META_BLOCK(curr_block, curr_block->size);
        }
    }
    return (NULL);
}

t_vm_page *search_in_large_zone(void *ptr)
{
    for (t_vm_page *zone_head = g_zones.large; zone_head; zone_head = zone_head->next)
        if((void *)GET_L_MEMORY_BLOCK(zone_head) == ptr)
            return (zone_head);
    return (NULL);
}

t_bool is_allocated(void *ptr)
{
    t_meta_block *block;

    if ((block = search_in_zone(ptr, TINY_ZONE)) || (block = search_in_zone(ptr, SMALL_ZONE)))
        return (block->is_free == false);
    if (search_in_large_zone(ptr))
        return (true);
    return (false);
}