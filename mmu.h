/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#include "stdint.h"
#include "defines.h"
#include "i386.h"
#include "tss.h"
#include "game.h"

#define INICIO_PAGINAS_LIBRES_KERNEL 0x00100000
#define INICIO_PAGINAS_LIBRES_TAREAS 0X00400000
#define PAGE_SIZE 4096

typedef struct str_pd_entry {    
    uint8_t  p:1;
    uint8_t  r_w:1;
    uint8_t  u_s:1;
    uint8_t  pwt:1;
    uint8_t  pcd:1;
    uint8_t  a:1;
    uint8_t  ign:1;
    uint8_t  ps:1;
    uint8_t  g:1;
    uint8_t  disp:3;
    uint32_t base:20;

} __attribute__((__packed__, aligned (4))) pd_entry;

typedef struct str_pt_entry {
  uint8_t  p:1;
    uint8_t  r_w:1;
    uint8_t  u_s:1;
    uint8_t  pwt:1;
    uint8_t  pcd:1;
    uint8_t  a:1;
    uint8_t  dirt:1;
    uint8_t  ps:1;
    uint8_t  g:1;
    uint8_t  disp:3;
    uint32_t base:20;
} __attribute__((__packed__, aligned (4))) pt_entry;




void mmu_inicializar();
void mmu_inicalizar_tareas();
unsigned int mmu_proxima_pagina_fisica_libre_kernel();
unsigned int mmu_proxima_pagina_fisica_libre_tareas();
void mmu_mapear_pagina(unsigned int dir_virtual, unsigned int dir_pd, unsigned int fisica, unsigned char u_s);
void mmu_unmapear_pagina(unsigned int dir_virtual, unsigned int dir_pd);
void identity_mapping(unsigned int dir_pd);
void mmu_inicializar_dir_kernel();
unsigned int mmu_inicializar_tarea(int indice_tarea);

void resetearTarea(int indice_tarea);



#endif	/* !__MMU_H__ */




