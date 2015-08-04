
#include <stdio.h>
#include <time.h>

#define LOOPS 1000000000

static __thread int tlsvar __attribute__((tls_model ("initial-exec")));
int globalvar __attribute__ ((visibility ("hidden")));
//int globalvar;

int tls_access(void)
{
  return tlsvar;
}

void set_tls(int v)
{
  tlsvar = v;
}

int global_access(void)
{
  return globalvar;
}

int main(void)
{
  struct timespec start, end;
  unsigned int i, loops = LOOPS;
  double tls_elapsed, global_elapsed;

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
  for (i = 0; i < LOOPS; i++)
    {
      tls_access();
    }
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

  tls_elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
  for (i = 0; i < LOOPS; i++)
    {
      global_access();
    }
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

  global_elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;

  printf("TLS ticks per 1000 loops: %.10f Global ticks per 1000 loops: %.10f\n",
         (tls_elapsed / loops) * 1000, (global_elapsed / loops) * 1000);
  printf("resio %f",(float)(tls_elapsed)/global_elapsed);

}
