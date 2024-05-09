#include "libk.h"

void	kputnbr(int nb)
{
	char *str = itoa_base(nb, DECIMAL);
	ft_putstr(str);
}