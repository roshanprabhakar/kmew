#ifndef __SERIAL_IO
#define __SERIAL_IO

#include <stdint.h>

#include "peripherals/mini_uart.h"
#include "peripherals/gpio.h"

/** UNRELIABLE **/
void bare_metal_miniUART_setup();

void _putchar(char c);
void _getchar(char* c); // load *c with serial input
void _delchar();

#endif /* __SERIAL_IO */
