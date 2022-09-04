i686-elf-as src/boot.s -o bin/boot.o

i686-elf-gcc -c src/kernel.c -o bin/kernel.o  -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c src/serial.c -o bin/serial.o  -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c src/terminal.c -o bin/terminal.o  -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c src/utils.c -o bin/utils.o  -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c src/gdt.c -o bin/gdt.o  -std=gnu99 -ffreestanding -O2 -Wall -Wextra
# i686-elf-gcc src/*.c -o bin/kernel.o bin/serial.o bin/utils.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra