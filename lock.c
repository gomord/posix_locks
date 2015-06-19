#include <stdio.h>
#include <time.h>

int get_recoure(){
	printf("hello world\n");
	return 1;
}
int g_lock = 0;

void asm_inc(int *val){
	asm("incl %0"::"m"(*val));
}
void asm_dec(int *val){
	asm("decl %0"::"m"(*val));
}
void lock(){
	do{
		asm_inc(&g_lock);
		if (g_lock == 1)
			break;
		else{
			asm_dec(&g_lock);
			sleep(1);
		}
	}
	while(1);
}
void unlock(){
	asm_dec(&g_lock);
}
//get resoure with lock
int main(int argc ,char * argv[]){
	lock();
	get_recoure();
	unlock();
}

