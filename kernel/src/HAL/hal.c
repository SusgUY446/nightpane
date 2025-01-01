#include "hal.h"




void HalHaltSystem() {
    for (;;) {
        asm ("hlt");
    }
}

void HalClearInterrupts() {
    asm ("cli");  
}

void HalEnableInterrupts() {
    asm ("sti");  
}