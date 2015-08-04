#include <string.h>
#include "canary.c"
void vuln1(char *str){
	char buf[0x10];
}
void vuln2(char *str){
	char buf[0x20];
}
void vuln(const char *str)
{
	
	char buf[0x10];
	fix_canary(84);
	//strcpy(buf, str);
}
 
int main(int argc, char *argv[])
{
  vuln(argv[1]);
  return 0;
}
