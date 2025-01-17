#include "ps2.h"


char Ps2ScanCodeToCharacter(uint8_t makeCode) {
    switch (makeCode) {
        case 41: return '`';
        case 2: return '1';
        case 3: return '2';
        case 4: return '3';
        case 5: return '4';
        case 6: return '5';
        case 7: return '6';
        case 8: return '7';
        case 9: return '8';
        case 10: return '9';
        case 11: return '0';
        case 12: return '-';
        case 13: return '=';
        case 14: return '\b'; 
        case 15: return '\t'; 
        case 16: return 'q';
        case 17: return 'w';
        case 18: return 'e';
        case 19: return 'r';
        case 20: return 't';
        case 21: return 'y';
        case 22: return 'u';
        case 23: return 'i';
        case 24: return 'o';
        case 25: return 'p';
        case 26: return '[';
        case 27: return ']';
        case 28: return '\n'; 
        case 30: return 'a';
        case 31: return 's';
        case 32: return 'd';
        case 33: return 'f';
        case 34: return 'g';
        case 35: return 'h';
        case 36: return 'j';
        case 37: return 'k';
        case 38: return 'l';
        case 39: return ';';
        case 40: return '\'';
        case 43: return '\\';
        case 44: return 'z';
        case 45: return 'x';
        case 46: return 'c';
        case 47: return 'v';
        case 48: return 'b';
        case 49: return 'n';
        case 50: return 'm';
        case 51: return ',';
        case 52: return '.';
        case 53: return '/';
        case 57: return ' '; 
        default: return '\0'; 
    }
}





uint8_t Ps2ReadScanCodeFromPort(){
    while(1){
        uint8_t status = KiInByte(0x64);
        if(status & 0x01){
            return KiInByte(0x60);
        }
    }
}


char Ps2ReadKey() {
    uint8_t scan_code = Ps2ReadScanCodeFromPort(); 
    return Ps2ScanCodeToCharacter(scan_code);
}