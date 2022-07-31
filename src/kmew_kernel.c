void kmew_main() __attribute__((section(".text.kernel")));

#include <stdint.h>
#include "printf.h"

void kmew_main() {
	
	bare_metal_miniUART_setup();
	printf("hello %d world\n", 5);

	/*
	while (1) {
		// busy wait until uart status reg asserts 1 byte available
		if ((*(uint32_t*) AUX_MU_LSR_REG) & 0x01) break;
	}
	char data = (*(uint32_t*) AUX_MU_IO_REG) & 0xFF;
	*/
}
