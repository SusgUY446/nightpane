#include "terminal.h"
#include "../driver/ps2/ps2.h"
#include "extern/mini-printf.h"
static int line = 0;
static int line_cursor = 0;

extern struct limine_framebuffer *framebuffer;


void KiTerminalPrint(char* status) {
    static bool init = false;
    if(init == false){
        init = true;
    }
    if(!init){  
        KiDrawRect(0, 10, framebuffer->height - 10, framebuffer->width, 0x0000000);
        init = true;
    }               
    
    KiDrawText(1 + line_cursor, 12 * line, status, 1, 0xfffffff);
    line_cursor += 5;
    line++;
    line_cursor = 0;
   
    if ((12 * line) >= framebuffer->height) {
        KiClearScreen();
    } 
}

void KiTerminalPuts(char* status) {
    static bool init = false;
    if(init == false){
        init = true;
    }
    if(!init){  
        KiDrawRect(0, 10, framebuffer->height - 10, framebuffer->width, 0x0000000);
        init = true;
    }               
    
    KiDrawText(1 + line_cursor, 12 * line, status, 1, 0xfffffff);
    line_cursor += 5;
    //line++;
    line_cursor = 0;
   
    if ((12 * line) >= framebuffer->height) {
        KiClearScreen();
    } 
}

void KiTerminalPrintF(char *format, ...) {
    char buffer[10293];
    va_list args;
    va_start(args, format); 
    mini_vsnprintf(buffer, sizeof(buffer), format, args); 
    va_end(args); 
    KiTerminalPrint(buffer);
}

void KiClearScreen(){
    KiChangeBackground(0x0000000);
    line = 0;
}

