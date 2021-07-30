/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "defines.h"

unsigned int proxima_pagina_libre_kernel;
unsigned int proxima_pagina_libre_tareas;


void mmu_inicializar() {
	proxima_pagina_libre_kernel = INICIO_PAGINAS_LIBRES_KERNEL;
}
void mmu_inicializar_tareas(){
	proxima_pagina_libre_tareas = INICIO_PAGINAS_LIBRES_TAREAS;
}
unsigned int mmu_proxima_pagina_fisica_libre_kernel(){
	unsigned int proxima_pagina_libre = proxima_pagina_libre_kernel;
	proxima_pagina_libre_kernel+= PAGE_SIZE;
	return proxima_pagina_libre;
}
	
unsigned int mmu_proxima_pagina_fisica_libre_tareas() {
	unsigned int pagina_libre_tarea = proxima_pagina_libre_tareas;
	proxima_pagina_libre_tareas += PAGE_SIZE;
	return pagina_libre_tarea;
}

void mmu_mapear_pagina(unsigned int dir_virtual, unsigned int dir_pd, unsigned int fisica, unsigned char u_s){
	unsigned int pd_index = (dir_virtual >> 22);
	unsigned int pt_index = (dir_virtual << 10) >> 22;
	pd_entry* pd =	(pd_entry*) dir_pd;
	if (pd[pd_index].p == 0) {
		pd[pd_index].base = mmu_proxima_pagina_fisica_libre_kernel()>> 12;
		pd[pd_index].p = 1;
		pd[pd_index].r_w = 1;
		pd[pd_index].u_s = u_s;
	}
	// invariante: pd[pd_index] esta definido
	pt_entry* pt = (pt_entry*) (pd[pd_index].base << 12);
	pt[pt_index].base = fisica >> 12;
	pt[pt_index].p = 1;
	pt[pt_index].r_w = 1;
	pt[pt_index].u_s = u_s;
	tlbflush();
}

void mmu_unmapear_pagina(unsigned int dir_virtual, unsigned int dir_pd){
	unsigned int pd_index = (dir_virtual >> 22);
	unsigned int pt_index = (dir_virtual << 10) >> 22;
	pd_entry* pd =	(pd_entry*) dir_pd;
	if (pd[pd_index].p == 1){
		pt_entry* pt = (pt_entry*) (pd[pd_index].base << 12);
		pt[pt_index].p = 0;
	}
}

void mmu_inicializar_dir_kernel(){
	pd_entry* pd = (pd_entry*) 0x27000;
	pd[0].p = 1;
	pd[0].r_w = 1;
	pd[0].u_s = 0;
	pd[0].base = 0x28000 >> 12;
	identity_mapping(0x00027000);
}


void identity_mapping(unsigned int dir_pd){
	int i;
	for (i = 0; i < 0x003FFFFF; i += PAGE_SIZE) {
		mmu_mapear_pagina(i, dir_pd, i, 0);
	}
}
unsigned int cr3[11];
unsigned int direcciones_tareas[11] = {
							TASK_IDLE_DIR,

							TASK_A_SALTADORA_DIR,
							TASK_A_CAZADORA_DIR,
							TASK_A_CAZADORA_DIR, 
							TASK_A_CAZADORA_DIR, 
							TASK_A_CAZADORA_DIR,

							TASK_B_SALTADORA_DIR, 
							TASK_B_CAZADORA_DIR, 
							TASK_B_CAZADORA_DIR, 
							TASK_B_CAZADORA_DIR, 
							TASK_B_CAZADORA_DIR};
	

unsigned int mmu_inicializar_tarea(int indice_tarea){

	//Mapeo kernel
	pd_entry* pd = (pd_entry*) mmu_proxima_pagina_fisica_libre_kernel();
	cr3[indice_tarea]=((unsigned int) pd >> 12) << 12;
	pd[0].p = 1;
	pd[0].r_w = 1;
	pd[0].u_s = 0;
	pt_entry* pt = (pt_entry*) mmu_proxima_pagina_fisica_libre_kernel();
	pd[0].base = ((unsigned int) pt) >> 12;
	identity_mapping((unsigned int)pd);
	//Mappeo codigo de tarea
	unsigned int dir_fisica = mmu_proxima_pagina_fisica_libre_tareas();
	mmu_mapear_pagina(0x08000000, (unsigned int)pd, dir_fisica, 1);

    mmu_mapear_pagina(dir_fisica, rcr3(), dir_fisica, 0);
	char* ptr_codigo = (char*) direcciones_tareas[indice_tarea];
	char* ptr_destino = (char*) dir_fisica;
	for(int k = 0; k < PAGE_SIZE; k++)
		ptr_destino[k] = ptr_codigo[k];
	mmu_unmapear_pagina(dir_fisica, rcr3());
	return cr3[indice_tarea];
}


void resetearTarea(int indice_tarea){
	unsigned int dir_fisica = mmu_proxima_pagina_fisica_libre_tareas();
	mmu_mapear_pagina(0x08000000, rcr3(), dir_fisica, 1);

    mmu_mapear_pagina(dir_fisica, rcr3(), dir_fisica, 0);
	char* ptr_codigo = (char*) direcciones_tareas[indice_tarea];
	char* ptr_destino = (char*) dir_fisica;
	for(int k = 0; k < PAGE_SIZE; k++)
		ptr_destino[k] = ptr_codigo[k];
	mmu_unmapear_pagina(dir_fisica, rcr3());
}