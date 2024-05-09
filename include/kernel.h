
#ifndef _KERNEL_H
#define _KERNEL_H

#include <stddef.h>
#include "config.h"

#define MULTI_ADDRESS    0x000007B0 
#define STRING_ADDRESS	0x000007D0 
#define GDT_ADDRESS 0x00000800

#define GET_EBP(x) __asm__ volatile("mov %%ebp, %0" : "=r"(x)::)
#define GET_ESP(x) __asm__ volatile("mov %%esp, %0" : "=r"(x)::)
#define GET_EIP(x) __asm__ volatile("movl $1f, %0; 1:" : "=r"(x))

//#define GET_EIP(x) __asm__ volatile("mov %%eip, %0" : "=r"(x)::)
#define GET_ECX(x) __asm__ volatile("mov %%ecx, %0" : "=r"(x)::)
#define GET_EDX(x) __asm__ volatile("mov %%edx, %0" : "=r"(x)::)
#define GET_EBX(x) __asm__ volatile("mov %%ebx, %0" : "=r"(x)::)
#define GET_EAX(x) __asm__ volatile("mov %%eax, %0" : "=r"(x)::)
#define GET_ESI(x) __asm__ volatile("mov %%esi, %0" : "=r"(x)::)
#define GET_EDI(x) __asm__ volatile("mov %%edi, %0" : "=r"(x)::)




enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};


/* ************************************************************************** */
/*				Prototype                                     */
/* ************************************************************************** */


extern void halt(void);
void	ft_putstr(const char* str);
void	terminal_initialize();
void	kmain();
void	terminal_writechar(char c, char colour);
void	ft_putstr_color(const char* str, uint32 color);
void	print_register();
void	set_function();
void	set_string();
extern 	void test_syscalls();
// void print_char_with_asm(char *ptr);

#endif // SOME_HEADER_H
