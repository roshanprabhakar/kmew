#include "mm.h"
#include "printf.h"

uint64_t malloc_page() {
	int i = 0;
	for (; !IS_FREE(i) && i < NUM_PAGES; i++) {}
	if (i == NUM_PAGES) return 0x0L;
	SET_USE(i);
	return IND_TO_PTR(i);
}

void free_page(uint64_t ptr) {
	SET_FREE(PTR_TO_IND(ptr));
}
