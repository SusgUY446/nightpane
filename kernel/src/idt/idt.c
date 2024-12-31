#include "../terminal/terminal.h"

#define IDT_SIZE 256

extern void KiHaltSystem();
extern void KiCloseInterrupts();
extern void KiISRDivideBy0ErrorLoader();
extern void KiUnknownInterruptLoader();
struct InterruptDescriptor64 {
   uint16_t offset_1;        
   uint16_t selector;        
   uint8_t  ist;             
   uint8_t  type_attributes; 
   uint16_t offset_2;        
   uint32_t offset_3;        
   uint32_t zero;            
};

struct IDTR {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

struct InterruptDescriptor64 idt[IDT_SIZE];
struct IDTR idtr;

void KiSetIDTEntry(int index, void (*handler)(), uint16_t selector, uint8_t type_attributes, uint8_t ist){
    uint64_t handler_address = (uint64_t)handler;
    idt[index].offset_1 = handler_address & 0xFFFF;
    idt[index].selector = selector;
    idt[index].ist = ist;
    idt[index].type_attributes = type_attributes;
    idt[index].offset_2 = (handler_address >> 16) & 0xFFFF;    
    idt[index].offset_3 = (handler_address >> 32) & 0xFFFFFFFF;
    idt[index].zero = 0;  
}

void KiLoadIDT(){
    idtr.limit = (sizeof(struct InterruptDescriptor64) * IDT_SIZE) - 1;
    idtr.base = (uint64_t)&idt;

    __asm__ volatile("lidt %0" : : "m"(idtr));
}

void KiSetupIDT(){
    for(int i = 0; i < IDT_SIZE; i++){
        KiSetIDTEntry(i, KiUnknownInterruptLoader, 0x08, 0x8E, 0);
    }   
    KiSetIDTEntry(0, KiISRDivideBy0ErrorLoader, 0x08, 0x8E, 0);
    KiLoadIDT();
}

void KiDivideBy0Error(uint64_t* stack){
    //OSBugCheck("DIVIDE BY 0 ERROR");
    //KiCloseInterrupts();
    KiTerminalPrint("Kernel Suicide: DIVIDE BY 0 ERROR");
    // while(1){
    //     KiHaltSystem();
    //     continue;
    // }
    return;
}

void KiUnknownInterrupt(uint64_t* stack){
    //OSBugCheck("DIVIDE BY 0 ERROR");
    //KiCloseInterrupts();
    KiTerminalPrint("Kernel Suicide: UNKNOWN INTERRUPT (WAS UNDEFINED!!!!!!)");
    // while(1){
    //     KiHaltSystem();
    //     continue;
    // }
    return;
}