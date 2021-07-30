/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"

game_t game;

void actualizarPantalla(uint32_t eip){

	for(int i=0;i<8;i++){
		if(scheduler.tareaActual == scheduler.tareasDesalojadas[i]){
			return;
		}
	}

	print_dec(game.vidasA,1,35,43,0x1F);
	print_dec(game.vidasB,1,44,43,0x4F);

	actualizarRelojes();


	if(eip<0x8000000){
		eip = 0;
	}else{
		eip = eip - 0x08000000;
	}
	eip = eip/4;

    if(scheduler.tareaActual == 0){
        screen_drawBox(7+game.eipAy,5+game.eipAx,1,1,' ',0x2F);

        game.eipAy = eip / 32;
        game.eipAx = eip - 32* game.eipAy;

        screen_drawBox(7+game.eipAy,5+game.eipAx,1,1,'O',0x1F);

    }
    if(scheduler.tareaActual == 1){
        screen_drawBox(7+game.eipBy,43+game.eipBx,1,1,' ',0x2F);

        game.eipBy = eip / 32;
        game.eipBx = eip - 32* game.eipBy;

        screen_drawBox(7+game.eipBy,43+game.eipBx,1,1,'O',0x4F);

    }
}


void actualizarRelojes(){

	avanzarReloj();
	uint16_t letra_blanca = 0x0F;

	uint8_t t[2] = "a";
	const uint8_t* p;

	switch(scheduler.tareaActual){
		case 0:
			t[0] = scheduler.relojes[scheduler.tareaActual][0];
    		p = t;
			print(p, 16,44, letra_blanca);
			break;
		case 1:
			t[0] = scheduler.relojes[scheduler.tareaActual][0];
    		p = t;
			print(p, 54,44, letra_blanca);
			break;
		case 2:
			t[0] = scheduler.relojes[scheduler.tareaActual][0];
    		p = t;
			print(p, 18,44, letra_blanca);
			break;
		case 3:
			t[0] = scheduler.relojes[scheduler.tareaActual][0];
    		p = t;
			print(p, 56,44, letra_blanca);
			break;
		case 4:
			t[0] = scheduler.relojes[scheduler.tareaActual][0];
    		p = t;
			print(p, 20,44, letra_blanca);
			break;
		case 5:
			t[0] = scheduler.relojes[scheduler.tareaActual][0];
    		p = t;
			print(p, 58,44, letra_blanca);
			break;
		case 6:
			t[0] = scheduler.relojes[scheduler.tareaActual][0];
    		p = t;
			print(p, 22,44, letra_blanca);
			break;
		case 7:
			t[0] = scheduler.relojes[scheduler.tareaActual][0];
    		p = t;
			print(p, 60,44, letra_blanca);
			break;
		case 8:
			t[0] = scheduler.relojes[scheduler.tareaActual][0];
    		p = t;
			print(p, 24,44, letra_blanca);
			break;
		case 9:
			t[0] = scheduler.relojes[scheduler.tareaActual][0];
    		p = t;
			print(p, 62,44, letra_blanca);
			break;
				
	}
}

void avanzarReloj(){
	switch(scheduler.relojes[scheduler.tareaActual][0]){
		case '|':
			 scheduler.relojes[scheduler.tareaActual][0] = '/';
			break;
		case '/':
			 scheduler.relojes[scheduler.tareaActual][0] = '-';
			break;
		case '-':
			 scheduler.relojes[scheduler.tareaActual][0] = '\\';
			break;
		case '\\':
			 scheduler.relojes[scheduler.tareaActual][0] = '|';
			break;
		}
}

void restarVida(){
	if(scheduler.tareaActual == 0){
		game.vidasA = game.vidasA -1;
		mmu_unmapear_pagina(0x8000000,rcr3());
		resetearTarea(1);
	}
	if(scheduler.tareaActual == 1){
		game.vidasB = game.vidasB -1;
		mmu_unmapear_pagina(0x8000000,rcr3());
		resetearTarea(6);
	}

	if(game.vidasA == 0){
		print_dec(0,1,35,43,0x1F);
		uint8_t t[] = "Perdio jugador A, por quedarse sin vidas";
    	const uint8_t *perdio = t;
    	print(perdio, 0, 0, 0x0F);
		terminarGame();
	}
	if(game.vidasB == 0){
		print_dec(0,1,44,43,0x4F);
		uint8_t t[] = "Perdio jugador B, por quedarse sin vidas";
    	const uint8_t *perdio = t;
    	print(perdio, 0, 0, 0x0F);
		terminarGame();
	}
}

void game_inicializar() {
	game.vidasA = MAX_VIDAS;
	game.vidasB = MAX_VIDAS;
	game.eipAx = 0;
	game.eipAy = 0;
	game.eipBx = 0;
	game.eipBy = 0;
}

uint32_t game_numero() {
	if( scheduler.tareaActual == 2 || scheduler.tareaActual == 3 ){
		return 1;
	}
	if( scheduler.tareaActual == 4 || scheduler.tareaActual == 5 ){
		return 2;
	}
	if( scheduler.tareaActual == 6 || scheduler.tareaActual == 7 ){
		return 3;	
	}
	else{
		return 4;
	}
}

void game_escribir(uint32_t direccion, uint32_t* dato) {
    pd_entry* pd;
    if(scheduler.tareaActual == 2 || scheduler.tareaActual == 4 || scheduler.tareaActual == 6 || scheduler.tareaActual == 8 ){
        pd = (pd_entry*) (uint32_t)tss_saltadora_b.cr3;
    }
       else{
        pd = (pd_entry*) (uint32_t)tss_saltadora_a.cr3;
    }
    uint32_t offset = direccion;
    direccion = direccion + 0x8000000;
    unsigned int pd_index = (direccion >> 22);
    unsigned int pt_index = (direccion << 10) >> 22;

    pt_entry* pt = (pt_entry*) (pd[pd_index].base << 12);
    uint32_t fisica = (uint32_t)(pt[pt_index].base << 12);

    fisica = fisica + ((direccion << 20) >> 20);

    mmu_mapear_pagina(0x7000000,rcr3(),fisica,1);

    uint32_t lineal = 0x7000000;

    lineal = lineal + offset;

    uint32_t* p = (uint32_t*)lineal;

    *p = *dato;

    mmu_unmapear_pagina(0x7000000,rcr3());
}

void game_leer(uint32_t direccion, uint32_t* dato) {

    pd_entry* pd;

    if(scheduler.tareaActual == 2 || scheduler.tareaActual == 4 || scheduler.tareaActual == 6 || scheduler.tareaActual == 8 ){
        pd = (pd_entry*) (uint32_t)tss_saltadora_b.cr3;
    }
       else{
        pd = (pd_entry*) (uint32_t)tss_saltadora_a.cr3;
       }
    uint32_t offset = direccion;
    direccion = direccion + 0x8000000;
    unsigned int pd_index = (direccion >> 22);
    unsigned int pt_index = (direccion << 10) >> 22;

    pt_entry* pt = (pt_entry*) (pd[pd_index].base << 12);
    uint32_t fisica = (uint32_t)(pt[pt_index].base << 12);

    fisica = fisica + ((direccion << 20) >> 20);


    mmu_mapear_pagina(0x7000000,rcr3(),fisica,1);

    uint32_t lineal = 0x7000000;

    lineal = lineal + offset;

    uint32_t* p = (uint32_t*)lineal;    

    *dato = *p;

    mmu_unmapear_pagina(0x7000000,rcr3());

}

void imprimirLectura(uint32_t offset){
	
	offset = offset/4;

	if(scheduler.tareaActual == 2 || scheduler.tareaActual == 4 || scheduler.tareaActual == 6 || scheduler.tareaActual == 8 ){

	    uint32_t offy = offset / 32;
	    uint32_t offx = offset - 32* offy;

    	screen_drawBox(7+offy,43+offx,1,1,' ',0x1F);
	}
	else{
		uint32_t offy = offset / 32;
	    uint32_t offx = offset - 32* offy;

    	screen_drawBox(7+offy,5+offx,1,1,' ',0x4F);
	}

}

void imprimirEscritura(uint32_t offset){
	offset = offset/4;
	if(scheduler.tareaActual == 2 || scheduler.tareaActual == 4 || scheduler.tareaActual == 6 || scheduler.tareaActual == 8 ){

	    uint32_t offy = offset / 32;
	    uint32_t offx = offset - 32* offy;

    	screen_drawBox(7+offy,43+offx,1,1,'X',0x1F);
	}
	else{
		
		uint32_t offy = offset / 32;
	    uint32_t offx = offset - 32* offy;

    	screen_drawBox(7+offy,5+offx,1,1,'X',0x4F);
	}
}

uint8_t verificarEntradas(uint32_t dato,uint32_t offset){
	uint8_t desalojar = 0;
	if(scheduler.tareaActual == 0 || scheduler.tareaActual == 1){
		desalojar = 1;	
	}

	if(dato > 0x80000FFF || dato < 0x8000000){
		desalojar = 1;
	}
	if(offset > 0xffc){
		desalojar = 1;
	}
	return desalojar;
}

uint8_t llamoUnaSaltadora(){
	if(scheduler.tareaActual == 0 || scheduler.tareaActual == 1){
		return 1;	
	}
	return 0;
}

	