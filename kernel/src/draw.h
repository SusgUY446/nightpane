#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED






#include "limine.h"



void KiDrawPixel(int x, int y, uint32_t color);
void KiDrawRect(int x, int y, int height, int width, uint32_t color);
void KiChangeBackground(uint32_t color);









#endif