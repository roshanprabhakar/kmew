#include "serial_io.h"

/**
 * Qemu seems to perform this configuration when wiring miniUART to stdio.
 * Unable to debug without hardware, unreliable.
 */
void bare_metal_miniUART_setup() {
  // disable auxiliaries
  *(uint32_t*) AUX_ENABLES = 0;

  // disable pull up/down for all gpio pins
  *(uint32_t*) GPPUD = 0;
  delay(150);

  // disable pull up/down for pins 14,15
  *(uint32_t*) GPPUDCLK0 = (1 << 14) | (1 << 15);
  delay(150);

  // required to take effect
  // *(uint32_t*) GPPUD = 0;
  *(uint32_t*) GPPUDCLK0 = 0;

  // set gpio pins 14,15 to respective alternate functions
  uint32_t gpfsel1 = *(uint32_t*) GPFSEL1; // gpio control reg for pins 10-19

  gpfsel1 &= ~(0b111 << 12);					// clear bits used for pin 14 (14-12)
  gpfsel1 |= 0b010 << 12;							// set pin 14 to alternate function 5
  gpfsel1 &= ~(0b111 << 15);					// clear bits used for pin 15 (17-15)
  gpfsel1 |= 0b010 << 15;							// set pin 15 to alternate function 5

  *(uint32_t*) GPFSEL1 = gpfsel1;

  // mini-uart init
  *(uint32_t*) AUX_ENABLES = 1;				// enables access to mini-uart registers
  *(uint32_t*) AUX_MU_CNTL_REG = 0;		// disable transmitter and receiver (for now)
  *(uint32_t*) AUX_MU_IER_REG = 0;		// disable interrupts + clear pending
  *(uint32_t*) AUX_MU_LCR_REG = 3;		// enable 8-bit mode
  *(uint32_t*) AUX_MU_MCR_REG = 0;		// keep rts line high
  *(uint32_t*) AUX_MU_BAUD_REG = 270;	// set baud rate

  *(uint32_t*) AUX_MU_CNTL_REG = 3;		// enable bit 0 (rec), bit 1 (tran)
}

void _putchar(char c) {
  for (;;) { if ((*(uint32_t*) AUX_MU_LSR_REG) & 0x20) break; }
  *(uint32_t*) AUX_MU_IO_REG = c;
}

void putchar(char c) {
  _putchar(c);
}

void getchar(char* c) {
  for (;;) { if ((*(uint32_t*) AUX_MU_LSR_REG) & 0x01) break; }
  *c = (char) ((*(uint32_t*) AUX_MU_IO_REG ) & 0xFF);
}

void delchar() {
  putchar('\b'); 
  putchar((char) 127);
  putchar('\b');
}
