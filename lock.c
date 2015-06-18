#include <stdio.h>
#include <time.h>

int get_recoure(){
	printf("hello world\n");
	return 1;
}
int g_lock = 0;
void lock(){
	do{
		g_lock++;
		if (g_lock == 1)
			break;
		else{
			g_lock--;
			sleep(1);
		}
	}
	while(1);
}
void unlock(){
	g_lock--;
}
//get resoure with lock
int main(int argc ,char * argv[]){
	lock();
	get_recoure();
	unlock();
}

