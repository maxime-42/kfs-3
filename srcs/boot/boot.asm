section .multiboot
	dd 0x1BADB002	; Magic number
	dd 0x0			; Flags
	dd - (0x1BADB002 + 0x0)	; Checksum

extern kmain

global load_gdt
global _start

; global global syscalls
; test_syscalls:

;     mov eax, 2 ; Command print
;     int 0x80
;     ret
	

load_gdt:
	mov eax, [esp + 4]
	lgdt [eax]

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov ss, ax
  
	mov ax, 0x18
	mov gs, ax

	ret

_start:
	call kmain
	hlt

section .bss
resb 8192			; 8KB for stack
stack_space: