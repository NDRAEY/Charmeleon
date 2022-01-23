#ifndef _MAIN_
#define _MAIN_

#include "multiboot.h"
#include "defs.h"
#include <stdint.h>

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

static multiboot_info_t *inf;
static uint32_t *fb; 
static uint32_t *gfb; 

// From auto-generated image.c
extern int someimage_width;
extern int someimage_height;
extern char someimage[];
extern char someimage_name;

#endif
