/**
 * IO communication with miniUART terminal emulator.
 */

#ifndef __SERIAL_IO
#define __SERIAL_IO

#include <stdint.h>

#include "peripherals/mini_uart.h"
#include "peripherals/gpio.h"

/** UNRELIABLE **/
/*
 *  mUART configuration for bare metal raspi3b.
 *  Untested.
 */
void bare_metal_miniUART_setup();

void putchar(char c);
void delchar();
void getchar(char* c); // load *c with serial input

/* Delay with simple loop (defined in boot.S) */
void delay(uint64_t cycles);

#endif /* __SERIAL_IO */
