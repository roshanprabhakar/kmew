#ifndef __ARM_INTERRUPTS
#define __ARM_INTERRUPTS

#include "base.h"

#define IBASE								(PBASE+0x0000B000)
#define IRQ_BASIC_PENDING		(IBASE+0x00000200)
#define IRQ_PENDING_1				(IBASE+0x00000204)
#define IRQ_PENDING_2				(IBASE+0x00000208)
#define FIQ_CONTROL					(IBASE+0x0000020C)
#define ENABLE_IRQ_1				(IBASE+0x00000210)
#define ENABLE_IRQ_2				(IBASE+0x00000214)
#define ENABLE_BASIC_IRQ		(IBASE+0x00000218)
#define DISABLE_IRQ_1				(IBASE+0x0000021C)
#define DISABLE_IRQ_2				(IBASE+0x00000220)
#define DISABLE_BASIC_IRQ		(IBASE+0x00000224)

// irq reg 1
#define SYS_TIMER_MATCH_1 	(1 << 1)
#define SYS_TIMER_MATCH_3 	(1 << 3)
#define USB_CONTROLLER 			(1 << 9)
#define AUX_INT 						(1 << 29)

// irq reg 2
#define I2C_SPI_SLV_INT 		(1 << 11)
#define PWA0 								(1 << 13)
#define PWA1 								(1 << 14)

//...

#define UART_INT 						(1 << 25)


#endif // __ARM_INTERRUPTS
