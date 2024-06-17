#include "malloc.h"

t_memory_zones g_zones = (t_memory_zones){0};
// pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * Allocate a new page of memory using mmap and initialize a new zone or append to an existing zone.
 * 
 * @param zone Pointer to the zone to allocate memory (TINY, SMALL or LARGE)
 * @param zone_tail Pointer to the tail of the zone (the last node of the list of zone)
 * @param size Size of the memory to allocate
 * @return TRUE if allocation was successful, FALSE otherwise
 */
static t_bool mm_get_new_page_from_kernel(t_vm_page **zone, t_vm_page **zone_tail, size_t size)
{
    t_vm_page *page_memory;
    t_vm_page *zone_tail_tmp;

    // page_memory = (t_vm_page *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    page_memory = (t_vm_page *)kmalloc(size);
    printk("page_memory = %p\n", page_memory);
    if (page_memory == MAP_FAILED)
        return (FALSE);
    page_memory->size = size;
    page_memory->next = NULL;
    if (*zone == NULL)
    {
        *zone = page_memory;
        *zone_tail = page_memory;
    }
    else
    {
        (*zone_tail)->next = page_memory;
        zone_tail_tmp = *zone_tail;
        *zone_tail = page_memory;
        (*zone_tail)->prev = zone_tail_tmp;
    }
    return (TRUE);
}

/**
 * Initialize a zone of memory for a given size.
 * 
 * @param size Size of the memory to allocate
 * @return TRUE if initialization was successful, FALSE otherwise
 */
static t_bool init_new_zone(size_t size)
{
    t_bool status;
    if (IS_TINY(size))
    {
        status = mm_get_new_page_from_kernel(&g_zones.tiny, &g_zones.tiny_tail, TINY_ZONE_SIZE);
        if (status == FALSE)
            return (FALSE);
        set_block_metadata(GET_ZONE_FIRST_META_BLOCK(GET_ZONE_TAIL(TINY_ZONE)), TRUE, FIRST_BLOCK_SIZE(TINY_ZONE));
    }
    else if (IS_SMALL(size))
    {
        status = mm_get_new_page_from_kernel(&g_zones.small, &g_zones.small_tail, SMALL_ZONE_SIZE);
        if (status == FALSE)
            return (FALSE);
        set_block_metadata(GET_ZONE_FIRST_META_BLOCK(GET_ZONE_TAIL(SMALL_ZONE)), TRUE, FIRST_BLOCK_SIZE(SMALL_ZONE));
    }
    return (TRUE);
}

/**
 * Allocate a block of memory within a zone.
 * 
 * @param zone Pointer to the zone to allocate memory from
 * @param size Size of the memory to allocate
 * @return Pointer to the allocated memory
 */
static void *mm_split_free_data_block_for_allocation(t_vm_page *zone, size_t size)
{
    t_meta_block *curr_meta_block;
    t_meta_block *biggest_free_meta_block;
    size_t      aligned_size;
    size_t      leftover_size;

    // init_new_zone(size);

    biggest_free_meta_block = NULL;
    aligned_size = get_alligned_size(size);
    for (t_vm_page *zone_head = zone; zone_head; zone_head = zone_head->next)
    {
        curr_meta_block = GET_ZONE_FIRST_META_BLOCK(zone_head);
        while (IS_ADDR_IN_ZONE(zone_head, curr_meta_block))
        {
          if (curr_meta_block->is_free && aligned_size <= curr_meta_block->size &&\
              (!biggest_free_meta_block || curr_meta_block->size < biggest_free_meta_block->size))
              biggest_free_meta_block = curr_meta_block;
          curr_meta_block = GET_NEXT_META_BLOCK(curr_meta_block, curr_meta_block->size);
        }
    }
    if (biggest_free_meta_block)
    {
        leftover_size = biggest_free_meta_block->size - aligned_size;
        if (leftover_size > METADATA_SIZE)
            set_block_metadata(GET_NEXT_META_BLOCK(biggest_free_meta_block, aligned_size), TRUE, leftover_size - sizeof(t_meta_block));
        set_block_metadata(biggest_free_meta_block, FALSE, aligned_size);
        return (GET_VM_PAGE(biggest_free_meta_block));
    }
    init_new_zone(size);
    printk("zone ====>> %d\n", zone);
    return (mm_split_free_data_block_for_allocation(zone, size));
}

/**
 * Allocate a large block of memory using mmap directly.
 * 
 * @param size Size of the memory to allocate
 * @return Pointer to the allocated memory
 */
static inline void *get_large_alloc(size_t size)
{
    // struct rlimit   zone_size_limit;

    // getrlimit(RLIMIT_DATA, &zone_size_limit);
    // if (LARGE_ZONE_SIZE(size) > zone_size_limit.rlim_cur)
    //     return (NULL);
    if (mm_get_new_page_from_kernel(&g_zones.large, &g_zones.large_tail, LARGE_ZONE_SIZE(size)))
        return (GET_L_MEMORY_BLOCK(g_zones.large_tail));
    return (NULL);
}

/**
 * Custom malloc function that allocates memory using the zone allocation mechanism or the large allocation mechanism.
 * 
 * @param size Size of the memory to allocate
 * @return Pointer to the allocated memory
 */
void *ft_malloc(size_t size)
{
    if (size == 0)
        return (NULL);
    if (IS_LARGE(size))
        return (get_large_alloc(size));
    //here i init a new zone only if i don't find i right zone for the size
    if (!GET_RIGHT_ZONE(size) && init_new_zone(size) == FALSE)
        return (NULL);
    return (mm_split_free_data_block_for_allocation(GET_RIGHT_ZONE(size), size));
}

/**
 * Thread-safe malloc function that calls ft_malloc with a mutex lock.
 * 
 * @param size Size of the memory to allocate
 * @return Pointer to the allocated memory
 */
void *malloc(size_t size)
{
    void *ptr;
    //pthread_mutex_lock(&g_mutex);
    ptr = ft_malloc(size);
    //pthread_mutex_unlock(&g_mutex);
    return (ptr);
}
