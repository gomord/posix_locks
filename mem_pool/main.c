#include <stdio.h>
#include "mem_pool.h"
#define NR_ELEM 10
#define SIZE_MEM ( NR_ELEM*(sizeof(mem_node_t) + 16))
char memory[SIZE_MEM];
int main(int argc,char *argv[]){
	int i;
	char *pc[NR_ELEM*2];
	init_mem();
	printf("address %x added to mem %d\n",(int)memory,add2pool(memory,SIZE_MEM,16));
	for(i=0;i<NR_ELEM+1;i++){
		pc[i] = (char *)malloc(10);
		printf("i=%d elem = %p\n",i,pc[i]); 
	}
	for(;i<NR_ELEM*2;i++){
		pc[i] = (char *)malloc(10);
		printf("i=%d elem = %p\n",i,pc[i]); 
	}
	printf("free\n");
	for(i=0;i<NR_ELEM;i++){
		free(pc[i]);
		printf("i=%d elem = %p\n",i,pc[i]); 
	}
	for(i=0;i<NR_ELEM/2;i++){
		pc[i] = (char *)malloc(10);
		printf("i=%d elem = %p\n",i,pc[i]); 
	}
	for(i=0;i<NR_ELEM/2;i++){
		free(pc[i]);
		printf("i=%d elem = %p\n",i,pc[i]); 
	}
	//free(pc);
	return 0;
}
