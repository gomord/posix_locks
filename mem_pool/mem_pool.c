#include <stdio.h>
#include "mem_pool.h"
#define MEM(node) (node + 1)
#define NODE(mem) (PNODE(mem) - 1)
#define BLOCK_SIZE(size) (sizeof(mem_node_t) + size)
#define COUNT_MASK 0x3
#define PNODE(ptr) ((mem_node_t *)((size_t)(ptr) & ~COUNT_MASK))

 #define CAS(ptr,old,new) \
          (__sync_bool_compare_and_swap_4(ptr,(unsigned int)old,(unsigned int)new))

struct mem_root mr;
void init_mem(void){
	int i;
	for(i=0;i<NR_POOLS;i++){
		mr.pools[i].size = 0;
		mr.pools[i].head = NULL;
	}
}
static void add_node(mem_node_t **head,mem_node_t *node){
	int i = -1;
	size_t counter;
	do{
		i++;
		counter = (size_t)*head & COUNT_MASK;
		counter++;
		node->next = *head;
		//remove me!!
		if(node == NULL) break;
	}while(!CAS(head,node->next,node | (counter & COUNT_MASK)));
	if(i>9)	
		printf("number of tries to add is %d \n",i);
}
static mem_node_t *remove_node(mem_node_t **head){
	mem_node_t *next;
	size_t counter;
	int i = -1;
//	printf("next %d head %d",next,head);
	
	do{
		i++;
		counter = (size_t)*head & COUNT_MASK;
		counter++;
		next = *head;
		if(PNODE(next) == NULL) break;
	}while(!CAS(head,next,PNODE(next)->next | (counter & COUNT_MASK)));
	if(i>500)	
		printf("numver of tries to remove is %d \n",i);
	return PNODE(next);
}
int add_to_pool(char *block,size_t mem_size,size_t pool_size){
	int i;
	int pool_num;
	//check alien to 4 
	//printf("ms %d, bs %d %%%d \n ",mem_size,BLOCK_SIZE(pool_size),mem_size%BLOCK_SIZE(pool_size));
	if((int)block & 0x3 || 0 != mem_size % BLOCK_SIZE(pool_size)){
		return -1;
	}
	//printf("ms %d, bs %d\n",mem_size,BLOCK_SIZE(pool_size));
	//fine empty pool
	for(i=0;i<NR_POOLS;i++){
		if(mr.pools[i].size == pool_size){
			break;
		}
		if(mr.pools[i].size == 0){ 
			if(i != 0 || mr.pools[i-1].size < pool_size){
				break;
			}
			else return -1;
		}
	}
	if(i == NR_POOLS){
		return -1;
	}
	pool_num = i;

	printf("pool i=%d\n",pool_num);
	//set up link list
	for(i=0;
		i<mem_size - BLOCK_SIZE(pool_size);
		i+= BLOCK_SIZE(pool_size)){
		PNODE(block+i)->next = PNODE(block + i + BLOCK_SIZE(pool_size));
	}
	PNODE(block + i)->next = NULL;
	mr.pools[pool_num].head = PNODE(block);
	mr.pools[pool_num].size = pool_size;
	return mem_size/BLOCK_SIZE(pool_size);
}

void free(void *mem){
	add_node(&NODE(mem)->pool->head,NODE(mem));
}

void * malloc(size_t size){
	int i=0;
	mem_node_t *mem_free;
	while(i != NR_POOLS){
		//printf("i=%d ps = %d,\n",i,mr.pools[i].size);
		if(mr.pools[i].size >= size && mr.pools[i].head != NULL){
			//printf("found i=%d ps = %d,\n",i,mr.pools[i].size);
			mem_free = remove_node(&mr.pools[i].head);
			if(mem_free == NULL) i++;
			else{ 
				mem_free->pool = &mr.pools[i];
				return MEM(mem_free);
			}
		}
		if(mr.pools[i].size == 0){
			break;
		}
	}
	return NULL;

}
