/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  funciones del controlador de interrupciones
*/

#ifndef __PIC_H__
#define __PIC_H__

#include "stdint.h"

void resetear_pic(void);
void habilitar_pic();
void deshabilitar_pic();

static __inline __attribute__((always_inline)) void outb(uint32_t port, uint8_t data);

void fin_intr_pic1(void);
void fin_intr_pic2(void);

#endif	/* !__PIC_H__ */
