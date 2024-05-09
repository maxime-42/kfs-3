#include "interrupts.h"
#include "config.h"
#include "libk.h"
#include "io.h"
#include "idt.h"
#include "keyboard.h"


static char azerty_keyboard[128] = {
	0, 0, '&', 0, '"', '\'', '(', 0, 0, '!', 0, 0, ')', '-', '\b', 0, 'a', 'z',
    'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$', '\n', 0, 'q', 's', 'd',
    'f', 'g', 'h', 'j', 'k', 'l', 'm', 0, '<', 0, '`', 'w', 'x', 'c', 'v', 'b',
    'n', ',', ';', ':', '=', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.', '6',
	0, 0, 0, 0, 0
};

static char qwerty_keyboard[128] = {
	0, 0, '1', '2','3','4','5','6','7','8','9','0','-','=',	'\b',/* backspace */
	'\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',  /* enter */
	CTRL_KEY,'a', 's','d','f','g','h','j','k','l',';','\'',	'`',
	SHIFT_KEY, '\\','z','x','c','v','b','n','m',',','.','/',
	SHIFT_KEY,      /* right shift */'*',0, /* alt */' ',  /* space */
	CAPSLOCK_KEY,   /* caps lock */
	0,              /* F1 */
	0,              /* F2 */
	0,              /* F3 */
	0,              /* F4 */
	0,              /* F5 */
    0,              /* F6 */
	0,              /* F7 */
	0,              /* F8 */
	0,              /* F9 */
	0,              /* F10 */
	0,              /* num lock */
	0,              /* scroll lock */
	0,              /* HOME */
	0,              /* up arrow */
	0,              /* PAGEUP */
	'-',
	LEFT_ARROW_KEY, /* left arrow */
	0,
	RIGHT_ARROW_KEY,/* right arrow */
	'+',
	0,              /* END */
	0,              /* down arrow */
	0,              /* PAGEDOWN */
	0,              /* INSERT */
	0,              /* DEL */
	0,
	0,
	0,
	0,              /* F11 */
	0,              /* F12 */
	0               /* undefined keys */
};

/********************************************************************************
 * @brief: select the keyboard layout
 * @return: the keyboard layout
 */

static char *selec_keyboard_layout()
{
	if (get_keyboard_layout() == AZERTY)
	{
		return azerty_keyboard;
	}
	return qwerty_keyboard;
}


/*****************************
 * @brief:This function is called when a key has been pressed on the keyboard. 
 * @param:frame  - A pointer to the frame of the interrupt stack
 */
static void keyboard_handler(t_interrupt_frame frame)
{
	uint16		scan_code = inb(KEYBOARD_DATA_PORT) & 0x7F;/********** Get the data from the port **********/
	char 		*kb_layout = selec_keyboard_layout();
	char		character = kb_layout[scan_code]; /******* Translate to ASCII if possible *******/

	inb(KEYBOARD_DATA_PORT) ;//Read the data to clear the interrupt

	uint16	pressRelease = inb(KEYBOARD_DATA_PORT) & 0X80;
    
	if (pressRelease)//If it's a release we don't care about it for now
        return;
	else
	{
		outb(KEYBOARD_DATA_PORT, 0);/*********** Clear the buffer ***********/
		put_char_to_buffer(character);
		// outb(KEYBOARD_DATA_PORT, 0);

	}
	(void)frame;
}

/**
 * @brief: This function is called to initialize the keyboard
 * @return: void
 * 
 */
void init_keyboard()
{
    int ret = add_handler(33, &keyboard_handler);

	(void)ret;
}