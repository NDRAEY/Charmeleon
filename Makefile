include ./defs.mk

SOURCES = $(wildcard src/*.c)
	  
OBJS = temps/main.o \
       temps/font.o \
       temps/font_parse.o \
       temps/string.o \
       temps/random.o \
       temps/ports.o \
       temps/rtc.o 
       
IMAGE = image.c
IMAGE_PNG = agumon.png
IMAGE_OBJ = temps/image.o

ISO = total.iso

ASM = $(wildcard src/*.s)
ASMOBJS = temps/boot.o

TARGET = build/main.bin

all: $(TARGET)
	@mkdir build || true
	@mkdir temps || true
	#setup
	@mkdir build/boot/grub/ -p || true
	@cp src/grub.cfg build/boot/grub/grub.cfg
	@echo "XORRISO [GRUB-MKDRESCUE]" $(ISO)
	@grub-mkrescue build/ -o $(ISO)	
	qemu-system-x86_64 -rtc base=localtime -m 150M -s -cdrom $(ISO) -serial stdio

$(IMAGE_OBJ): $(IMAGE)
	@echo "IMAGE" $@
	@$(PREFIX)gcc $(CFLAGS) $(IMAGE) -o $@

$(IMAGE): $(IMAGE_PNG)
	@echo "IMAGE2C" $@
	@python3 src/png2charmeleon.py $< > $(IMAGE)

$(ASMOBJS): temps/%.o : src/%.s
	@echo "ASM" $@ $<
	@as --32 $< -o $@

$(OBJS): temps/%.o : src/%.c
	@echo "CC" $@ $<
	@$(PREFIX)gcc $(CFLAGS) $< -o $@

$(TARGET): $(ASMOBJS) $(IMAGE_OBJ) $(OBJS)
	@echo "LD" $(TARGET)
	@$(PREFIX)ld $(LDFLAGS) $(ASMOBJS) $(IMAGE_OBJ) $(OBJS) -o $(TARGET)

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
