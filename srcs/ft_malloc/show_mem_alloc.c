#include "malloc.h"

inline static void putstr(const char *str)
{
    for (int i = 0; str[i]; i++)
        ft_putchar(&str[i]);
        // write(1, &str[i], 1);
        
}

void print_base(unsigned int number, unsigned short base)
{
    const char  tokens[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char        base_number[sizeof(number) * 8];
    char        *base_pointer;               
    if (base > sizeof(tokens))
        return;
    base_pointer = base_number;
    if (number == 0)
        *base_pointer++ = '0';
    while (number)
    {
        *base_pointer++ = tokens[number % base];
        number /= base;
    }
    while (base_pointer-- != base_number - 1)
    ft_putchar(base_pointer);
        // write(1, base_pointer, 1);
}

void write_hex(void *addr, size_t size) {
    char buffer[256];
    // int len = snprintf(buffer, sizeof(buffer), "%p: ", addr);
    (void) size;
    ft_putchar(buffer);
    // write(1, buffer, len);
}

void write_byte(unsigned char byte) {
    char buffer[4];
    // int len = printk("%02x ", byte);
    // write(1, buffer, len);
    ft_putchar(buffer);

}



static void print_hex(unsigned char *ptr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
      if (i % 16 == 0)
        write_hex(ptr + i, size - i);
      if (i % 16 && i % 8 == 0)
        ft_putchar(" ");
        // write(1, " ", 1);

      write_byte(ptr[i]);
      if (i % 16 == 15 || i + 1 == size)
        ft_putchar("\n");
        // write(1, "\n", 1);
    }
}

inline static void print_mem_info(void *start, void *end, long size)
{
    PRINT_ADDR(start);
    putstr(" - ");
    PRINT_ADDR(end);
    putstr(" : \033[0;32m");
    PUT_NBR(size);
    putstr(" \033[0mbytes\n");
}

static void print_zone_infos(t_zone_type zone_type, t_bool extra_infos)
{
    t_vm_page      *chosen_zone;
    t_meta_block *block_hdr;

    chosen_zone = GET_ZONE_BY_TYPE(zone_type);
    ft_putstr(GET_ZONE_NAME(zone_type));
    ft_putstr("\t: ");
    PRINT_ADDR(chosen_zone);
    ft_putstr("\n");
    if (!chosen_zone)
        return ;
    if (zone_type == LARGE_ZONE)
    {
        for (t_vm_page *zone_head = chosen_zone; zone_head; zone_head = zone_head->next)
        {
            print_mem_info(GET_L_MEMORY_BLOCK(zone_head), zone_head + zone_head->size, zone_head->size);
            if (extra_infos)
                print_hex((unsigned char *)GET_L_MEMORY_BLOCK(zone_head), zone_head->size - sizeof(t_vm_page));
        }
    }
    else
    {
        for (t_vm_page *zone_head = chosen_zone; zone_head; zone_head = zone_head->next)
        {
            block_hdr = GET_ZONE_FIRST_META_BLOCK(zone_head);
            while (IS_ADDR_IN_ZONE(zone_head, GET_NEXT_META_BLOCK(block_hdr, block_hdr->size)))
            {
                print_mem_info(GET_VM_PAGE(block_hdr), GET_BLOCK_FOOTER(block_hdr), block_hdr->size - sizeof(t_ftr_block));
                if (block_hdr->is_free == false && extra_infos)
                    print_hex((unsigned char *)GET_VM_PAGE(block_hdr), block_hdr->size - sizeof(t_ftr_block));
                block_hdr = GET_NEXT_META_BLOCK(block_hdr, block_hdr->size);
            }
        }
    }
}

void show_alloc_mem()
{
    //pthread_mutex_lock(&g_mutex);
    print_zone_infos(TINY_ZONE, false);
    print_zone_infos(SMALL_ZONE, false);
    print_zone_infos(LARGE_ZONE, false);
    //pthread_mutex_unlock(&g_mutex);
}

// void show_alloc_mem_ex()
// {
//     //pthread_mutex_lock(&g_mutex);
//     print_zone_infos(TINY_ZONE, true);
//     print_zone_infos(SMALL_ZONE, true);
//     print_zone_infos(LARGE_ZONE, true);
//     //pthread_mutex_unlock(&g_mutex);
// }