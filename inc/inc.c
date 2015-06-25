
//==============================================================================
//C Code for pthread_create() test
//==============================================================================
#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NTHREADS 4
#define NLOOP 0xfffffff
#define ASM_INC 0
#define PER_CPU 0
#define PER_CACH 64
#define MUL_PROC 1
#define LOCK ""//"lock "
unsigned int g_inc=0;
unsigned int *g_incs;
pthread_t threads[NTHREADS];
int get_num_cpus(void){
	return sysconf(_SC_NPROCESSORS_CONF);
}
void *do_inc(void *id) {
	int i;
	int j;
	i=0;
	cpu_set_t cpus;
	CPU_ZERO(&cpus);
#if MUL_PROC
	CPU_SET((int)id%get_num_cpus(), &cpus);
#else
	CPU_SET(0, &cpus);
#endif
	pthread_setaffinity_np(threads[(int)id], sizeof(cpu_set_t), &cpus);
	//printf("thread %d started\n",(int)id);
	for(i=0;i<NLOOP;i++){
		//asm("lock incl %0"::"m"(g_inc));
#if ASM_INC
		asm(LOCK "incl %0"::"m"(g_inc));
#elif PER_CPU
		g_incs[(int)id*PER_CACH]++;
#else
		g_inc++;
#endif
	}
	pthread_exit(NULL);
}                      
int main(int argc, char *argv[]) {
	void *status;
	int rc, i,t, j, detachstate;
	int sum;
	g_incs = (int*)malloc(sizeof(int)*NTHREADS*64);
	if(g_incs == NULL){
		exit(0);
	}
	//pthread_t tid;	
	pthread_attr_t attr;
	printf("cpus %d\n",get_num_cpus());
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for (j=0; j<NTHREADS; j++) {
		rc = pthread_create(&threads[j], &attr, 
			do_inc, (void *)j);
		if (rc) {              
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}

		/* Wait for the thread */
	}
	/* Free attribute and wait for the other threads */
	for(t=0; t<NTHREADS; t++) {
		rc = pthread_join(threads[t], &status);
		if (rc) {
			printf("ERROR; return code from pthread_join() is %d\n", rc);
			exit(-1);
		}
		//printf("Main: completed join with thread %d"\
		//	 "having a status   of %ld\n",t,(long)status);
	}
	pthread_attr_destroy(&attr);
	//pthread_attr_destroy(&attr);
	for(i=0;i<NTHREADS;i++){
		sum+=g_incs[i*PER_CACH];
	}
	printf("inc = %u, from %u, %% %f \n",
#if PER_CPU
		sum,NLOOP*NTHREADS,(double)sum*100/(NLOOP*NTHREADS));
#else
		g_inc,NLOOP*NTHREADS,(double)g_inc*100/(NLOOP*NTHREADS));
#endif

	free(g_incs);
	pthread_exit(NULL);

}

