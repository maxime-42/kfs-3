// #include "uapi_mm.h"
#include <string.h>
#include <unistd.h>
// #include <stdlib.h>
#include "malloc.h"
#include "libk.h"
#include "heap.h"
// #include "kernel.h"
/**
 * il faudra que je verifie demain dans quelle vm_page le block 4 se trouve
 * car lorsque je le free le realloc segfault donc cela signifie que cette page
 * a ete retourne au kernel mais que le pointeur n'a pas ete mis a null
 * donc pour le realloc lorsque je cherche le plus grand free, cela me fais
 * depasser dans ma boucle et donc je segfault
 * 
 * @return int 
 */


int testeur()
{
    char * addr = vmalloc(300);
    for(int i = 0; i < 5 ; i++) {
  		addr[i] = i+48;
    }
	addr[5] = '\0';
    printk(" ===>>> before free addr = %s \n", addr);
    printk("vsize = %d\n", vsize(addr));
    printk("ksize = %d\n", ksize(addr));

    vfree(addr);

    for(int i = 0; i < 5 ; i++) {
		addr[i] = i+48;
    }
	addr[5] = '\0';
    printk(" ===>>> after free addr = %s \n", addr);
    return (1); 
}





// int testeur1()
// {
//     char * addr = kmalloc(700);
//     for(int i = 0; i < 5 ; i++) {
//   		addr[i] = i+48;
//     }
// 	addr[5] = '\0';
//     printk("before addr = %p\n", addr);

//     vfree(addr);

//     char *addr2 = kmalloc(700);
//     printk(" after addr = %p\n", addr2);

//     return (0); 
// }

// int     testeur2()
// {
//     uint32  *addr;
//     for(int i = 0; i < 10; i++)
//     {
//       addr = vmalloc(60);
//       if (addr == NULL)
//       {
//           printk("Failed to allocate memory\n");
//           return (1);
//       }
//       printk("size = %d\n", vsize(addr));
//       printk("size = %d\n", ksize(addr));
//       addr[0] = 42;
//       printk("addr = %s\n", addr);
//    }
//     return (0);
// }
