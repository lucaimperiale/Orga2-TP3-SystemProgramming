/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#ifndef __SYSCALL_H__
#define __SYSCALL_H__

#include "stdint.h"

#define LS_INLINE static __inline __attribute__((always_inline))

/*
 * Syscalls
 */

LS_INLINE uint32_t syscall_numero() {
    int32_t ret;
    __asm __volatile(
        "mov $0x542, %%eax \n"
        "int $0x66     \n"
        "mov %%ebx, %0"
        : "=r" (ret)
        : /* no input */
        : "eax", "ebx"
    );
    return ret;
}

LS_INLINE void syscall_escribir(uint32_t direccion, uint32_t* dato) {
    __asm __volatile(
        "mov $0x824, %%eax \n"
        "mov %0, %%ebx \n"
        "mov %1, %%ecx \n"
        "int $0x66     \n"
        : /* no output*/
        : "m" (direccion), "m" (dato)
        : "eax", "ebx"
    );
}

LS_INLINE void syscall_leer(uint32_t direccion, uint32_t* dato) {
    __asm __volatile(
        "mov $0x7CA, %%eax \n"
        "mov %0, %%ebx \n"
        "mov %1, %%ecx \n"
        "int $0x66     \n"
        : /* no output*/
        : "m" (direccion), "m" (dato)
        : "eax", "ebx"
    );
}

#endif  /* !__SYSCALL_H__ */
