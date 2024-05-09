#include "libk.h"

void	print_ascii(char c)
{
	if (c >= 32 && c <= 126) 
		ft_putchar(c);
	else 
		ft_putchar('.');
}
