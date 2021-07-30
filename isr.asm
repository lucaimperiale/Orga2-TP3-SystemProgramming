; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"
extern controlDebugMode

%define GDT_TSS_IDLE  26

BITS 32

extern screen_drawBox
;; PIC
extern fin_intr_pic1
extern printInterrupcion
extern interrupcionTeclado

;; Sched
extern sched_proximoIndice
extern syscall

;;Juego
extern actualizarPantalla
extern actualizarScheduler
extern actualizarEipPila
extern game_numero
extern game_escribir
extern game_leer
extern scheduler
extern imprimirEscritura
extern imprimirLectura
extern verificarEntradas
extern debugOpen
extern debugMode
extern debug
extern hasErrorCode
extern llamoUnaSaltadora


;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1

_isr%1:
    pushad
    push %1
    call hasErrorCode
    cmp eax, 1
    pop ebx; pop %1
    popad
    jne checkDebug%1
    add esp, 4 ; Saco error code
    checkDebug%1:
    cmp byte [debugOpen], 1
    je .actualizarScheduler%1
    cmp byte [debugMode], 0
    je .doNotOpenDebug%1
    pushad
    push gs
    push fs
    push es
    push ds
    push ss
    push %1
    mov eax, cr4
    push eax
    mov eax, cr3
    push eax
    mov eax, cr2
    push eax
    mov eax, cr0
    push eax
    call debug
    add esp, 40
    popad
    jmp .actualizarScheduler%1

    .doNotOpenDebug%1:
    mov eax, %1
    push eax
    call printInterrupcion
    add esp,4

    .actualizarScheduler%1:
    call actualizarScheduler
    cmp eax,1
    je esSaltadora%1


    .jmpAIdle%1:
    ; si cazadora:
    mov ax,(GDT_TSS_IDLE << 3)
    mov [selector], ax
    jmp far [offset]
    ; si saltadora;
    ; tocar en la pila el esp, el eip
    
    esSaltadora%1:
    ;breakpoint
    push esp
    call actualizarEipPila

    ; eip de la pila = 0x8000000
    ; esp de la pila = 0x8001000
    ; para el iret

    add esp,4

    mov ax,(GDT_TSS_IDLE << 3)
    mov [selector], ax
    jmp far [offset]

    fin%1:
    iret 


%endmacro

;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler
isrnumero:           dd 0x00000000
isrClock:            db '|/-\'

offset: dd 0
selector: dw 0

sched_tarea_offset:     dd 0x00
sched_tarea_selector:   dw 0x00

;;
;; Rutina de atención de las EXCEPCIONES
;; -------------------------------------------------------------------------- ;;
ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19
;;
;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;

GLOBAL _isr32
_isr32:
    pushad    
    call fin_intr_pic1

    call proximoReloj

    cmp byte [debugOpen], 1
    je .fin

    push dword [esp+32]
    call actualizarPantalla
    add esp,4
    call sched_proximoIndice

    mov [sched_tarea_selector],ax
    jmp far [sched_tarea_offset]
    .fin:
    popad
    iret

    


;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;

GLOBAL _isr33
_isr33:
    pushad
    call fin_intr_pic1
    xor eax,eax
    in al,0x60

    ;cmp al, 0x15
    ;jne interruptC
    ;breakpoint
    ;call controlDebugMode
    ;jmp teclado_end

    interruptC:
    push eax

    call interrupcionTeclado
    add esp,4
    
    teclado_end:
    popad
    iret
    



;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;

%define sysNumero   0x542
%define sysEscribir 0x824
%define sysLeer     0x7CA

GLOBAL _isr66
_isr66:

    pushad
    
    call llamoUnaSaltadora
    cmp eax,1
    popad
    je desalojar

    cmp eax,sysEscribir
    je escribir

    cmp eax,sysLeer
    je leer

    cmp eax,sysNumero
    je numero

    escribir:
    push ebx
    push ecx
    call verificarEntradas; dato,offset
    pop ecx
    pop ebx
    cmp eax,1
    je desalojar


    push ecx;dato
    push ebx;offset
    call game_escribir; offset, dato
    add esp,8
    push ebx
    call imprimirEscritura;offset
    add esp,4
    mov ax,(GDT_TSS_IDLE << 3)
    mov [selector],ax
    jmp far [offset]
    jmp end
    
    leer:
    push ebx
    push ecx
    call verificarEntradas; dato,offset
    pop ecx
    pop ebx
    cmp eax,1
    je desalojar

    

    push ecx
    push ebx
    call game_leer; offset, dato
    add esp,8
    push ebx
    call imprimirLectura;offset
    add esp,4
    jmp end

    numero:
    call game_numero
    mov ebx,eax
    jmp end

    desalojar:
    int 1 ;excepcion de procesador de debug

    end:
    iret

;; Funciones Auxiliares
;; -------------------------------------------------------------------------- ;;
proximoReloj:
        pushad
        inc DWORD [isrnumero]
        mov ebx, [isrnumero]
        cmp ebx, 0x4
        jl .ok
                mov DWORD [isrnumero], 0x0
                mov ebx, 0
        .ok:
                add ebx, isrClock
                imprimir_texto_mp ebx, 1, 0x0f, 49, 79
                popad
        ret
        

;;Funciones de Juego
;; -------------------------------------------------------------------------- ;;

GLOBAL terminarGame
terminarGame:
    cli
    hlt
    
