#include "debug.h"
#include "defines.h"
#include "screen.h"
#include "i386.h"
#include "colors.h"
#include "mmu.h"
#include "idt.h"
#include "tss.h"
#include "game.h"

bool debugOpen = false;
bool debugMode = false;
const ca screenBackupDir[30*36];



void controlDebugMode(){
	if(debugMode && debugOpen){
		closeDebug();
	}else{
		debugMode = !debugMode;
		if(!debugMode){
			screen_drawBox(2,0,1,15,' ',C_BG_BLACK | C_FG_BLACK); //borro el mensaje de modo debug
		}
	}
}

void closeDebug(){
	debugOpen = false;
	// zapato
	// debugMode = false;
	// screen_drawBox(2,0,1,15,' ',C_BG_BLACK | C_FG_BLACK); //borro el mensaje de modo debug
	ca (*screen)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
	ca* backup = (ca*) screenBackupDir;
	int x, y, i = 0;
	for (y = 7; y < 45; y++) {
		for (x = 24; x < 54; x++, i++)
				screen[y][x] = backup[i];
	}
}

void backupScreen(){
	ca (*screen)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
	ca* backup = (ca*) screenBackupDir;
	int x, y, i = 0;
	for (y = 7; y < 45; y++){
		for (x = 24; x < 54; x++, i++)
			backup[i] = screen[y][x];
	}
}

void debug(uint32_t cr0, uint32_t cr2, uint32_t cr3, 
						uint32_t cr4, uint8_t inter, 
						uint16_t ss, uint16_t ds, uint16_t es,
						uint16_t fs, uint16_t gs, uint32_t edi,
						uint32_t esi, uint32_t ebp, 
						uint32_t esp, uint32_t ebx,
						uint32_t edx, uint32_t ecx,
						uint32_t eax, uint32_t eip,
						uint16_t cs, uint32_t eflags){

	debugOpen = true;		
	backupScreen();
	printInterrupcion((uint32_t) inter);
	int x, y, i;
	for (y = 8; y < 43; y++){
		for (x = 25; x < 53; x++)
			screen_pintar(0, C_BG_LIGHT_GREY, y, x);
	}
	for (y = 7; y < 44; y++){
		screen_pintar(0, C_BG_BLACK, y, 24);
		screen_pintar(0, C_BG_BLACK, y, 53);
	}
	for (x = 25; x < 53; x++){
		screen_pintar(0, C_BG_BLACK, 7, x);
		screen_pintar(0, C_BG_BLACK, 43, x);
	}
	print_char("Interruption number:", 26, 9, C_FG_BLACK | C_BG_LIGHT_GREY);
	print_dec(inter, 4, 47, 9, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("eax", 26, 11, C_BG_LIGHT_GREY);
	print_hex(eax, 8, 30, 11, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("ebx", 26, 13, C_BG_LIGHT_GREY);
	print_hex(ebx, 8, 30, 13, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("ecx", 26, 15, C_BG_LIGHT_GREY);
	print_hex(ecx, 8, 30, 15, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("edx", 26, 17, C_BG_LIGHT_GREY);
	print_hex(edx, 8, 30, 17, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("esi", 26, 19, C_BG_LIGHT_GREY);
	print_hex(esi, 8, 30, 19, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("edi", 26, 21, C_BG_LIGHT_GREY);
	print_hex(edi, 8, 30, 21, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("ebp", 26, 23, C_BG_LIGHT_GREY);
	print_hex(ebp, 8, 30, 23, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("esp", 26, 25, C_BG_LIGHT_GREY);
	print_hex(esp, 8, 30, 25, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("eip", 26, 27, C_BG_LIGHT_GREY);
	print_hex(eip, 8, 30, 27, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("cs", 27, 29, C_BG_LIGHT_GREY);
	print_hex(cs, 4, 30, 29, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("ds", 27, 31, C_BG_LIGHT_GREY);
	print_hex(ds, 4, 30, 31, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("es", 27, 33, C_BG_LIGHT_GREY);
	print_hex(es, 4, 30, 33, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("fs", 27, 35, C_BG_LIGHT_GREY);
	print_hex(fs, 4, 30, 35, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("gs", 27, 37, C_BG_LIGHT_GREY);
	print_hex(gs, 4, 30, 37, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("ss", 27, 39, C_BG_LIGHT_GREY);
	print_hex(ss, 4, 30, 39, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("eflags", 31, 41, C_BG_LIGHT_GREY);
	print_hex(eflags, 8, 38, 41, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("cr0", 40, 11, C_BG_LIGHT_GREY);
	print_hex(cr0, 8, 44, 11, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("cr2", 40, 13, C_BG_LIGHT_GREY);
	print_hex(cr2, 8, 44, 13, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("cr3", 40, 15, C_BG_LIGHT_GREY);
	print_hex(cr3, 8, 44, 15, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("cr4", 40, 17, C_BG_LIGHT_GREY);
	print_hex(cr4, 8, 44, 17, C_FG_WHITE | C_BG_LIGHT_GREY);
	print_char("stack", 40, 19, C_BG_LIGHT_GREY);
	unsigned int* stack = (unsigned int*) esp;
	for(i = 0; stack < (unsigned int*) ebp && i < 5; i++, stack++)
		print_hex(*stack, 8, 25+16, 7+20+2+i, C_FG_WHITE | C_BG_LIGHT_GREY);
}