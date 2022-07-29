#include <stdint.h>

/* first 32 bits of dtb_ptr32 points to an object described here:
 * https://elinux.org/Device_Tree_Reference#Introduction
 *
 * helpful:
 * https://unix.stackexchange.com/questions/118683/what-is-a-device-tree-and-a-device-tree-blob
 */
#if 0
int kmew_main(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3) {
  return 0;
}

const uint32_t __stack_chk_guard	= 0xBADBADFF;
const uint32_t __stack_chk_fail		= 0xFFBADBAD;
#endif

extern uint64_t _get_el();

int kmew_main() {
  int32_t x;
  *(&x) = 55;

	uint64_t el = _get_el();

  return (int)el;
}
