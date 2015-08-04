#include <stdio.h>
#include <string.h>
/*void *my_memset(void *s, int c, size_t n){
	volatile void *ts = s;
	memset(ts,c,n);
}
*/
extern ml_func(int,int);
int main(){
	char a[34];
	printf("hello world %d\n",ml_func(2,3));
	memset(a,0,34);
}
