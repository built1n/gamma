all:
	i586-elf-as boot.s -o boot.o
	i586-elf-gcc kernel_main.c -o kernel_main.o -O2 -ffreestanding -c -std=gnu99
	i586-elf-gcc term.c -o term.o -O2 -ffreestanding -c -std=gnu99
	i586-elf-gcc string.c -o string.o -O2 -ffreestanding -c -std=gnu99
	i586-elf-gcc -T linker.ld -o bootImage.bin  -ffreestanding -nostdlib  -lgcc boot.o kernel_main.o term.o string.o
