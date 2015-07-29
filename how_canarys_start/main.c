#include <stdio.h>

#include <string.h>
#include <sys/auxv.h>

int guard(char over[100]){
	over[0] = over[100];
	printf("hello world");
}
int main(int argc,char *argv[]){
	long unsigned int random = getauxval(AT_RANDOM);
	printf("random %lx = %x\n",random,*(unsigned int*)random);
	guard(argv[0]);
}
