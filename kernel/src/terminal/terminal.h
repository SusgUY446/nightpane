#ifndef TERMINAL_H_INCLUDED
#define TERMINAL_H_INCLUDED



#include "../drawing/draw.h"
#include "../drawing/text.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void KiClearScreen();
void KiTerminalPrint(char* status);

#endif