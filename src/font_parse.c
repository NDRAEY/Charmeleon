#include "main.h"
#include "font.h"
#include "string.h"
#define FW 8
#define FH 16

char* font;

void font_init(){
	font = getfont();
}

void drawchar(char ch, int ix, int iy){
	int x, y;
	for(y = 0; y < FH; y++){
		for(x = 0; x < FW; x++){
	    	if(font[(ch*FW*FH)+(FW*y)+x]==1){
				plot_pixel(ix+x,iy+y,generate_rgb(147,255,220));
	        }
	    }
	}
}

void drawtext(char* text, int x, int y) {
	int len = strlen(text);
	int nx = x;
	int ny = y;
	for(int i=0; i<len; i++) {
		switch(text[i]){
			case '\n':
				ny+=FH;
				nx=x;
				break;
			default:		
				drawchar(text[i],nx,ny);
				nx+=FW;
		}
	}
}
