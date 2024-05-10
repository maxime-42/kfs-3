

#include "../include/heap.h"

int main(){
  kheap_init();
  void * ptr = kmalloc(10);
  (void) ptr;
}