#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "screen.h"
#include "defines.h"

void controlDebugMode();
void closeDebug();
void backupScreen();
void debug(uint32_t cr0, uint32_t cr2, uint32_t cr3,
		    uint32_t cr4, uint8_t inter, uint16_t ss,
		    uint16_t ds, uint16_t es,
			uint16_t fs, uint16_t gs, uint32_t edi,
			uint32_t esi, uint32_t ebp, 
			uint32_t esp, uint32_t ebx,
			uint32_t edx, uint32_t ecx,
			uint32_t eax, uint32_t eip, 
			uint16_t cs, uint32_t eflags);
//bool debugOpen;
//bool debugMode;
#endif  /* !__DEBUG_H__ */