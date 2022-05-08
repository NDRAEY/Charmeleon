#include "main.h"
#include "font.h"
#include "string.h"
#include "random.h"
#include "ports.h"
#include "rtc.h"
#include "memmgr.h"
#include "heap.h"
#include "defs.h"
#include "gfx.h"
#include "pci.h"

void serial_print(char *text){
	for(int i=0; i<strlen(text); i++){
		outb(0x3f8,text[i]);
	}
}

void main(unsigned long magic, unsigned long addr) {
	inf = (multiboot_info_t*)addr;
	fb = (uint32_t*)inf->framebuffer_addr;	

	serial_print("Initializing RTC...\n");
	rtc_init();
	serial_print("Initializing RAND...\n");
	rand_init();
	serial_print("Initializing HEAP...\n");
	kheap_init((void*)(32*M),(void*)(32*M+(32*1024)),(void*)(inf->mem_upper*1024)); //32MB

	serial_print("Initializing MEMORY MANAGER...\n");
	memmgr_init(inf->mem_upper*1024);
	serial_print("Initializing PCI...\n");
	pci_init();
	serial_print("Initializing GFX...\n");
	gfb = (uint32_t*)malloc((int)(inf->framebuffer_width*inf->framebuffer_height*sizeof(uint64_t)));
	serial_print("Initializinf GFX(2)...\n");
	gfx_init(gfb);
	serial_print("Initializing FONT...\n");
	font_init();
	serial_print("Next...\n");

	char num[16];

	rgb_color fill;
	fill.r = 220;
	fill.g = 35;
	fill.b = 0;

	char time[128];

	pci_dev_t ac97 = pci_get_device(0x0104, 0x0000, 4);
	if(!ac97.bits) {
		serial_print("[ERR] AC'97 not found!!!\n");
	}else{
		serial_print("[FOUND] Found device AC'97\n");
	}

	while(1){
		fillall(fill);
		imagedraw(someimage, someimage_width, someimage_height, 100, 100);
		drawtext("OH-LALA!!! Charmeleon is here!!! And Agumon too!!!\n(@charmeleon.ndraey)",8,10);
		drawtext("Agumon from DIGIMON",(720/2)+(int)(720/8), 78);
		itoa(rand(65536*2),num);
		drawtext(num,8,10+16+16);

		memset(time,0,128);
		gettimestr(time);
		drawtext(time,8,58);
		
		gfx_update(fb,gfb);
	}
}
