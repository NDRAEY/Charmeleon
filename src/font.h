#ifndef _FONT_
#define _FONT_

char* getfont();
void font_init();
int my_strlen(const char * s);
void drawchar(char ch, int ix, int iy);
void drawtext(char* text, int x, int y);

#endif
