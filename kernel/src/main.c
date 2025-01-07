#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "drawing/draw.h"
#include "limine.h"
#include "superheader.h"
#include "terminal/terminal.h"
#include "HAL/hal.h"
#include "driver/ps2/ps2.h"

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

__attribute__((used, section(".limine_requests")))
static volatile struct limine_hhdm_request hhdm_info_request = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};


__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;

struct limine_framebuffer *framebuffer;




// using limines higher half direct mapping till i can be arsed to write my own VMM
uintptr_t KiPhysicalToVirtualMemory(uintptr_t physical_address) {
    if (hhdm_info_request.response == NULL) {
        KiTerminalPrint("Fail");
        HalHaltSystem();
        return 0;
    }
    return physical_address + hhdm_info_request.response->offset;
}


extern void KiSetupGDT();
extern void KiTestAsmCLinkage();
BOOTDATA btdta;

// void TestDivideByZero() {
//     volatile int a = 10;
//     volatile int b = 0;
//     int c = a / b; 
//     (void)c;
// }

extern void KiTestAsmCLinkage();
void KiMain(void) {
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        HalHaltSystem();
    }

    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        HalHaltSystem();
    }

    framebuffer = framebuffer_request.response->framebuffers[0];
    KiChangeBackground(0x0000000);
    KiTerminalPrint("Loading System.....\n");
    
    if (firmware_type_request.response == NULL) {
        KiTerminalPrint("Failure to Get Firmware Type\nHalting System");
        HalHaltSystem();
    }
    if (boot_time_request.response == NULL) {
        KiTerminalPrint("Failure to Get Boot Time\nHalting System");
        HalHaltSystem();
    }
    if (bootloader_info_request.response == NULL) {
        KiTerminalPrint("Failure to Get Bootloader Type\nHalting System");
        HalHaltSystem();
    }
    if (hhdm_info_request.response == NULL) {
        KiTerminalPrint("Failure to Get HHDM Type\nHalting System");
        HalHaltSystem();
    }
    
    
    btdta.firmwaretype = firmware_type_request.response->firmware_type;
    btdta.boottime = boot_time_request.response->boot_time;
    btdta.loadername = bootloader_info_request.response->name;
    //TestDivideByZero();
    //KiTerminalPrintF("%d", i);
    volatile uintptr_t *address = (volatile uintptr_t *)(KiPhysicalToVirtualMemory(0x01));
    *address = 10;
    KiTerminalPrint("Hi");    
    KiTerminalPrintF("%d", *address);
    while(1){
        KiTerminalPrintF("%c", Ps2ReadKey());
    }

    
    HalHaltSystem();
}
