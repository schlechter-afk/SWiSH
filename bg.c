#include "headers.h"

int bgproc(char *argumentList[250], int len)
{
    int forkChild;
    forkChild = fork();
    argumentList[len] = NULL;
    double time_spent = 0.0;
    time_t begin = time(NULL);
    if (forkChild == 0)
    {
        execvp(argumentList[0], argumentList);
        exit(0);
    }
    else
    {
        int ppid = getpid();
        printf("%d\n", ppid);
    }
    time_t end = time(NULL);
    time_spent += (double)(end - begin);
    return time_spent;
}