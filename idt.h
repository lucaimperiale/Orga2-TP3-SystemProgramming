/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de las rutinas de atencion de interrupciones
*/

#ifndef __IDT_H__
#define __IDT_H__

#include "stdint.h"

/* Struct de descriptor de IDT */
typedef struct str_idt_descriptor {
    uint16_t idt_length;
    uint32_t idt_addr;
} __attribute__((__packed__)) idt_descriptor;

/* Struct de una entrada de la IDT */
typedef struct str_idt_entry_fld {
    uint16_t offset_0_15;
    uint16_t segsel;
    uint16_t attr;
    uint16_t offset_16_31;
} __attribute__((__packed__, aligned (8))) idt_entry;

extern idt_entry idt[];
extern idt_descriptor IDT_DESC;

void idt_inicializar();
extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr32();
extern void _isr33();
extern void _isr66();


#endif  /* !__IDT_H__ */
