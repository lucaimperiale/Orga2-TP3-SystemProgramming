/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"

int16_t ordenTareas [10] = {GDT_TSS_SALTADORA_A,
							GDT_TSS_SALTADORA_B,
							GDT_TSS_CAZADORA_A1,
							GDT_TSS_CAZADORA_B1,
							GDT_TSS_CAZADORA_A2,
							GDT_TSS_CAZADORA_B2,
							GDT_TSS_CAZADORA_A3,
							GDT_TSS_CAZADORA_B3,
							GDT_TSS_CAZADORA_A4,
							GDT_TSS_CAZADORA_B4};


sched scheduler;

void scheduler_inicializar(){
	scheduler.tareaActual = 19;
	for(int i =0; i<8 ; i++){
		scheduler.tareasDesalojadas[i] = 10;
	}
	for(int i=0;i<10;i++){
		scheduler.relojes[i][0] = '|';
	}

}

uint8_t actualizarScheduler(){

  uint8_t esSaltadora;

	if(scheduler.tareaActual == 0 || scheduler.tareaActual == 1){
		restarVida();
    esSaltadora = 1;
	}
	else{
		for(int i =0; i<8 ; i++){
			if(scheduler.tareasDesalojadas[i] == 10){
				scheduler.tareasDesalojadas[i] = scheduler.tareaActual;
				break;
			}
		}
		matarTareaPantalla();
    esSaltadora = 0;
	}

	int jugadorA = 0;
	int jugadorB = 0;

	for(int i=0; i<8;i++){
		if(scheduler.tareasDesalojadas[i] == 2 || scheduler.tareasDesalojadas[i] == 4 || scheduler.tareasDesalojadas[i] == 6 || scheduler.tareasDesalojadas[i] == 8 ){
			jugadorA++;
		}
		if(scheduler.tareasDesalojadas[i] == 3 || scheduler.tareasDesalojadas[i] == 5 || scheduler.tareasDesalojadas[i] == 7 || scheduler.tareasDesalojadas[i] == 9 ){
			jugadorB++;
		}
	}

	if(jugadorA >= 4){
		uint8_t t[] = "Perdio jugador A, por quedarse sin cazadoras";
		const uint8_t *perdio = t;
		print(perdio, 0, 1, 0x0F);
		terminarGame();
	}
	if(jugadorB >= 4){
		uint8_t t[] = "Perdio jugador B, por quedarse sin cazadoras";
		const uint8_t *perdio = t;
		print(perdio, 0, 1, 0x0F);
		terminarGame();
	}
  return esSaltadora;
}


int16_t sched_proximoIndice() {
  scheduler.tareaActual = (scheduler.tareaActual+1) % 10;
  for(int i =0; i<8 ; i++){
  	if(scheduler.tareaActual == scheduler.tareasDesalojadas[i]){
  		scheduler.tareaActual = (scheduler.tareaActual+1) % 10;
  	}
  }
  return (ordenTareas[scheduler.tareaActual] << 3 ) + 3;
}

void matarTareaPantalla(){
	uint16_t roja_fnegro = 0x04;

	uint8_t t[2] = "a";
	const uint8_t* p;

	switch(scheduler.tareaActual){
		case 2:
			t[0] = 'X';
    		p = t;
			print(p, 18,44, roja_fnegro);
			break;
		case 3:
			t[0] = 'X';
    		p = t;
			print(p, 56,44, roja_fnegro);
			break;
		case 4:
			t[0] = 'X';
    		p = t;
			print(p, 20,44, roja_fnegro);
			break;
		case 5:
			t[0] = 'X';
    		p = t;
			print(p, 58,44, roja_fnegro);
			break;
		case 6:
			t[0] = 'X';
    		p = t;
			print(p, 22,44, roja_fnegro);
			break;
		case 7:
			t[0] = 'X';
    		p = t;
			print(p, 60,44, roja_fnegro);
			break;
		case 8:
			t[0] = 'X';
    		p = t;
			print(p, 24,44, roja_fnegro);
			break;
		case 9:
			t[0] = 'X';
    		p = t;
			print(p, 62,44, roja_fnegro);
			break;
				
	}
}


void actualizarEipPila(uint32_t *pila){
	  * (pila) = 0x8000000;
	  * (pila+3) = 0x8000FFF;
}

uint8_t hasErrorCode(uint8_t excepcion){
	if(excepcion == 8 || excepcion == 10 || excepcion == 11 || excepcion == 12 || excepcion == 13 || excepcion == 14 || excepcion == 17)
		return 1;
	else
		return 0;
}