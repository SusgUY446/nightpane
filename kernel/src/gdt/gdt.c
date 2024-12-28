#include "../runtimelib.h"

extern void KiLoadGDT(void* gdt);

struct GDTEntry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

struct GDTPointer {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

struct GDTEntry gdt[3];
struct GDTPointer gdt_pointer;

void KiSetupGDT(){
    gdt[0] = (struct GDTEntry){0};
    gdt[1] = (struct GDTEntry){
        .limit_low = 0xFFFF,
        .base_low = 0x0000,
        .base_middle = 0x00,
        .access = 0x9A,
        .granularity = 0xA0,
        .base_high = 0x00
    };
    gdt[2] = (struct GDTEntry){
        .limit_low = 0xFFFF,
        .base_low = 0x0000,
        .base_middle = 0x00,
        .access = 0x92,
        .granularity = 0xA0,
        .base_high = 0x00
    };
    gdt_pointer.limit = sizeof(gdt) - 1;
    gdt_pointer.base = (uint64_t)&gdt;
    KiLoadGDT(&gdt_pointer);
}