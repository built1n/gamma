SOURCES=boot.o kernel_main.o string.o term.o util.o gdt.o idt.o isr.o interrupt.o gdt-as.o
CFLAGS=-nostdlib -ffreestanding -fno-stack-protector -std=gnu99
ASFLAGS=-msyntax=att
all: $(SOURCES)
	ld $(SOURCES) -T linker.ld -o bootImage.bin
clean:
	rm *.o -f
	rm bootImage.bin -f
	rm *~ -f
install: all
	cp bootImage.bin /boot/project_gamma
floppy-image: all
	touch floppyImage.img
	losetup /dev/loop0 floppyImage.img
	mount /dev/loop0 floppy_dir
	cp bootImage.bin floppy_dir/kernel
	losetup -d /dev/loop0
