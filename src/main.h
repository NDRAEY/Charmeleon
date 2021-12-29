#ifndef _MAIN_
#define _MAIN_

#include "multiboot.h"
#include <stdint.h>

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

static multiboot_info_t *inf;
static uint32_t *fb; 

// From auto-generated image.c
extern int someimage_width;
extern int someimage_height;
extern char someimage[];
extern char someimage_name;

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
rgb_color blend_colors(rgba_color c1, rgba_color c2);
void imagedraw(char meleon[], int width, int height, int startx, int starty);

#endif
