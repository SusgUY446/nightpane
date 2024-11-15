#ifndef PS2_H_INCLUDED
#define PS2_H_INCLUDED




#include "../driver.h"

char Ps2ReadKey();
uint8_t Ps2ReadScanCodeFromPort();
char Ps2ScanCodeToCharacter(uint8_t makeCode);
#endif