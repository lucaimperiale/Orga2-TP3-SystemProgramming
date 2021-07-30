/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "stdint.h"
#include "screen.h"
#include "tss.h"
#include "defines.h"

typedef struct str_sched {
    uint8_t tareaActual;
    uint8_t tareasDesalojadas[8];
    uint8_t relojes[10][2];
} __attribute__((__packed__)) sched;


int16_t sched_proximoIndice();
void scheduler_inicializar();
uint8_t actualizarScheduler();
void matarTareaPantalla();

void actualizarEipPila(uint32_t *pila);



extern sched scheduler;
extern int16_t ordenTareas [10];

#endif	/* !__SCHED_H__ */
