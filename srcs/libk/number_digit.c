// #include "config"

int		number_digit(int n)
{
    int	i = 0;

    if (n == 0)
        return 1;

    if (n < 0) {
        i++;  // Account for the negative sign
        n = -n;  // Make the number positive
    }

    while (n != 0) {
        n /= 10;
        i++;
    }

    return i;
}
