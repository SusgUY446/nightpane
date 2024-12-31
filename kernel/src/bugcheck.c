#include "bugcheck.h"
#include "drawing/draw.h"
#include "drawing/text.h"

extern void KiHaltSystem();
extern void KiCloseInterrupts();


// void OSBugCheck(char* error){
//     //KiChangeBackground(0x1e1e2e);
//     KiDrawText(700, 600, ":(", 10, 0xFFFFFF);
//     KiDrawText(10, 10, "OS has ran into an issue and has been shutdown to prevent damage", 1, 0xFFFFFF);
//     KiDrawText(10, 20, "please contact zvqle with these error code", 1, 0xFFFFFF);
//     KiDrawText(10, 60, error, 1, 0xFFFFFF);
//     // KiCloseInterrupts();
//     // while(1){
//     //     KiHaltSystem();
//     //     continue;
//     // }
    
// }