#ifndef _KEYBOARD_H
#define _KEYBOARD_H 
#include "config.h"

void init_keyboard();
#define KEYB_BUFLEN	1024
#define AZERTY 0
#define QWERTY 1
# define SHIFT_KEY              -1
# define CTRL_KEY               -2
# define CAPSLOCK_KEY           -3
# define LEFT_ARROW_KEY         -10
# define RIGHT_ARROW_KEY        -11
/* ************************************************************************** */
/* 			Structs                                               */
/* ************************************************************************** */


typedef struct	keyboard_buffer
{
	char		buffer[KEYB_BUFLEN];
	uint16		tail; //incrmente during push*
	uint16		head; //incremente during decrementaton*
	uint8		layout;
}	t_keyboard_buffer;



/* ************************************************************************** */
/* 			PROTOTYPE                                            */
/* ************************************************************************** */

void	init_keyboard_buffer();
int		put_char_to_buffer(unsigned char data);

void	clear_buffer();
void	set_keyboard_layout(uint8 layout);
char	get_last_char();
uint32	get_keyboard_layout();
void	clear_buffer();
char	*get_keyboard_buffer();

#endif // !_KEYBOARD_H
