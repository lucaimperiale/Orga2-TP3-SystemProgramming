/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "colors.h"
#include "defines.h"
#include "syscall.h" 

void task() {

    uint32_t numero = syscall_numero();
    
    if(numero==1) {
        uint32_t i, a = 0xA5A5A5A5;
        for(i=10;i<50000;i++) {
            syscall_escribir((4*32*26+i*4)%(4096),&a);
        }
    }

    if(numero==2) {
        uint32_t i, a = 0xA5A5A5A5;
        for(i=10;i<50000;i++) {
            syscall_escribir((4*32*7831+i*4)%(4096),&a);
        }
    }
    
    if(numero==3) {
        uint32_t a = 0xA5A5A5A5;
        while(1) {
            syscall_escribir(4096,&a);
        }
    }
    
    if(numero==4) {
        uint32_t a = 0xA5A5A5A5;
        uint32_t i=0;
        while(1) {
            syscall_leer(i%(4096),&a);
            i=i+4;
        }
    }
    
    while(1) { __asm __volatile("mov $2, %%eax":::"eax"); }
}
