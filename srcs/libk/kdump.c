#include "kernel.h"
#include "libk.h"

/*******************************
 * @brief: the function is to print a hexadecimal representation of a character c, 
 * along with some spacing logic.
 * 
 * @param: c - the character to be printed
 * @param: index - the index of the character in the string
 * 
 * @return: None
 *******************************/

static void ft_print_hex(uint8 c, uint32 index) 
{
    const char base[HEX_BASE] = "0123456789abcdef";

    if (index < HEX_BASE) {
        // ft_putchar(base[c / HEX_BASE]);
        // ft_putchar(base[c % HEX_BASE]);
        // ft_putchar(' ');
		printk("%c%c ", base[c / HEX_BASE], base[c % HEX_BASE]);
    }

    // if ((index + 1) % 8 == 0)
        // ft_putchar(' ');
	if (index == 16)
        ft_putchar(' ');

}

/**************************************************
 * @brief:The function it is about to print a memory dump
 * with hexadecimal values and their corresponding ASCII characters.
 *
 * @param: mem_addr - the address of the memory to be printed
 * @ param: size - the size of the memory to be printed
 * 
 * @return: None
 ***************************************************/
void kdump(void *mem_addr, uint32 size) 
{
    
	uint32 *ptrAddr = (uint32 *)mem_addr;
    uint32 addr = *ptrAddr;
    char *str = (char *)addr;
    // char addr_str[9];

	// kmemset(addr_str, 0, sizeof(addr_str));
    for (uint32 j = 0; j < size; j++) {
		printk("%x| ", addr);

        for (uint32 i = 0; i < 32; i++)
            ft_print_hex(str[i], i);

        ft_putchar('|');

        for (uint32 i = 0; i < 16; i++)
            print_ascii(str[i]);

        ft_putstr("|\n");

        addr += HEX_BASE;
        str = (char *)addr;
    }
}
