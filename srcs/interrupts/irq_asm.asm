; Declare the external symbol irq_handler
extern irq_handler

; Define a macro named IRQ with two parameters
%macro IRQ 2
global irq%1                ; Declare the symbol irq%1 as global
irq%1:                      ; Start of the IRQ handler
    cli                     ; Clear interrupts

    ; Push 0 and the second parameter onto the stack
    push byte 0
    push byte %2

    ; Jump to the irq_common_stub
    jmp irq_common_stub
%endmacro

; Define IRQ handlers for IRQs 0 to 15
IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

; Common IRQ handler stub
irq_common_stub:
    pusha               ; Pushes the values of edi,esi,ebp,esp,ebx,edx,ecx,eax
    mov ax, ds          ; Load the data segment descriptor into ax
    push eax            ; Push the data segment descriptor onto the stack
    mov ax, 0x10        ; Load 0x10 into ax, which is the code segment descriptor
    mov ds, ax          ; Load ds with 0x10
    mov es, ax          ; Load es with 0x10
    mov fs, ax          ; Load fs with 0x10
    mov gs, ax          ; Load gs with 0x10
    call irq_handler    ; Call the irq_handler function
    pop ebx             ; Restore the original data segment descriptor
    mov ds, bx          ; Restore ds with the original value
    mov es, bx          ; Restore es with the original value
    mov fs, bx          ; Restore fs with the original value
    mov gs, bx          ; Restore gs with the original value
    popa                ; Pop the values of edi,esi,ebp,esp,ebx,edx,ecx,eax
    add esp, 8          ; Clean up the pushed error code and pushed ISR number
    sti                 ; Set interrupts
    iret                ; Return from interrupt, pops CS, EIP, EFLAGS, SS, and ESP
