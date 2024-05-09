#include "libk.h"
#include "kernel.h"
#include "keyboard.h"
#include "shell.h"
#include "commands.h"
#include "interrupts.h"
#include "io.h"

/*
*	read_line
*		check if the last char is a new line
*		return 1 if it is a new line
*		return 0 if it is not a new line
*/
static uint32		read_line()
{

		// ft_putstr("keyb_buf.buffer");
		if (get_last_char() == '\n')
		{
			
			// init_keyboard_buffer();
			// kmemest(keyb_buf.buffer, 0, sizeof(keyb_buf.buffer));
			// clear_buffer();
			return NEW_LINE;

		}
	return NO_NEW_LINE;
}




/***********************************************************************

 * @brief: this function is used to execute the command entered by the user
 * 
 * @param: void
 * 
 * @return: int
 * @note:
 * @details: allow
************************************************************************/
static uint32 exec_command(void) {
    char *ptr_buf = get_keyboard_buffer();
    int ret = read_line();
	uint32 addr = 0X000007C0 - 32;

    if (ret == NEW_LINE) 
	{
        if (strcmp(ptr_buf, "azerty\n") == 0) {
            set_keyboard_layout(AZERTY);
        } else if (strcmp(ptr_buf, "qwerty\n") == 0) {
            set_keyboard_layout(QWERTY);
        } else if (strcmp(ptr_buf, "shutdown\n") == 0) {
            qemu_shutdown();
        } else if (strcmp(ptr_buf, "stack\n") == 0) {
            kdump(&addr, 10);
        } else if (strcmp(ptr_buf, "panic\n") == 0) {
            kdump(&addr, 10);
            kpanic();
        } else if (strcmp(ptr_buf, "clear\n") == 0) {
            terminal_initialize();
        } else if (strcmp(ptr_buf, "reboot\n") == 0) {
            reboot();
        } else {
			printk("Invalid command: %s\n", ptr_buf);
        }

        clear_buffer();
        // ft_putstr("$> ");
    }

    return ret;
}

static void display_menu() 
{

	printk("======================\n");
	printk("| Available Commands |\n");
	printk("======================\n");
	printk("| azerty    : Set keyboard layout to AZERTY.   |\n");
	printk("| qwerty    : Set keyboard layout to QWERTY.   |\n");
	printk("| shutdown  : Shutdown the system.             |\n");
	printk("| stack     : Display stack information.       |\n");
	printk("| panic     : Display stack information and    |\n");
	printk("|             enter kernel panic.              |\n");
	printk("| clear     : Clear the terminal screen.       |\n");
	printk("| reboot    : Reboot the system.               |\n");
	printk("======================\n");
}
void		shell(void)
{
	uint8	ret = NEW_LINE;
	display_menu();
	while (1)
	{
		if (ret == NEW_LINE)
		{
			exec_command();
			ft_putstr("$> ");
		}

		ret = read_line();
	}
	
}