#include "kernel.h"
#include "io.h"
#include "config.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25 
uint16* video_mem = 0;
uint16 terminal_row = 0;
uint16 terminal_col = 0;
// static uint32 color = VGA_COLOR_WHITE;


uint16 terminal_make_char(char c, char colour)
{
    return (colour << 8) | c;
}

void terminal_putchar(int x, int y, char c, char colour)
{
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}

void terminal_backspace()
{
    if (terminal_row == 0 && terminal_col == 0)
    {
        return;
    }

    if (terminal_col == 0)
    {
        terminal_row -= 1;
        terminal_col = VGA_WIDTH;
    }

    terminal_col -=1;
    terminal_writechar(' ', 15);
    terminal_col -=1;
}

void terminal_writechar(char c, char colour)
{
    outb(COM1, c);

    if (c == '\n')
    {
        terminal_row += 1;
        terminal_col = 0;
        return;
    }

//  if (c == 0x08)
//     {
//         terminal_backspace();
//         return;
//     }

    terminal_putchar(terminal_col, terminal_row, c, colour);
    terminal_col += 1;
    if (terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row += 1;
    }
}

void ft_putchar(char c )
{
	terminal_writechar(c, VGA_COLOR_WHITE);
}

void terminal_initialize()
{
    video_mem = (uint16*)(0xB8000);
    terminal_row = 0;
    terminal_col = 0;
    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            terminal_putchar(x, y, ' ', 0);
        }
    }   
}


size_t strlen(const char* str)
{
    size_t len = 0;
    while(str[len])
    {
        len++;
    }

    return len;
}


void ft_putstr(const char* str)
{
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++)
    {
        terminal_writechar(str[i], VGA_COLOR_WHITE);
    }
}