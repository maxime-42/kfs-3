; Declare the external symbol isr_handler
extern isr_handler

; Common ISR handler stub
isr_common_stub:
    pusha               ; Pushes the values of edi,esi,ebp,esp,ebx,edx,ecx,eax
    mov ax, ds          ; Load the data segment descriptor into ax
    push eax            ; Push the data segment descriptor onto the stack
    mov ax, 0x10        ; Load 0x10 into ax, which is the kernel data segment descriptor
    mov ds, ax          ; Load ds with 0x10
    mov es, ax          ; Load es with 0x10
    mov fs, ax          ; Load fs with 0x10
    mov gs, ax          ; Load gs with 0x10
    call isr_handler    ; Call the isr_handler function
    pop eax             ; Restore the original data segment descriptor
    mov ds, ax          ; Restore ds with the original value
    mov es, ax          ; Restore es with the original value
    mov fs, ax          ; Restore fs with the original value
    mov gs, ax          ; Restore gs with the original value
    popa                ; Pop the values of edi,esi,ebp,esp,ebx,edx,ecx,eax
    add esp, 8          ; Clean up the pushed error code and pushed ISR number
    sti                 ; Set interrupts
    iret                ; Return from interrupt, pops CS, EIP, EFLAGS, SS, and ESP

; Macro for isr function without error code
%macro ISR_NOERRCODE 1
global isr%1             ; Declare the symbol isr%1 as global

isr%1:                   ; Start of the ISR function
    cli                  ; Clear interrupts
    push byte 0          ; Push 0 onto the stack (error code)
    push byte %1         ; Push the ISR number onto the stack
    jmp isr_common_stub  ; Jump to the common ISR stub
%endmacro

; Macro for isr function with error code
%macro ISR_ERRCODE 1
global isr%1             ; Declare the symbol isr%1 as global

isr%1:                   ; Start of the ISR function
    cli                  ; Clear interrupts
    push byte %1         ; Push the error code onto the stack
    jmp isr_common_stub  ; Jump to the common ISR stub
%endmacro 

; Define ISR handlers for IRQs 0 to 31, 128, and 177
ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9 
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31
ISR_NOERRCODE 128
ISR_NOERRCODE 177
