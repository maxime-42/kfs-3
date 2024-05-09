#include "libk.h"


void		printk(char *str, ...)
{
	int		*arg_ptr;
	char	*format;
	int		i = 0;
	uint8	zero_padding;
	char	temp_buffer[9];

	arg_ptr = (int *)(&str);
	format = (char *)(*arg_ptr++);

	while (format[i]) 
	{
		zero_padding = 0;

        if (format[i] == '%') {
            i++;
            
            // Check for zero padding
            if (format[i] == '0') {
                i++;
                zero_padding = format[i] - '0';
                i++;
            }

            // Process format specifiers
            switch (format[i]) {
                case 'c':
                    ft_putchar(*arg_ptr++);
                    break;
                case 's':
                    ft_putstr(*((char **)arg_ptr++));
                    break;
                case 'x':
                    kmemset(temp_buffer, 0, sizeof(temp_buffer));
                    hex_to_str(*arg_ptr++, temp_buffer);
                    ft_putstr(temp_buffer);
                    break;
                case 'p':
                    kmemset(temp_buffer, 0, sizeof(temp_buffer));
                    hex_to_str(*arg_ptr++, temp_buffer);
                    ft_putstr("0x");
                    ft_putstr(temp_buffer);
                    break;
                case 'd':
                    // Handle zero padding
                    if (zero_padding > 0) {
                        while (zero_padding - number_digit(*arg_ptr)) {
                            ft_putchar('0');
                            zero_padding--;
                        }
                    }
                    kputnbr(*arg_ptr++);
                    break;
                default:
                    // Print the character directly if not a format specifier
                    ft_putchar('%');
                    ft_putchar(format[i]);
                    break;
            }
        } else {
            // Print non-format characters directly
            ft_putchar(format[i]);
        }
        i++;
    }
}
