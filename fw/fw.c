#include "fx2regs.h"

void main() {

	unsigned int i;


	USBCS |= bmDISCON;
	for (i = 0; i < 65535; i++) {
		__asm__ ("nop");
	}
	USBCS &= ~bmDISCON;

	USBIE = 0;


	while(1) {

		OEC |= 1;

		for (i = 0; i < 65535; i++) {
			__asm__ ("nop");
		}

		OEC &= ~0x01;

		for (i = 0; i < 65535; i++) {
			__asm__ ("nop");
		}
	}

}



