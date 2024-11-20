#ifndef SUPERHEADER_H_INCLUDED
#define SUPERHEADER_H_INCLUDED






#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

typedef struct _BOOTDATA{
    uint64_t boottime;
    char* loadername;
    uint64_t firmwaretype;
} BOOTDATA;

#endif