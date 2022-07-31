#ifndef __SERIAL_IO
#define __SERIAL_IO

#include <stdint.h>

#include "peripherals/mini_uart.h"
#include "peripherals/gpio.h"

/** UNRELIABLE **/
void bare_metal_miniUART_setup();

// printf internal function
void _putchar(char c);

#endif /* __SERIAL_IO */
