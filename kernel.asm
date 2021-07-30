; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"

; Defines

%define GDT_IDX_CODIGO_0 20
%define GDT_IDX_DATOS_0  22
%define GDT_TSS_INICIAL  25
%define GDT_TSS_IDLE  26
%define char 'e'
%define greenScreen (0x22)
%define blackScreen (0x00)
%define blanco (0x0F)   

extern GDT_DESC
extern IDT_DESC
extern idt_inicializar
extern resetear_pic
extern habilitar_pic
extern mmu_inicializar
extern mmu_inicializar_dir_kernel
extern iniciar_pantalla 
extern tss_inicializar
extern mmu_inicializar_tarea
extern mmu_inicializar_tareas
extern scheduler_inicializar
extern game_inicializar

global start


;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

offset: dd 0
selector: dw 0

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    cli

    ; Cambiar modo de video a 80 X 50
    mov ax, 0003h
    int 10h ; set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h ; load 8x8 font

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0
    
    ; Habilitar A20

    call habilitar_A20
    
    ; Cargar la GDT

    LGDT [GDT_DESC] ; (investigar)

    ; Setear el bit PE del registro CR0
    xchg bx, bx

    mov eax,cr0
    or eax,1
    mov cr0,eax     ; Manzana

    ; Saltar a modo protegido
    jmp (GDT_IDX_CODIGO_0 << 3):modoprotegido

BITS 32
    modoprotegido:

    ; Establecer selectores de segmentos

    mov ax ,(GDT_IDX_DATOS_0 << 3)
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov gs, ax


    ; Establecer la base de la pila

    mov esp, 0x27000
    mov ebp, esp

    ; Imprimir mensaje de bienvenida (falta esto)

    imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 0, 0

    inicializar: ;lo puse, porque sino quedaba la etiqueta del macro de arriba cuando debuggeabas

    ; Inicializar pantalla
    call iniciar_pantalla
    
    ; Inicializar el manejador de memoria
    call mmu_inicializar
    call mmu_inicializar_tareas   

    ; Inicializar el directorio de paginas    
    call mmu_inicializar_dir_kernel 

    ; Cargar directorio de paginas
    mov eax, 0x27000
    mov cr3, eax    

    ; Habilitar paginacion 
    ; breakpoint
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax

    ; Inicializar tss

    call tss_inicializar

    ; Inicializar el scheduler

    call scheduler_inicializar

    ; Inicializar la IDT

    call idt_inicializar
    

    ; Cargar IDT
    lidt [IDT_DESC]

    xchg bx, bx
    ;mov [0xffffffffffffffff], eax
    ; Configurar controlador de interrupciones

    call resetear_pic

    call habilitar_pic

    ; Cargar tarea inicial

    mov ax, (GDT_TSS_INICIAL << 3)
    ltr ax

    ; Habilitar interrupciones

    sti

    ;Inicializar juego

    call game_inicializar

    ; Saltar a la primera tarea: Idle

    jmp (GDT_TSS_IDLE << 3):0

    ; Ciclar infinitamente (por si algo sale mal...)
    xchg bx, bx 

    int 0x42

    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
