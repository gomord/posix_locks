static __always_inline void inline fix_canary(unsigned long new_canary){
	asm(	
		"push %%eax\n\t"/*
		"movl %%ebp, %%eax\n\t"
		"subl %%esp, %%eax\n\t"
		"addl $4,   %%eax\n\t"
		"addl %%esp,%%eax\n\t"*/
		"movl %0,%%eax\n\t"
		"movl %%eax,-0xc(%%ebp)\n\t"
		"movl %%eax, %%gs:0x14\n\t"
		"pop %%eax"
		:
		:"m"(new_canary)
		);
	    	

}
