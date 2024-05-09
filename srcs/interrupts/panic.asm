global kpanic

disable :
	cli; Disable interrupts
	hlt; Halt the CPU


section .text

; Function to clean registers
clean_registers:
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx
    ret

; Function to trigger a kernel panic
kpanic:
    call clean_registers  ; Call the clean_registers function to clean the registers
.loop:
	call disable             ;
    jmp .loop             ; Loop indefinitely
