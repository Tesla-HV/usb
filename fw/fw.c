#include "fx2regs.h"

#define MSB(x) (((int)(x) >> 8) & 0xFF)
#define LSB(x) ((int)(x) & 0xFF)

// Я не знаю, сколько тут нужно nop-ов, но думаю, что 16 хватит
#define SYNCDELAY __asm__("nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;")

char *data1 = "Hello World!";
char *data2 = "Goodbye!";

void send_string(const unsigned char *data) {
	int len = 0;
	AUTOPTRH2 = MSB(&EP6FIFOBUF);
	AUTOPTRL2 = LSB(&EP6FIFOBUF);
	len = 0;
	do {
		EXTAUTODAT2 = *data;
		len++;	
	} while(*(data++) != 0);
	EP6BCH = MSB(len);
	SYNCDELAY;
	EP6BCL = LSB(len);
	SYNCDELAY;
}

void main() {

	unsigned int i, j, len;
	char *data_ptr;

	// Переключаем тактовую частоту процессора на 48 МГц
	CPUCS = ((CPUCS & ~bmCLKSPD) | bmCLKSPD1);

	while(1) {

		// Висим в цикле пока в буфере EP6-IN нет свободного места
		while(EP2468STAT & bmEP6FULL);

		// Отправляем привет
		send_string(data1);

		// Светодиод гори!
		OEC |= 1;

		// Ничего не делаем 1048576 раз (для задержки)
		for (i = 0; i < 1024; i++) {
			for (j = 0; j < 1024; j++) {
				__asm__ ("nop");
			}
		}
	
		// Висим в цикле пока в буфере EP6-IN нет свободного места
		while(EP2468STAT & bmEP6FULL);

		// Отправляем пока
		send_string(data2);

		// Светодиод погасни!
		OEC &= ~0x01;

		// Ничего не делаем 1048576 раз (для задержки)
		for (i = 0; i < 1024; i++) {
			for (j = 0; j < 1024; j++) {
				__asm__ ("nop");
			}
		}

	}

}



