#include "keyboard.h"
#include "libk.h"
#include "io.h"

// this file is for keyboard buffer
// it is used to store the keyboard input
// and it is used to get the keyboard input

// and it is used to get the keyboard layout

// and it is used to set the keyboard layout


static t_keyboard_buffer keyb_buf;

/********************************
 * @brief: init the keyboard buffer
 *
 ********************************/
void	init_keyboard_buffer()
{
	// kmemset(&keyb_buf, 0, sizeof(keyb_buf.buffer));
	kmemset(&keyb_buf, 0, sizeof(keyb_buf));
}


/*****************************
 * @brief: get the keyboard buffer
 * @Return: the keyboard buffer
 *
 *****************************/
char *get_keyboard_buffer()
{
	return keyb_buf.buffer;
}


/********************************
 * @brief: get the keyboard layout
 * @Return: the keyboard layout
 *
 ********************************/

uint32	get_keyboard_layout()
{
	return keyb_buf.layout;
}

/*****************************
 * @brief: set keyboard layout
 * @param layout : the layout you want to set
 *
 *****************************/
void	set_keyboard_layout(uint8 layout)
{
	keyb_buf.layout = layout;
}


/*****************************
 * @brief: get the last char in buffer
 * @Return: the last char in buffer
 * 
 *****************************/
char	get_last_char()
{
	return keyb_buf.buffer[keyb_buf.head - 1] ;

}

/*****************************
 * @brief: clear buffer
 *
 *****************************/
void	clear_buffer()
{
	kmemset(&keyb_buf, 0, sizeof(keyb_buf.buffer));
	keyb_buf.head = 0;
	keyb_buf.tail = 0;
}

/*****************************
 * @brief: add data to buffer
 * @param data : the char you want to push into buffer
 * @Return:  0-success ,1-fail
 * ****************************/
int put_char_to_buffer(unsigned char data)
{
	if(data == 0)
		return  1;
	if (keyb_buf.head >= KEYB_BUFLEN )
	{
		keyb_buf.head = 0;
		kmemset(&keyb_buf, 0, sizeof(keyb_buf.buffer));
	}
    // outb(KEYBOARD_DATA_PORT, 0);
	// store new char to buffer and increase head index
	keyb_buf.buffer[keyb_buf.head++] = data;
	ft_putchar(data);
	// outb(KEYBOARD_DATA_PORT, 0);

	return  0;
}