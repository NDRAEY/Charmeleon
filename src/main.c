#include "main.h"
#include "font.h"
#include "string.h"
#include "random.h"
#include "ports.h"
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

void serial_print(char *text){
	for(int i=0; i<strlen(text); i++){
		outb(0x3f8,text[i]);
	}
}

void main(unsigned long magic, unsigned long addr) {
	inf = (multiboot_info_t*)addr;
	magic = magic^2; // supress warning
	fb = (uint32_t*)inf->framebuffer_addr;
	font_init();
	rtc_init();
	rand_init();
	rect_colored rc = createrect_colored(0,0,inf->framebuffer_width,720,generate_rgb(220,33,0));
	drawrect(rc);
	imagedraw(someimage, someimage_width, someimage_height, 120, 120);
	drawtext("OH-LALA!!! Charmeleon is here!!!\n(@charmeleon.ndraey)",8,10);
	char num[16];
	itoa(rand(65536*2),num);
	drawtext(num,8,10+16+16);

	time_t timez;
	timez = read_time();
	char ti[12*6];
	char sc[8];
	char mn[8];
	char hr[8];
	char dy[8];
	char mnt[8];
	char yr[8];
	itoa(timez.hr,hr);
	itoa(timez.min,mn);
	itoa(timez.sec,sc);
	itoa(timez.dy,dy);
	itoa(timez.mn,mnt);
	itoa(timez.yr,yr);
	strcpy(ti,hr);
	strcat(ti,":");
	strcat(ti,mn);
	strcat(ti,":");
	strcat(ti,sc);
	strcat(ti,"\n");
	strcat(ti,dy);
	strcat(ti,"/");
	strcat(ti,mnt);
	strcat(ti,"/");
	strcat(ti,yr);
	drawtext(ti,8,58);

	serial_print("Current time is: ");
	serial_print(hr);
	serial_print(":");
	serial_print(mn);
	serial_print(":");
	serial_print(sc);
	serial_print("\n");
	/*
	for(int i=0; i<45; i++){
		drawtext("NDRAEY NDRAEY NDRAEY NDRAEY NDRAEY NDRAEY NDRAEY NDRAEY NDRAEY NDRAEY NDRAEY NDRAEY NDRAEY NDRAEY NDRAEY NDRAEY NDRAEY NDRAEY",0,i*16);
	}
	imagedraw(someimage, someimage_width, someimage_height, (inf->framebuffer_width-someimage_width)/2, (inf->framebuffer_height-someimage_height)/2);
	*/
	while(1){}
}
