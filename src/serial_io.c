#include "serial_io.h"

void _putchar(char c) {
  for (;;) { if ((*(uint32_t*) AUX_MU_LSR_REG) & 0x20) break; }
  *(uint32_t*) AUX_MU_IO_REG = c;
}

void _getchar(char* c) {
  for (;;) { if ((*(uint32_t*) AUX_MU_LSR_REG) & 0x01) break; }
  *c = (char) ((*(uint32_t*) AUX_MU_IO_REG ) & 0xFF);
}

void _delchar() {
  _putchar('\b'); 
  _putchar((char) 127);
  _putchar('\b');
}
