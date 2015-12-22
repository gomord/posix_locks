#include <stdio.h>
#include "mem_pool.h"
#define NR_ELEM 10
#define SIZE_MEM(pool_size) ( NR_ELEM*(sizeof(mem_node_t) + pool_size))
char memory[SIZE_MEM(12)];
char memory2[SIZE_MEM(28)];
int main(int argc,char *argv[]){
	int i=0;
	char *pc[NR_ELEM*2];
	init_mem();
	printf("address %x added to mem %d\n",(int)memory,add2pool(memory,SIZE_MEM(12),12));
	printf("address %x added to mem %d\n",(int)memory2,add2pool(memory2,SIZE_MEM(28),28));
	for(i=0;i<NR_ELEM;i++){
		pc[i] = (char *)malloc(10);
		printf("i=%d elem = %p\n",i,pc[i]); 
	}
	for(;i<NR_ELEM*2;i++){
		pc[i] = (char *)malloc(10);
		printf("i=%d elem = %p\n",i,pc[i]); 
	}
	return 0;
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
