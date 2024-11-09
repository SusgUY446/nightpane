#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED






#include "draw.h"



void KiDrawCharacter(int x, int y, int size, char c, uint32_t color);
void KiDrawText(int x, int y, char* s, int size, uint32_t color);

#endif