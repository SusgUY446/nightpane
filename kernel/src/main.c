#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "drawing/draw.h"
#include "limine.h"
#include "superheader.h"
#include "terminal/terminal.h"

__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);


__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

__attribute__((used, section(".limine_requests")))
static volatile struct limine_firmware_type_request firmware_type_request = {
    .id = LIMINE_FIRMWARE_TYPE_REQUEST,
    .revision = 0
};

__attribute__((used, section(".limine_requests")))
static volatile struct limine_boot_time_request boot_time_request = {
    .id = LIMINE_BOOT_TIME_REQUEST,
    .revision = 0
};

__attribute__((used, section(".limine_requests")))
static volatile struct limine_bootloader_info_request bootloader_info_request = {
    .id = LIMINE_BOOTLOADER_INFO_REQUEST,
    .revision = 0
};



__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;

struct limine_framebuffer *framebuffer;


void KiHaltSystem() {
    for (;;) {
        asm ("hlt");
    }
}

void KiCloseInterrupts() {
    asm ("cli");  
}

extern void KiSetupGDT();
extern void KiTestAsmCLinkage();
BOOTDATA btdta;

void TestDivideByZero() {
    volatile int a = 10;
    volatile int b = 0;
    int c = a / b; // Should trigger exception
    (void)c;
}

extern void KiTestAsmCLinkage();
void KiMain(void) {
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        KiHaltSystem();
    }

    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        KiHaltSystem();
    }

    framebuffer = framebuffer_request.response->framebuffers[0];
    KiChangeBackground(0x0000000);
    KiTerminalPrint("Loading System.....\n");
    
    if (firmware_type_request.response == NULL) {
        KiTerminalPrint("Failure to Get Firmware Type\nHalting System");
        KiHaltSystem();
    }
    if (boot_time_request.response == NULL) {
        KiTerminalPrint("Failure to Get Boot Time\nHalting System");
        KiHaltSystem();
    }
    if (bootloader_info_request.response == NULL) {
        KiTerminalPrint("Failure to Get Bootloader Type\nHalting System");
        KiHaltSystem();
    }
    
    btdta.firmwaretype = firmware_type_request.response->firmware_type;
    btdta.boottime = boot_time_request.response->boot_time;
    btdta.loadername = bootloader_info_request.response->name;
    TestDivideByZero();
    //KiTerminalPrintF("%d", i);
    KiTerminalPrint("Hi");    


    
    KiHaltSystem();
}
