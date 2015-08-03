#include <stdio.h>

extern char **environ;

int main(int argc, char *argv[],char **envp)
{
    int ii,j;
    char **p = environ;
    for (ii = 0; ii < argc; ii++)
        printf("argv[%d] = '%s'\n", ii, argv[ii]);
    while (*p)
        printf("%s\n", *p++);
    return 0;
}
