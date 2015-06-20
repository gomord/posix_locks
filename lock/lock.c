#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "lock.h"
#define NUM_OF_THREADS 4
int g_lock = 0;

inline void asm_inc(int *val){
	asm("incl %0"::"m"(*val));
	//int reg = 1;
	//asm("cmpxchgl %1, %0" ::"m"(*val),"r"(reg));
}
inline void asm_dec(int *val){
	asm("decl %0"::"m"(*val));
}
void lock(){
	do{
		asm_inc(&g_lock);
		if (g_lock == 1)
			break;
		else{
			asm_dec(&g_lock);
			sleep(rand()%NUM_OF_THREADS);
		}
	}
	while(1);
}
void unlock(){
	asm_dec(&g_lock);
}


