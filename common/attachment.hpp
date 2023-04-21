#include "rpm.hpp"

unsigned long checkValue = 0x5A454C44;
unsigned long checkOffset = 0x11A5EC;

extern RPM emulator;
extern unsigned long base;

bool attachToProject64() {
	if (emulator.Process("Project64.exe")) {
		for (BYTE i = 0; i < 32; i++) {
			if (emulator.Read<unsigned long>(0xDFE00000 + (0x10000 * i) + checkOffset) == checkValue) {
				base = 0x5FE00000 + (0x10000 * i);
				return true;
			}
		}
	}
	return false;
}