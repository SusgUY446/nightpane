#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "drawing/draw.h"
#include "limine.h"
#include "drawing/text.h"
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


static void hcf(void) {
    for (;;) {
#if defined (__x86_64__)
        asm ("hlt");
#elif defined (__aarch64__) || defined (__riscv)
        asm ("wfi");
#elif defined (__loongarch64)
        asm ("idle 0");
#endif
    }
}


void KiMain(void) {
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        hcf();
    }

    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    framebuffer = framebuffer_request.response->framebuffers[0];
    KiChangeBackground(0x0000000);

    KiTerminalPrint("H");
    

    hcf();
}
