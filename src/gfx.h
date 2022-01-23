#ifndef _GFX_H_
#define _GFX_H_
#include <stdint.h>
#include "defs.h"
//#include "main.h"

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

typedef struct {
	char r;
	char g;
	char b;
} rgb_color;

typedef struct {
	char r;
	char g;
	char b;
	char a;
} rgba_color;

typedef struct {
	int x;
	int y;
} point_int;

int pixidx(int x, int y);
int extpixidx(int x, int y, int w);
int getpix(int x, int y);
rgb_color getpix_rgb(int x, int y);
rgba_color getpix_rgba(int x, int y);
void plot_pixel(int x,int y,int color);
int generate_rgb(char r, char g, char b);
void plot_pixel_rgb(int x,int y,rgb_color color);
rect createrect(int x, int y, int w, int h);
rect_colored createrect_colored(int x, int y, int w, int h, int color);
void drawrect(rect_colored r);
void fillall(rgb_color clr);
void imagedraw(char meleon[], int width, int height, int startx, int starty);

void gfx_init();
void gfx_update();
#endif
