SOURCES=boot.o kernel_main.o string.o term.o util.o gdt.o idt.o isr.o interrupt.o gdt-as.o panic.o clock.o keyboard.o heap.o page.o frame.o io.o power.o
CFLAGS=-nostdlib -ffreestanding -fno-stack-protector -std=gnu99 -Wall -m32 -Iinclude
CC=gcc
#uncomment for MinGW GCC:
#CC=mingw32-gcc
ASFLAGS=-march=i686 --32
all: $(SOURCES)
	ld $(SOURCES) -T linker.ld -o bootImage.bin -melf_i386
clean:
	rm -rf isodir
	rm isoImage.iso -f
	rm *.o -f
	rm bootImage.bin -f
	rm *~ -f
	rm a.out -f
install: all
	cp bootImage.bin /boot/project_gamma
iso: all
	rm -rf isodir
	mkdir isodir
	mkdir isodir/boot
	mkdir isodir/boot/grub
cp bootImage.bin isodir/boot/project_gamma
cp iso_grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o isoImage.iso isodir
