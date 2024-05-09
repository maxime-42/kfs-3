#include "config.h"
#include "io.h"

/*****************************************
 * @brief:   Shutdown the system and close windows
 * @return:  void
 *****************************************
*/
void qemu_shutdown(void)
{
    CLEAN_REGISTERS();
    outw(0x604, 0x2000);
}
