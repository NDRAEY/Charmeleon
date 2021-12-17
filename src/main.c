#include <stdint.h>
#include "multiboot.h"

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

multiboot_info_t *inf;

typedef struct {
	int x;
	int y;
	int w;
	int h;
} rect;

typedef struct {
	int x;
	int y;
	int w;
	int h;
	int color;
} rect_colored;

int pixidx(int x, int y){
	return inf->framebuffer_width*y+x;
}

int extpixidx(int x, int y, int w){
	return w*y+x;
}

void plot_pixel(uint32_t* fb,int x,int y,int color){
	fb[pixidx(x,y)]=color;
}

rect createrect(int x, int y, int w, int h) {
	rect r;
	r.x=x;
	r.y=y;
	r.w=w;
	r.h=h;
	return r;
}

rect_colored createrect_colored(int x, int y, int w, int h, int color) {
	rect_colored rk;
	rk.x=x;
	rk.y=y;
	rk.w=w;
	rk.h=h;
	rk.color = color;
	return rk;
}

void drawrect(rect_colored r, uint32_t* fb){
	int i,j;
	for(i=0; i<r.h; i++){
		for(j=0; j<r.w; j++){
			plot_pixel(fb,r.x+j,r.y+i,r.color);
		}
	}
}

int generate_rgb(char r, char g, char b){
	return (((r&0xff)<<16)|((g&0xff)<<8)|(b&0xff));
}

void imagedraw(char meleon[], uint32_t* fb, int width, int height, int startx, int starty){
	for(int i=0; i<height;i++){
		for(int j=0; j<width;j++) {
			int r = meleon[extpixidx(j*4,i,width*4)];
			int g = meleon[extpixidx(j*4,i,width*4)+1];
			int b = meleon[extpixidx(j*4,i,width*4)+2];
			int a = meleon[extpixidx(j*4,i,width*4)+3];
			plot_pixel(fb,j+startx,i+starty,generate_rgb(r,g,b));
		}
	}
}

// From auto-generated image.c
extern int someimage_width;
extern int someimage_height;
extern char someimage[];

void main(unsigned long magic, unsigned long addr) {
	inf = (multiboot_info_t*)addr;
	uint32_t *fb; fb = (uint32_t*)inf->framebuffer_addr;

	imagedraw(someimage, fb, someimage_width, someimage_height, 20, 20);
	while(1){}
}
