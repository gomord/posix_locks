
#include <stdio.h>
#include "lock.h"
int get_recoure(){
	printf("hello world\n");
	return 1;
}

//get resoure with lock
int main(int argc ,char * argv[]){
	lock();
	get_recoure();
	unlock();
}

