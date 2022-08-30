#ifndef	_P_TIMER_H
#define	_P_TIMER_H

#include "base.h"

#define TBASE						(PBASE+0x00003000)
#define TIMER_CS        (TBASE+0x00000000)
#define TIMER_CLO       (TBASE+0x00000004)
#define TIMER_CHI       (TBASE+0x00000008)
#define TIMER_C0        (TBASE+0x0000000C)
#define TIMER_C1        (TBASE+0x00000010)
#define TIMER_C2        (TBASE+0x00000014)
#define TIMER_C3        (TBASE+0x00000018)

/*
#define TIMER_CS_M0	(1 << 0)
#define TIMER_CS_M1	(1 << 1)
#define TIMER_CS_M2	(1 << 2)
#define TIMER_CS_M3	(1 << 3)
*/

#endif  /*_P_TIMER_H */
