include ./defs.mk

SOURCES = $(wildcard src/*.c)
	  
OBJS = temps/main.o \
       temps/font.o \
       temps/font_parse.o \
       temps/string.o \
       temps/random.o \
       temps/ports.o \
       temps/irq.o \
       temps/pic.o \
       temps/memmgr.o \
       temps/rtc.o \
       temps/paging.o \
       temps/heap.o \
       temps/gfx.o \
       
IMAGE = image.c
IMAGE_PNG = agumon.png
IMAGE_OBJ = temps/image.o

ISO = total.iso

ASM = $(wildcard src/*.s)
ASMOBJS = temps/boot.o

NASM = $(wildcard src/*.asm)
NASMOBJS = temps/irq_.o

TARGET = build/main.bin

mkdir build || true
mkdir temps || true

all: $(TARGET)
	@mkdir build/boot/grub/ -p || true
	@cp src/grub.cfg build/boot/grub/grub.cfg
	@echo "XORRISO [GRUB-MKDRESCUE]" $(ISO)
	@grub-mkrescue build/ -o $(ISO)	
	qemu-system-x86_64 -rtc base=localtime -m 256M -s -cdrom $(ISO) -serial stdio

$(IMAGE_OBJ): $(IMAGE)
	@echo "IMAGE" $@
	@$(PREFIX)gcc $(CFLAGS) $(IMAGE) -o $@

$(IMAGE): $(IMAGE_PNG)
	@echo "IMAGE2C" $@
	@python3 src/png2charmeleon.py $< > $(IMAGE)

$(ASMOBJS): temps/%.o : src/%.s 
	@echo "ASM" $@ $<
	@as --32 $< -o $@

$(NASMOBJS): temps/%.o : src/%.asm
	@echo "NASM" $@ $<
	@nasm -felf32 $< -o $@

$(OBJS): temps/%.o : src/%.c
	@echo "CC" $@ $<
	@$(PREFIX)gcc -g $(CFLAGS) $< -o $@

$(TARGET): $(ASMOBJS) $(NASMOBJS) $(IMAGE_OBJ) $(OBJS)
	@echo "LD" $(TARGET)
	@$(PREFIX)ld $(LDFLAGS) $(ASMOBJS) $(NASMOBJS) $(IMAGE_OBJ) $(OBJS) -o $(TARGET)

clean:
	rm build/* -r || true
	rm temps/* -r || true
	rm total.iso || true
	rm image.c || true

clean_nototal:
	rm build/* -r || true
	rm temps/* -r || true

install:	
	sudo cp build/main.bin /boot/charmeleon.bin # On my machine, add entries to grub.cfg
