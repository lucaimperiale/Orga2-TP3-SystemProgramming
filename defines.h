/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Bool */
/* -------------------------------------------------------------------------- */
#define TRUE                    0x00000001
#define FALSE                   0x00000000
#define ERROR                   1
typedef _Bool bool;
#define true 0x01
#define false 0x00

/* Atributos paginas */
/* -------------------------------------------------------------------------- */
#define PAG_P                   0x00000001
#define PAG_R                   0x00000000
#define PAG_RW                  0x00000002
#define PAG_S                   0x00000000
#define PAG_US                  0x00000004

/* Misc */
/* -------------------------------------------------------------------------- */
#define MAX_VIDAS               5

/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT 40

#define GDT_IDX_NULL_DESC           0
#define GDT_IDX_CODIGO_0			20
#define GDT_IDX_CODIGO_3			21
#define GDT_IDX_DATOS_0				22
#define GDT_IDX_DATOS_3				23
#define GDT_IDX_VIDEO				24
#define GDT_TSS_INICIAL				25
#define GDT_TSS_IDLE				26
#define GDT_TSS_SALTADORA_A			27
#define GDT_TSS_SALTADORA_B		    28
#define GDT_TSS_CAZADORA_A1			29
#define GDT_TSS_CAZADORA_A2			30
#define GDT_TSS_CAZADORA_A3			31
#define GDT_TSS_CAZADORA_A4			32
#define GDT_TSS_CAZADORA_B1			33
#define GDT_TSS_CAZADORA_B2			34
#define GDT_TSS_CAZADORA_B3			35
#define GDT_TSS_CAZADORA_B4			36

/* Offsets en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_OFF_NULL_DESC           (GDT_IDX_NULL_DESC      << 3)
#define GDT_OFF_CODIGO_0			(GDT_IDX_CODIGO_0 		<< 3)
#define GDT_OFF_CODIGO_3			(GDT_IDX_CODIGO_3 		<< 3)
#define GDT_OFF_DATOS_0				(GDT_IDX_DATOS_0		<< 3)
#define GDT_OFF_DATOS_3				(GDT_IDX_DATOS_3		<< 3)
#define GDT_OFF_INICIAL				(GDT_OFF_INICIAL		<< 3)
#define GDT_OFF_IDLE				(GDT_TSS_IDLE			<< 3)


/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */
#define BOOTSECTOR              0x00001000 /* direccion fisica de comienzo del bootsector (copiado) */
#define KERNEL                  0x00001200 /* direccion fisica de comienzo del kernel */
#define VIDEO                   0x000B8000 /* direccion fisica del buffer de video */


#define TASK_A_SALTADORA_DIR	0X10000
#define TASK_A_CAZADORA_DIR		0X11000
#define TASK_B_SALTADORA_DIR	0X12000
#define TASK_B_CAZADORA_DIR		0x13000
#define TASK_IDLE_DIR			0x14000



#endif  /* !__DEFINES_H__ */
