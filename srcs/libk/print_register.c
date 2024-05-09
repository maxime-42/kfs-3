
#include "kernel.h"
#include "libk.h"

void print_register()
{
  unsigned int ebp, esp, eip, ecx, edx, ebx, eax, esi, edi;

    GET_EBP(ebp);
    GET_ESP(esp);
    GET_EIP(eip);
    GET_ECX(ecx);
    GET_EDX(edx);
    GET_EBX(ebx);
    GET_EAX(eax);
    GET_ESI(esi);
    GET_EDI(edi);

    ft_putstr((char const *)itoa_base(ebp, 16));
    ft_putchar('\n');
    ft_putstr((char const *)itoa_base(esp, 16));
    ft_putstr((char const *)itoa_base(eip, 16));
    ft_putchar('\n');
    ft_putstr((char const *)itoa_base(ecx, 16));
    ft_putchar('\n');
    ft_putstr((char const *)itoa_base(edx, 16));
    ft_putchar('\n');
    ft_putstr((char const *)itoa_base(ebx, 16));
    ft_putchar('\n');
    ft_putstr((char const *)itoa_base(eax, 16));
    ft_putchar('\n');
    ft_putstr((char const *)itoa_base(esi, 16));
    
    ft_putchar('\n');
    ft_putstr((char const *)itoa_base(edi, 16));
}