SOURCES=boot.o kernel_main.o string.o term.o util.o
CFLAGS=-nostdlib -ffreestanding -fno-stack-protector -std=gnu99 -O2
all: $(SOURCES)
	ld $(SOURCES) -T linker.ld -o bootImage.bin
clean:
	rm *.o -f
	rm bootImage.bin -f
install: all
	cp bootImage.bin /boot/project_gamma
