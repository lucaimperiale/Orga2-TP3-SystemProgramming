/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#ifndef __GAME_H__
#define __GAME_H__

#include "stdint.h"
#include "defines.h"
#include "screen.h"
#include "mmu.h"
#include "sched.h"



typedef struct game_t {
    uint8_t vidasA;
    uint8_t vidasB;
    uint8_t eipAx;
    uint8_t eipAy;
    uint8_t eipBx;
    uint8_t eipBy;
} __attribute__((__packed__)) game_t;


void game_inicializar();

uint32_t game_numero();

void game_escribir(uint32_t direccion, uint32_t* dato);

void game_leer(uint32_t direccion, uint32_t* dato);

void restarVida();

void actualizarPantalla(uint32_t eip);

extern void terminarGame();

void avanzarReloj();
void actualizarRelojes();

void imprimirLectura(uint32_t offset);
void imprimirEscritura(uint32_t offset);

uint8_t verificarEntradas(uint32_t dato,uint32_t offset);
uint8_t llamoUnaSaltadora();




#endif  /* !__GAME_H__ */
