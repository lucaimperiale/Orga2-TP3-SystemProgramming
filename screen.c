/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/
#include "debug.h"
#include "defines.h"
#include "screen.h"
#include "i386.h"
#define debug_scanCode 0x15



void interrupcionTeclado(uint8_t scanCode){

    uint8_t tabla [10][3] = {{'1','\0','\0'},
                            {'2','\0','\0'},
                            {'3','\0','\0'},
                            {'4','\0','\0'},
                            {'5','\0','\0'},
                            {'6','\0','\0'},
                            {'7','\0','\0'},
                            {'8','\0','\0'},
                            {'9','\0','\0'},
                            {'0','\0','\0'}};


    if(scanCode >1 && scanCode < 12){
        const uint8_t *p2 = tabla[scanCode-2];
        uint16_t att = 0x0F;
        print(p2,79,0,att);
    }
    if (scanCode == debug_scanCode){
        const char* st = "MODO DEBUG ON";
        print_char(st, 0, 2, C_FG_WHITE | C_BG_BLACK);
        controlDebugMode();
    }
    
}


void printInterrupcion(uint32_t interrupcion){

    uint8_t texto[] = "Ocurrio la interrupcion";
    uint8_t tabla [20][3] = {{'0','\0','\0'},
                            {'1','\0','\0'},
                            {'2','\0','\0'},
                            {'3','\0','\0'},
                            {'4','\0','\0'},
                            {'5','\0','\0'},
                            {'6','\0','\0'},
                            {'7','\0','\0'},
                            {'8','\0','\0'},
                            {'9','\0','\0'},
                            {'1','0','\0'},
                            {'1','1','\0'},
                            {'1','2','\0'},
                            {'1','3','\0'},
                            {'1','4','\0'},
                            {'1','5','\0'},
                            {'1','6','\0'},
                            {'1','7','\0'},
                            {'1','8','\0'},
                            {'1','9','\0'},
                                          };
    uint16_t att = 0x0F;
    const uint8_t *p = texto;

    print(p,0,0,att);

    if( interrupcion == 33){
        uint8_t t3[] = "33";
        const uint8_t *p3 = t3;
        print(p3,24,0,att);
        return;
    }


    const uint8_t *p2 = tabla[interrupcion];


    print(p2,24,0,att);

}


void print(const uint8_t* text, uint32_t x, uint32_t y, uint16_t attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    int32_t i;
    for (i = 0; text[i] != 0; i++) {
        p[y][x].c = (uint8_t) text[i];
        p[y][x].a = (uint8_t) attr;
        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }
}

void print_char(const char* text, uint32_t x, uint32_t y, uint16_t attr){
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    int32_t i;
    for (i = 0; text[i] != 0; i++) {
        p[y][x].c = (uint8_t) text[i];
        p[y][x].a = (uint8_t) attr;
        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }
}

void print_dec(uint32_t numero, uint32_t size, uint32_t x, uint32_t y, uint16_t attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    uint32_t i;
    uint8_t letras[16] = "0123456789";

    for(i = 0; i < size; i++) {
        uint32_t resto  = numero % 10;
        numero = numero / 10;
        p[y][x + size - i - 1].c = letras[resto];
        p[y][x + size - i - 1].a = attr;
    }
}

void imprimir_hexas_horizontal(uint32_t x, uint32_t y, uint16_t attr){
    uint32_t numero = 0;
    int32_t size = 1;
    while(numero < 32){
        print_hex(numero,size,x,y,attr);
        numero += 1;
        x += 1;
    }
}

void imprimir_hexas_vertical(uint32_t x, uint32_t y, uint16_t attr){
    uint32_t numero = 0;
    int32_t size = 1;
    while(numero < 32){
        print_hex(numero,size,x,y,attr);
        numero += 1;
        y += 1;
    }
}


void print_hex(uint32_t numero, int32_t size, uint32_t x, uint32_t y, uint16_t attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    int32_t i;
    uint8_t hexa[8];
    uint8_t letras[16] = "0123456789ABCDEF";
    hexa[0] = letras[ ( numero & 0x0000000F ) >> 0  ];
    hexa[1] = letras[ ( numero & 0x000000F0 ) >> 4  ];
    hexa[2] = letras[ ( numero & 0x00000F00 ) >> 8  ];
    hexa[3] = letras[ ( numero & 0x0000F000 ) >> 12 ];
    hexa[4] = letras[ ( numero & 0x000F0000 ) >> 16 ];
    hexa[5] = letras[ ( numero & 0x00F00000 ) >> 20 ];
    hexa[6] = letras[ ( numero & 0x0F000000 ) >> 24 ];
    hexa[7] = letras[ ( numero & 0xF0000000 ) >> 28 ];
    for(i = 0; i < size; i++) {
        p[y][x + size - i - 1].c = hexa[i];
        p[y][x + size - i - 1].a = attr;
    }
}

void screen_drawBox(uint32_t fInit,
                    uint32_t cInit,
                    uint32_t fSize,
                    uint32_t cSize,
                    uint8_t character,
                    uint8_t attr ) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
    uint32_t f;
    uint32_t c;
    for (f = fInit; f < fInit+fSize; f++) {
    for (c = cInit; c < cInit+cSize; c++) {
          p[f][c].c = character;
          p[f][c].a = attr;
    }}
}

void screen_pintar(unsigned char c, unsigned char color, uint8_t fila, uint8_t columna){
  ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
  p[fila][columna].c = c;
  p[fila][columna].a = color;
}

void iniciar_pantalla(){
    uint16_t blackScreen = 0x00;
    uint16_t greenScreen = 0x22;
    uint16_t letra_blanca = 0x0F;
    uint16_t bloqueAzul = 0x11;
    uint16_t bloqueRojo = 0x44;
    char e = 'e';


    screen_drawBox(0,0,50,80,e,blackScreen);
     //columna - fila
    imprimir_hexas_horizontal(5,5,letra_blanca);
    imprimir_hexas_horizontal(43,5,letra_blanca);
    imprimir_hexas_vertical(3,7,letra_blanca);
    imprimir_hexas_vertical(41,7,letra_blanca);
    screen_drawBox(7,5,32,32,e,greenScreen);
    screen_drawBox(7,43,32,32,e,greenScreen);

    uint8_t t2[] = "HP";
    const uint8_t *vida = t2;
    print(vida, 39, 43, letra_blanca);

    screen_drawBox(42,34,3,3,e,bloqueAzul);
    screen_drawBox(42,43,3,3,e,bloqueRojo);
    uint8_t t3[] = "0 1 2 3 4";
    const uint8_t *numeros = t3;
    uint8_t t4[] = "| | | | |";
    const uint8_t *simbolos = t4;
    
    
    print(numeros, 54, 42, letra_blanca);
    print(simbolos, 54,44, letra_blanca);
    
    print(numeros, 16, 42, letra_blanca);
    print(simbolos,16, 44, letra_blanca);

}



