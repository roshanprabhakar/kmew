#include <stdint.h>

// true: big_endian
uint8_t byte_order() {
	uint16_t st_v = 769U;
	char check = *(char*)(&st_v);
	return check == 3;
}
