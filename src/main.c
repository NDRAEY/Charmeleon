#include "main.h"
#include "font.h"
#include "string.h"
#include "random.h"
#include "rtc.h"

int pixidx(int x, int y){
	return inf->framebuffer_width*y+x;
}

int extpixidx(int x, int y, int w){
	return w*y+x;
}

int getpix(int x, int y){
	return fb[pixidx(x,y)];
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
	if(x<=(int)inf->framebuffer_width &&
	   x>=0 &&
	   y<=(int)inf->framebuffer_height&&
	   y>=0){
			fb[pixidx(x,y)]=color;		
	}
}

void plot_pixel_rgb(int x,int y,rgb_color color){
	if(x<=(int)inf->framebuffer_width &&
	   x>=0 &&
	   y<=(int)inf->framebuffer_height&&
	   y>=0){
			fb[pixidx(x,y)]=generate_rgb(color.r,color.g,color.b);
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

rgb_color blend_colors(rgba_color c1, rgba_color c2) {
    uint32_t alpha1 = c1.a;
    uint32_t red1 = c1.r;
    uint32_t green1 = c1.g;
    uint32_t blue1 = c1.b;

    uint32_t alpha2 = c2.a;
    uint32_t red2 = c2.r;
    uint32_t green2 = c2.g;
    uint32_t blue2 = c2.b;

    uint32_t r = (uint32_t)((alpha1 * 1.0 / 255) * red1);
    uint32_t g = (uint32_t)((alpha1 * 1.0 / 255) * green1);
    uint32_t b = (uint32_t)((alpha1 * 1.0 / 255) * blue1);

	rgb_color rgb;

    rgb.r = r + (((255 - alpha1) * 1.0 / 255) * (alpha2 * 1.0 / 255)) * red2;
    rgb.g = g + (((255 - alpha1) * 1.0 / 255) * (alpha2 * 1.0 / 255)) * green2;
    rgb.b = b + (((255 - alpha1) * 1.0 / 255) * (alpha2 * 1.0 / 255)) * blue2;

    return rgb;
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

void imagedraw2(char meleon[], int width, int height, int startx, int starty){
	for(int i=0; i<height;i++){
		for(int j=0; j<width;j++) {
			//if(meleon[extpixidx(j,i,width)+3]==0){continue;}
			char color = meleon[extpixidx(j,i,width)];
			plot_pixel(j+startx,i+starty,color);
		}
	}
}

void main(unsigned long magic, unsigned long addr) {
	inf = (multiboot_info_t*)addr;
	fb = (uint32_t*)inf->framebuffer_addr;
	font_init();
	rect_colored rc = createrect_colored(0,0,inf->framebuffer_width,720,generate_rgb(220,33,0));
	drawrect(rc);
	rect_colored rclear = createrect_colored(8,58,16+(8*10),58+16,generate_rgb(220,33,0));
	imagedraw(someimage, someimage_width, someimage_height, 70, 70);
	drawtext("OH-LALA!!! Charmeleon is here!!!\n(@charmeleon.ndraey)",8,10);
	char num[16];
	itoa(rand(65536),num);
	drawtext(num,8,10+16+16);
	time_c timez;
	char ti[12*3];
	while(1){
		timez = gettime_c();
		strcpy(ti,timez.hr);
		strcat(ti,":");
		strcat(ti,timez.min);
		strcat(ti,":");
		strcat(ti,timez.sec);
		drawtext(ti,8,58);
		for(int i=0; i<0xFFFFFFF+0xFFFFFF;i++){}
		for(int j=0; j<12*3; j++){ti[j]=0;}
		drawrect(rclear);
		for(int i=0; i<0xFFFFF+0xFFFF;i++){}
	}
}
