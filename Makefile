GREY        =   \033[030m
RED         =   \033[031m
GREEN       =   \033[032m
YELLOW      =   \033[033m
BLUE        =   \033[034m
MAGENTA     =   \033[035m
CYAN        =   \033[036m
BOLD        =   \033[1m
RESET       =   \033[0m

LINKER      = linker.ld  # Define linker script file

LOG_FILE = output.log


TARGET      = myos
ISO         = $(TARGET).iso
KERNEL_OUT  = myos.bin
OBJ_DIR     = obj

FLAGS		= -m32 -nostdlib -nodefaultlibs -fno-builtin -fno-exceptions -fno-stack-protector -Wall -Wextra -g3  -I include/ 
GRUB_CFG    = grub.cfg
BOOT        = boot.asm
SRC_ASM     = $(wildcard srcs/**/*.asm) $(wildcard srcs/*.asm)
SRC_C       = $(wildcard srcs/**/*.c) $(wildcard srcs/*.c)
OBJ_ASM     = $(patsubst srcs/%.asm,$(OBJ_DIR)/%.o,$(SRC_ASM))
OBJ_C       = $(patsubst srcs/%.c,$(OBJ_DIR)/%.o,$(SRC_C))
OBJ         = $(OBJ_ASM) $(OBJ_C)

# **************************************************************************** #
# 📖 RULES
# **************************************************************************** #


all: build

build: fclean $(OBJ_DIR) $(KERNEL_OUT)
	@printf "$(BOLD)$(GREEN)[✓] KERNEL BUILD DONE$(RESET)"
	@make verify-multiboot
	@make build-iso

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@gcc -m32 -ffreestanding ${FLAGS} -c $< -o $@

$(OBJ_DIR)/%.o: srcs/%.asm
	@mkdir -p $(dir $@)
	@nasm -f elf32 $< -o $@

$(KERNEL_OUT): $(OBJ)
	@ld -m elf_i386 -T ${LINKER} -o ${KERNEL_OUT} $(OBJ)
	@printf "$(BOLD)$(GREEN)[✓] KERNEL LINK DONE$(RESET)"

verify-multiboot:
	@if grub-file --is-x86-multiboot ${KERNEL_OUT}; then \
		printf "$(BOLD)$(GREEN)[✓] Multiboot header is valid$(RESET)"; \
	else \
		printf "$(BOLD)$(RED)[✗] Mufltiboot header is not valid$(RESET)"; \
		exit 1; \
	fi

build-iso:
	@mkdir -p isodir/boot/grub
	@cp ${KERNEL_OUT} isodir/boot/${TARGET}.bin
	@cp ${GRUB_CFG} isodir/boot/grub/grub.cfg
	@grub-mkrescue /usr/lib/grub/i386-pc -o myos.iso isodir
	@printf "$(BOLD)$(GREEN)[✓] ISO BUILD DONE$(RESET)"

clean:
	@rm -rf $(OBJ_DIR) $(ISO) $(LOG_FILE)
	@printf "$(BOLD)$(RED)[♻︎] DELETE KERNEL DONE$(RESET)"	

fclean: clean
	@rm -rf isodir ${KERNEL_OUT}
	@clear
	@printf "$(BOLD)$(RED)[♻︎] DELETE BUILD/ DONE$(RESET)"

qemu:
	@qemu-system-i386 -cdrom ${ISO}  -serial file:$(LOG_FILE)

qemu-no-iso:
	@qemu-system-i386 -kernel ${KERNEL_OUT}  -enable-kvm   -serial file:$(LOG_FILE)

# .PHONY: all build fclean clean qemu qemu-no-iso
