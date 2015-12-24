#ifndef _MEM_POOL_H
#define _MEM_POOL_H
#define NR_POOLS 10
#include <stddef.h>
struct mem_node;
typedef struct mem_pool{
	struct mem_node *head;
	size_t size;
} mem_pool_t;
typedef struct mem_node{
	union{
		struct mem_node *next;
		struct mem_pool *pool;
	};
}mem_node_t;
struct mem_root{
	mem_pool_t pools[NR_POOLS];
};
void init_mem(void);
int add_to_pool(char *mem,size_t mem_size,size_t pool_size);
void * malloc(size_t size);
void free(void *mem);
#endif // _MEM_POOL_H
