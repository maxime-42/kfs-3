#include "libk.h"


char	*itoa_base(int num, int base)
{
	// Declare a static array of 33 characters to hold the converted integer
    // (32 characters for the converted integer + 1 for the null terminator)
    static char text[33];  // Max length for 32-bit integer in binary + null terminator
    int loc = 32;
	kmemset(&text, 0, sizeof(text));

	// If the input integer is zero, set the first character of the text array
    // to '0' and skip the rest of the conversion
    if (num == 0)
    {
        text[--loc] = '0';
    }
    else
    {
	       // Initialize a variable to track the negative sign, if any
        int neg = 0;
        if (num < 0)
        {
            neg = 1;
            num = -num;
        }
        while (num)
        {
            int remainder = num % base;
         // If the remainder is less than 10, add the corresponding
            // digit character ('0' through '9') to the text array
            // Otherwise, add the corresponding letter character ('A' through 'Z')
            // to the text array
		    text[--loc] = (remainder < 10) ? ('0' + remainder) : ('A' + remainder - 10);
            // Divide the integer by the base to continue the conversion
		    num /= base;
        }
        if (neg)
            text[--loc] = '-';
    }
	    // Return a pointer to the beginning of the converted string
    return &text[loc];
}
