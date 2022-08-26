void kmew_main() __attribute__((section(".text.kernel")));

#include <stdint.h>
#include "printf.h"

void kmew_main() {
	
	bare_metal_miniUART_setup();
	printf("hello %d world\n", 5);

}
