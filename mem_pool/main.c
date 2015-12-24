#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "mem_pool.h"
#define NUM_THREADS 10
#define NR_ELEM 10000
#define SIZE_MEM(pool_size) ( NR_ELEM*(sizeof(mem_node_t) + pool_size))
char memory[SIZE_MEM(12)];
char memory2[SIZE_MEM(28)];

int g_inc = 0;
void *PrintHello(void *threadid)
{
	long tid;
	char *pc[5500];
	int count;
	int i,j;
	tid = (long)threadid;
	//printf("Hello World! It's me, thread #%ld!\n", tid);
	while(1){
	for(i=0;i<10000;i++){
		count = 0;
		for(j=0;j<5500;j++){
			pc[j] = (char *)malloc(10);
		}
		for(j=0;j<5500;j++){
			if(pc[j] != NULL)
				free(pc[j]);
			else count++;
		}
		printf("test number %04d for thread num %04ld %04d \r",i,tid,count);
	}
	}
	pthread_exit((void *)threadid);
}


void *BusyWork(void *t)
{
	int i;
	long tid;
	double result=0.0;
	tid = (long)t;
	printf("Thread %ld starting...\n",tid);
	for (i=0; i<1000000; i++)
	{
		result *= i;// result + sin(i) * tan(i);
	}
	printf("Thread %ld done. Result = %e\n",tid, result);
	while(1);
	pthread_exit((void*) t);
}



int main(int argc,char *argv[]){
        init_mem();
	printf("address %x added to mem %d\n",(int)memory,add_to_pool(memory,SIZE_MEM(12),12));
	printf("address %x added to mem %d\n",(int)memory2,add_to_pool(memory2,SIZE_MEM(28),28));
/*	
	int i=0;
	char *pc[NR_ELEM*2];
	for(i=0;i<NR_ELEM;i++){
		pc[i] = (char *)malloc(10);
		printf("i=%d elem = %p\n",i,pc[i]); 
	}
	for(;i<NR_ELEM*2;i++){
		pc[i] = (char *)malloc(10);
		printf("i=%d elem = %p\n",i,pc[i]); 
	}
	printf("free\n");
	for(i=0;i<NR_ELEM*2;i++){
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
	*/
	pthread_t thread[NUM_THREADS];
	pthread_attr_t attr;
	int rc;
	long t;
	void *status;

	// Initialize and set thread detached attribute 
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for(t=0; t<NUM_THREADS; t++) {
	//	printf("Main: creating thread %ld\n", t);
		rc = pthread_create(&thread[t], &attr,PrintHello, (void *)t); 
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	// Free attribute and wait for the other threads 
	for(t=0; t<NUM_THREADS; t++) {
		rc = pthread_join(thread[t], &status);
		if (rc) {
			printf("ERROR; return code from pthread_join() is %d\n", rc);
			exit(-1);
		}
		printf("Main: completed join with thread %ld having a status "\
				"of %ld\n",t,(long)status);
	}

	printf("Main: program completed. Exiting.\n");
	pthread_attr_destroy(&attr);
//*/

	while(1) sleep(100);
	pthread_exit(NULL);
	return 0;
}
