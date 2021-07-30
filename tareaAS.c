/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "i386.h"
#include "colors.h"
#include "defines.h"
#include "syscall.h" 

void task() {
    //breakpoint();
    void *m = (void*)0x8000d29;
    uint16_t *d = (uint16_t*)m;
    *d = 0xfeeb;
    goto *m;

	//    int32_t i=0;
    while(1) {
    	//m = (void*) (0x8000000 + (4*32*7831+i*4) %(4096));
    	//breakpoint();
    	//*d = 0xfeeb;
    	//i ++;
    	//goto *m;
    }
}
