#include "gfx.h"
#include "font.h"

#define ASSERT(b) ((b) ? (void)0 : panic(#b, __FILE__, __LINE__))

void panic(const char *message, const char *file, uint32_t line){
	rgb_color cl;
	cl.r=0;
	cl.g=0;
	cl.b=0;
	fillall(cl);
	drawtext("ERROR OCCURED.",0,0);
	drawtext("ERROR: ",0,16);
	drawtext(message,7*8,16);
	for(;;);
}
