#include "gfx.h"
#include "main.h"
#include "string.h"
#include "multiboot.h"
#include <stdint.h>

static int gfbw;
static int gfbh;

int pixidx(int x, int y){
	return gfbw*y+x;
}

int extpixidx(int x, int y, int w){
	return w*y+x;
}

int getpix(int x, int y){
	return gfb[pixidx(x,y)];
}

rgb_color getpix_rgb(int x, int y){
	rgb_color rgb;
	int rgb_ = getpix(x,y);
	rgb.r = (rgb_ >> 16) & 0xFF;
	rgb.g = (rgb_ >> 8) & 0xFF;
	rgb.b = rgb_ & 0xFF;
	return rgb;
}

rgba_color getpix_rgba(int x, int y){
	rgba_color rgba;
	int rgb_ = getpix(x,y);
	rgba.r = (rgb_ >> 16) & 0xFF;
	rgba.g = (rgb_ >> 8) & 0xFF;
	rgba.b = rgb_ & 0xFF;
	rgba.a = 0xff;
	return rgba;
}

int generate_rgb(char r, char g, char b){
	return (((r&0xff)<<16)|((g&0xff)<<8)|(b&0xff));
}

void plot_pixel(int x,int y,int color){
	if(x<=gfbw &&
	   x>=0 &&
	   y<=gfbh&&
	   y>=0){
	   		//serial_print("Painting a pixel...\n");
			gfb[pixidx(x,y)]=color;		
	}
}

void plot_pixel_rgb(int x,int y,rgb_color color){
	if(x<=gfbw &&
	   x>=0 &&
	   y<=gfbh&&
	   y>=0){
			gfb[pixidx(x,y)]=generate_rgb(color.r,color.g,color.b);
	}
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

void drawrect(rect_colored r){
	int i,j;
	for(i=0; i<r.h; i++){
		for(j=0; j<r.w; j++){
			plot_pixel(r.x+j,r.y+i,r.color);
		}
	}
}

void fillall(rgb_color clr){
	rect_colored rct;
	rct.x=0;
	rct.y=0;
	rct.w=gfbw;
	rct.h=gfbh;
	rct.color = generate_rgb(clr.r, clr.g, clr.b);
	drawrect(rct);
}


void imagedraw(char meleon[], int width, int height, int startx, int starty){
	for(int i=0; i<height;i++){
		for(int j=0; j<width;j++) {
			if(meleon[extpixidx(j*4,i,width*4)+3]==0){continue;}
			char r = meleon[extpixidx(j*4,i,width*4)];
			char g = meleon[extpixidx(j*4,i,width*4)+1];
			char b = meleon[extpixidx(j*4,i,width*4)+2];
			plot_pixel(j+startx,i+starty,generate_rgb(r,g,b));
		}
	}
}


void gfx_init(uint32_t *gt){
	serial_print("Setting sizes...\n");
	//gfbh = (uint32_t)inf->framebuffer_height;
	//gfbw = (uint32_t)inf->framebuffer_width;
	gfbh = 600;
	gfbw = 800;
	serial_print("Setting buffer...\n");
	gfb = gt;
}

void gfx_update(uint32_t *fb, uint32_t *gf){
	memcpy(fb,gf,gfbw*gfbh*sizeof(uint32_t));
}
