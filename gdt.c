/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#include "gdt.h"


#define tss(nombre) [nombre] = (gdt_entry) {\
        (uint16_t)    0x0067,         /* limit[0:15]  */\
        (uint16_t)    0x0000,         /* base[0:15]   */\
        (uint8_t)     0x00,           /* base   [23:16]  */\
        (uint8_t)     0x09,           /* type         */\
        (uint8_t)     0x00,           /* s            */\
        (uint8_t)     0x03,           /* dpl          */\
        (uint8_t)     0x01,           /* p            */\
        (uint8_t)     0x00,           /* limit[16:19] */\
        (uint8_t)     0x01,           /* avl          */\
        (uint8_t)     0x00,           /* l            */\
        (uint8_t)     0x00,           /* db           */\
        (uint8_t)     0x00,           /* g            */\
        (uint8_t)     0x00,           /* base[31:24]  */\
    }


gdt_entry gdt[GDT_COUNT] = {
    /* Descriptor nulo*/
    /* Offset = 0x00 */
    [GDT_IDX_NULL_DESC] = (gdt_entry) {
        (uint16_t)    0x0000,         /* limit[0:15]  */
        (uint16_t)    0x0000,         /* base[0:15]   */
        (uint8_t)     0x00,           /* base[23:16]  */
        (uint8_t)     0x00,           /* type         */
        (uint8_t)     0x00,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x00,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */    
        (uint8_t)     0x00,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     0x00,           /* base[31:24]  */
    },

        [GDT_IDX_CODIGO_0] = (gdt_entry) {
        (uint16_t)    0x39ff,         /* limit[0:15]  */
        (uint16_t)    0x0000,         /* base[0:15]   */
        (uint8_t)     0x00,           /* base[23:16]  */
        (uint8_t)     0x0A,           /* type         */
        (uint8_t)     0x01,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x01,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x01,           /* g            */
        (uint8_t)     0x00,           /* base[31:24]  */
    },

        [GDT_IDX_CODIGO_3] = (gdt_entry) {
        (uint16_t)    0x39ff,         /* limit[0:15]  */
        (uint16_t)    0x0000,         /* base[0:15]   */
        (uint8_t)     0x00,           /* base[23:16]  */
        (uint8_t)     0x0A,           /* type         */
        (uint8_t)     0x01,           /* s            */
        (uint8_t)     0x03,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x01,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x01,           /* g            */
        (uint8_t)     0x00,           /* base[31:24]  */
    },

        [GDT_IDX_DATOS_0] = (gdt_entry) {
        (uint16_t)    0x39ff,         /* limit[0:15]  */
        (uint16_t)    0x0000,         /* base[0:15]   */
        (uint8_t)     0x00,           /* base[23:16]  */
        (uint8_t)     0x02,           /* type         */
        (uint8_t)     0x01,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x01,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x01,           /* g            */
        (uint8_t)     0x00,           /* base[31:24]  */
    },

        [GDT_IDX_DATOS_3] = (gdt_entry) {
        (uint16_t)    0x39ff,         /* limit[0:15]  */
        (uint16_t)    0x0000,         /* base[0:15]   */    
        (uint8_t)     0x00,           /* base[23:16]  */
        (uint8_t)     0x02,           /* type         */
        (uint8_t)     0x01,           /* s            */
        (uint8_t)     0x03,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x01,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x01,           /* db           */
        (uint8_t)     0x01,           /* g            */
        (uint8_t)     0x00,           /* base[31:24]  */
    },
        [GDT_IDX_VIDEO] = (gdt_entry) {
        (uint16_t)    0x0FFF,         /* limit[0:15]  */
        (uint16_t)    0x8000,         /* base[0:15]   */
        (uint8_t)     0x0B,           /* base[23:16]  */
        (uint8_t)     0x02,           /* type         */
        (uint8_t)     0x01,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x01,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x00,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     0x00,           /* base[31:24]  */
    },

    tss(GDT_TSS_INICIAL),
    tss(GDT_TSS_IDLE),
    tss(GDT_TSS_SALTADORA_A),
    tss(GDT_TSS_SALTADORA_B),
    tss(GDT_TSS_CAZADORA_A1),
    tss(GDT_TSS_CAZADORA_A2),
    tss(GDT_TSS_CAZADORA_A3),
    tss(GDT_TSS_CAZADORA_A4),
    tss(GDT_TSS_CAZADORA_B1),
    tss(GDT_TSS_CAZADORA_B2),
    tss(GDT_TSS_CAZADORA_B3),
    tss(GDT_TSS_CAZADORA_B4)

};


gdt_descriptor GDT_DESC = {
    sizeof(gdt) - 1,        // preguntar
    (uint32_t) &gdt
};
