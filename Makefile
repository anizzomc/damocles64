INC_PATH = include/
DIRECTIVES = -fno-builtin -nostartfiles -nostdlib -I $(INC_PATH)
FLAGS = -m64 -c -Wall -g
OBJ_PATH = obj/
TARGET = kernel.sys

#Aparentemente para que todo funcione, la funcion de entrada tiene que estar linkeditada
#al comienzo


all:
	nasm -f elf64 loader.asm -o loader.o
	nasm -f elf64 arch/interrupt.asm -o $(OBJ_PATH)interruptasm.o
	nasm -f elf64 asm/control.asm -o $(OBJ_PATH)controlasm.o
	gcc $(FLAGS) kernel64.c -o kernel64.o $(DIRECTIVES)
	gcc $(FLAGS) arch/control.c -o $(OBJ_PATH)control.o $(DIRECTIVES)
	gcc $(FLAGS) drivers/video.c -o $(OBJ_PATH)video.o $(DIRECTIVES)
	gcc $(FLAGS) lib/klib.c -o $(OBJ_PATH)klib.o $(DIRECTIVES)
	gcc $(FLAGS) lib/presentation.c -o $(OBJ_PATH)presentation.o $(DIRECTIVES)
	gcc $(FLAGS) lib/string.c -o $(OBJ_PATH)string.o $(DIRECTIVES)
	gcc $(FLAGS) arch/pagination.c -o $(OBJ_PATH)pagination.o $(DIRECTIVES)
	gcc $(FLAGS) arch/memory.c -o $(OBJ_PATH)memory.o $(DIRECTIVES)
#	gcc $(FLAGS) prog/demoPagination.c -o $(OBJ_PATH)demoPagination.o $(DIRECTIVES)
	gcc $(FLAGS) arch/interrupt.c -o $(OBJ_PATH)interrupt.o $(DIRECTIVES)
	gcc $(FLAGS) drivers/keyboard.c -o $(OBJ_PATH)keyboard.o $(DIRECTIVES)
	ld -melf_x86_64 -T kernel64.ld loader.o kernel64.o $(OBJ_PATH)*.o -o kernel64.sys
	mcopy -o kernel64.sys c:/ 
clean:
	rm *.o
	rm obj/*.o
			