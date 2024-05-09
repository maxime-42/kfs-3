#ifndef _LIBK_H
#define _LIBK_H

#include <stddef.h>
#include "config.h"

void		*kmemset(void *b, int c, size_t len);
void		ft_putstr(const char* str);
void		ft_putchar(char c );
char		*itoa_base(int num, int base);
void		*kmemcpy(void *dest, const void *src, size_t n);
size_t		strlen(const char* str);
void		ft_putchar(char c );
void		print_register();
void		print_ascii(char c);
void		hex_to_str(uint32 addr, char *result);
void		ft_putchar(char c );
int			strcmp(const char *s1, const char *s2);
void		printk(char *str, ...);
void		kputnbr(int nb);
int			number_digit(int n);
void		kdump(void *mem_addr, uint32 sizee);

#endif // !_LIBK_H
