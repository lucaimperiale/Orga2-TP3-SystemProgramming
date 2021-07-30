/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"

#define agregarBase(descriptor_tss,tss) gdt[descriptor_tss].base_0_15 = (uint16_t)(uint32_t)(&tss) ;\
    gdt[descriptor_tss].base_23_16 = (uint8_t)(uint32_t)(&tss) >> 16;\
    gdt[descriptor_tss].base_31_24 = (uint8_t)(uint32_t)(&tss) >> 24;

tss tss_inicial;
tss tss_idle;
tss tss_cazadora_a[4];
tss tss_cazadora_b[4];
tss tss_saltadora_a;
tss tss_saltadora_b;


void asignarUnused(tss* tss){
    tss->unused0 = 0;
    tss->unused1 = 0;
    tss->unused2 = 0;
    tss->unused3 = 0;
    tss->unused4 = 0;
    tss->unused5 = 0;
    tss->unused6 = 0;
    tss->unused7 = 0;
    tss->unused8 = 0;
    tss->unused9 = 0;
    tss->unused10 = 0;
}

void tss_idle_inicializar(){
	asignarUnused(&tss_idle);

	tss_idle.ptl =0;
    tss_idle.esp0 = 0;
    tss_idle.esp1 = 0;
    tss_idle.ss1 = 0;
    tss_idle.esp2 = 0;
    tss_idle.ss2 = 0;
    tss_idle.cr3 = 0x27000;
    tss_idle.eip = 0x14000;
    tss_idle.eflags = 0x202;
    tss_idle.eax = 0;
    tss_idle.ecx = 0;
    tss_idle.edx = 0;
    tss_idle.ebx = 0;
	tss_idle.esp = 0x27000;
	tss_idle.ebp = 0x27000;
    tss_idle.esi = 0;
    tss_idle.edi = 0;
    tss_idle.cs = (GDT_IDX_CODIGO_0 << 3);
    tss_idle.ss = (GDT_IDX_DATOS_0 << 3);
    tss_idle.ds = (GDT_IDX_DATOS_0 << 3);
    tss_idle.es = (GDT_IDX_DATOS_0 << 3);
    tss_idle.fs = (GDT_IDX_DATOS_0 << 3);
    tss_idle.gs = (GDT_IDX_DATOS_0 << 3);
    tss_idle.ldt = 0;
    tss_idle.dtrap = 0;
    tss_idle.iomap = 0xFFFF;

}

void tss_cazadora_inicializar(tss* cazadora){
	asignarUnused(cazadora);

	cazadora->ptl = 0;
    //cazadora->esp0;
    //cazadora->ss0;
    cazadora->esp1 = 0;
    cazadora->ss1 = 0;
    cazadora->esp2 = 0;
    cazadora->ss2 = 0;
    //cazadora->cr3 = 0;
    cazadora->eip = 0x8000000;
    cazadora->eflags = 0x202;
    cazadora->eax = 0;
    cazadora->ecx = 0;
    cazadora->edx = 0;
    cazadora->ebx = 0;
	cazadora->esp = 0x8000000 + 0x1000;
	cazadora->ebp = 0x8000000 + 0x1000;
    cazadora->esi = 0;
    cazadora->edi = 0;
    cazadora->cs = (GDT_IDX_CODIGO_3 << 3 | 3);
    cazadora->ss = (GDT_IDX_DATOS_3 << 3 | 3);
    cazadora->ds = (GDT_IDX_DATOS_3 << 3 | 3);
    cazadora->es = (GDT_IDX_DATOS_3 << 3 | 3);
    cazadora->fs = (GDT_IDX_DATOS_3 << 3 | 3);
    cazadora->gs = (GDT_IDX_DATOS_3 << 3 | 3);
    cazadora->ldt = 0;
    cazadora->dtrap = 0;
    cazadora->iomap = 0xFFFF;

}

void tss_saltadora_inicializar(tss* saltadora){
	asignarUnused(saltadora);

	saltadora->ptl = 0;
    //saltadora->esp0;
    //saltadora->ss0;
    saltadora->esp1 = 0;
    saltadora->ss1 = 0;
    saltadora->esp2 = 0;
    saltadora->ss2 = 0;
    //saltadora->cr3 ;
    saltadora->eip = 0x8000000;
    saltadora->eflags = 0x202;
    saltadora->eax = 0;
    saltadora->ecx = 0;
    saltadora->edx = 0;
    saltadora->ebx = 0;
	saltadora->esp = 0x8000000 + 0x1000;
	saltadora->ebp = 0x8000000 + 0x1000;
    saltadora->esi = 0;
    saltadora->edi = 0;
    saltadora->cs = (GDT_IDX_CODIGO_3 << 3 | 3);
    saltadora->ss = (GDT_IDX_DATOS_3 << 3 | 3);
    saltadora->ds = (GDT_IDX_DATOS_3 << 3 | 3);
    saltadora->es = (GDT_IDX_DATOS_3 << 3 | 3);
    saltadora->fs = (GDT_IDX_DATOS_3 << 3 | 3);
    saltadora->gs = (GDT_IDX_DATOS_3 << 3 | 3);
    saltadora->ldt = 0;
    saltadora->dtrap = 0;
    saltadora->iomap = 0xFFFF;
}

void cargar_cr3_pilas(tss* tss, int indice){
	unsigned int cr3 = mmu_inicializar_tarea(indice);
	tss->cr3 = cr3;
	tss->esp0 = mmu_proxima_pagina_fisica_libre_kernel() + 0x1000;
	tss->ss0 = (GDT_IDX_DATOS_0 << 3);

}



void tss_inicializar() {

    agregarBase(GDT_TSS_INICIAL,tss_inicial)
    agregarBase(GDT_TSS_IDLE,tss_idle)

    agregarBase(GDT_TSS_SALTADORA_A,tss_saltadora_a)
    agregarBase(GDT_TSS_SALTADORA_B,tss_saltadora_b)


    agregarBase(GDT_TSS_CAZADORA_A1,tss_cazadora_a[0])
    agregarBase(GDT_TSS_CAZADORA_A2,tss_cazadora_a[1])
    agregarBase(GDT_TSS_CAZADORA_A3,tss_cazadora_a[2])
    agregarBase(GDT_TSS_CAZADORA_A4,tss_cazadora_a[3])

    agregarBase(GDT_TSS_CAZADORA_B1,tss_cazadora_b[0])
    agregarBase(GDT_TSS_CAZADORA_B2,tss_cazadora_b[1])
    agregarBase(GDT_TSS_CAZADORA_B3,tss_cazadora_b[2])
    agregarBase(GDT_TSS_CAZADORA_B4,tss_cazadora_b[3])

    //hasta aca solo agregue las bases en los descriptores de tss, en la gdt

    tss_idle_inicializar();    

    tss_saltadora_inicializar(&tss_saltadora_a);
    cargar_cr3_pilas(&tss_saltadora_a,1);
    tss_cazadora_inicializar(&tss_cazadora_a[0]);
    cargar_cr3_pilas(&tss_cazadora_a[0],2);
    tss_cazadora_inicializar(&tss_cazadora_a[1]);
    cargar_cr3_pilas(&tss_cazadora_a[1],3);
    tss_cazadora_inicializar(&tss_cazadora_a[2]);
    cargar_cr3_pilas(&tss_cazadora_a[2],4);
    tss_cazadora_inicializar(&tss_cazadora_a[3]);
    cargar_cr3_pilas(&tss_cazadora_a[3],5);


    tss_saltadora_inicializar(&tss_saltadora_b);
    cargar_cr3_pilas(&tss_saltadora_b,6);
    tss_cazadora_inicializar(&tss_cazadora_b[0]);
    cargar_cr3_pilas(&tss_cazadora_b[0],7);
    tss_cazadora_inicializar(&tss_cazadora_b[1]);
    cargar_cr3_pilas(&tss_cazadora_b[1],8);
    tss_cazadora_inicializar(&tss_cazadora_b[2]);
    cargar_cr3_pilas(&tss_cazadora_b[2],9);
    tss_cazadora_inicializar(&tss_cazadora_b[3]);
    cargar_cr3_pilas(&tss_cazadora_b[3],10);


}
