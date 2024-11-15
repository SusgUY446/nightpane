#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "drawing/draw.h"
#include "driver/ps2/ps2.h"
#include "limine.h"
#include "terminal/terminal.h"


__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);


__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};


__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;

struct limine_framebuffer *framebuffer;


static void halt(void) {
    for (;;) {
        asm ("hlt");
    }
}


void test_gdt() {
    uint64_t test_value = 0x12345678;
    uint64_t *test_ptr = (uint64_t*)0x10; 

    *test_ptr = test_value;

    if (*test_ptr != test_value) {
        KiTerminalPrint("Die!");
        while(1); 
    }

}

extern void KiTestAsmCLinkage();
void KiMain(void) {
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        halt();
    }

    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        halt();
    }

    framebuffer = framebuffer_request.response->framebuffers[0];
    KiChangeBackground(0x0000000);
    KiTestAsmCLinkage();
    KiTerminalPrint("Y");
    KiTerminalPrint("Y");
    //test_gdt();
    while(1){
        char idk = Ps2ReadKey();
        KiTerminalPrint(&idk);
    }
    

    halt();
}
