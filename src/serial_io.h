/**
 * IO communication with miniUART terminal emulator.
 */

#ifndef _SERIAL_IO_
#define _SERIAL_IO_

#include <stdint.h>

#include "peripherals/mini_uart.h"
#include "peripherals/gpio.h"

void _putchar(char c);
void _delchar();
void _getchar(char* c); // load *c with serial input

/* Delay with simple loop (defined in boot.S) */
void delay(uint64_t cycles);

#endif // _SERIAL_IO_
