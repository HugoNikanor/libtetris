#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "ansi_color.h"
#include "types.h"

// board not modified, but gcc complains if I put const there
void printboard(int width, int height, color board[][width]);

#endif // GRAPHICS_H
