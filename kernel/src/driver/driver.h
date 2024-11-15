#ifndef DRIVER_H_INCLUDED
#define DRIVER_H_INCLUDED





#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

uint8_t KiInByte(uint16_t port);
void KiOutByte(uint16_t port, uint8_t value);



#endif