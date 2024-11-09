#include "draw.h"



#include <stdint.h>





extern struct limine_framebuffer *framebuffer;



void KiDrawPixel(int x, int y, uint32_t color){
    volatile uint32_t *fb_ptr = framebuffer->address;
    fb_ptr[y * (framebuffer->pitch / 4) + x] = color;
}


void KiDrawRect(int x, int y, int height, int width, uint32_t color){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            KiDrawPixel(x + j, y + i, color);
        }
    }
}




void KiChangeBackground(uint32_t color){
    KiDrawRect(0, 0, framebuffer->height, framebuffer->width, color);
}