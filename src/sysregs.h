#ifndef _SYSREGS_H_
#define _SYSREGS_H_

// ***************************************
// SCTLR_EL1, System Control Register (EL1), Page 2654 of AArch64-Reference-Manual.
// ***************************************

#define SCTLR_RESERVED          (3 << 28) | (3 << 22) | (1 << 20) | (1 << 11)
#define SCTLR_EE_LITTLE_ENDIAN  (0 << 25)
#define SCTLR_EOE_LITTLE_ENDIAN (0 << 24)
#define SCTLR_I_CACHE_DISABLED  (0 << 12)
#define SCTLR_D_CACHE_DISABLED  (0 << 2)
#define SCTLR_MMU_DISABLED      0
#define SCTLR_MMU_ENABLED       1

#define SCTLR_VALUE_MMU_DISABLED	(SCTLR_RESERVED | SCTLR_EE_LITTLE_ENDIAN | SCTLR_I_CACHE_DISABLED | SCTLR_D_CACHE_DISABLED | SCTLR_MMU_DISABLED)

// ***************************************
// HCR_EL2, Hypervisor Configuration Register (EL2), Page 2487 of AArch64-Reference-Manual.
// ***************************************

#define HCR_RW	    						(1 << 31)
#define HCR_VALUE								HCR_RW

// ***************************************
// SCR_EL3, Secure Configuration Register (EL3), Page 2648 of AArch64-Reference-Manual.
// ***************************************

#define SCR_RESERVED	    			(3 << 4)
#define SCR_RW									(1 << 10)
#define SCR_NS									1
#define SCR_VALUE	    	    		(SCR_RESERVED | SCR_RW | SCR_NS)

// ***************************************
// SPSR_EL3, Saved Program Status Register (EL3) Page 389 of AArch64-Reference-Manual.
// ***************************************

#define SPSR_MASK_ALL						(7 << 6)
#define SPSR_EL1h								5
#define SPSR_EL0h 							0 // 4
#define SPSR_VALUE_TO1					(SPSR_MASK_ALL | SPSR_EL1h)
#define SPSR_VALUE_TO0 					(SPSR_MASK_ALL | SPSR_EL0h)

#endif // _SYSREGS_H_
