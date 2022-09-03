#ifndef _VTABLE_H_
#define _VTABLE_H_

#define S_FRAME_SIZE						256 		// size of all saved registers 

// m < n
#define SYNC_INVALID_ELnt				0 
#define IRQ_INVALID_ELnt				1 
#define FIQ_INVALID_ELnt				2 
#define ERROR_INVALID_ELnt			3 

#define SYNC_INVALID_ELnh				4 
#define IRQ_INVALID_ELnh				5 
#define FIQ_INVALID_ELnh				6 
#define ERROR_INVALID_ELnh			7 

#define SYNC_INVALID_ELm_64			8 
#define IRQ_INVALID_ELm_64			9 
#define FIQ_INVALID_ELm_64			10 
#define ERROR_INVALID_ELm_64		11 

#define SYNC_INVALID_ELm_32			12 
#define IRQ_INVALID_ELm_32			13 
#define FIQ_INVALID_ELm_32			14 
#define ERROR_INVALID_ELm_32		15 

#endif
