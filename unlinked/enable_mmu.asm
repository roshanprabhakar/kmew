
.section ".text.mmu_config"

.global _enable_mmu

_enable_mmu:
	/*
	mrs		p15,	0, 	r1, c1, c0, 0
	orr		r1,		#0x1
	msr		p15,	0,	r1,	c1,	c0,	0
	ret
	*/
