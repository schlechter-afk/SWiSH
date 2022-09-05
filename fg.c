#include "headers.h"

int fgproctime(char *argumentList[250], int len)
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
        // wait(NULL);
        int status;
        waitpid(forkChild, &status, WUNTRACED | WCONTINUED);
    }
    time_t end = time(NULL);
    time_spent += (double)(end - begin);
    return time_spent;
}

int fgproc(char *argumentList[250], int len)
{
    int forkChild;
    forkChild = fork();
    argumentList[len] = NULL;
    double time_spent = 0.0;
    time_t begin = time(NULL);
    if (forkChild == 0)
    {
        execvp(argumentList[0], argumentList);
        perror("something went wrong with fg: ");
        exit(0);
    }
    else
    {
        // wait(NULL);
        int status;
        waitpid(forkChild, &status, WUNTRACED | WCONTINUED);
    }
    time_t end = time(NULL);
    time_spent += (double)(end - begin);
    return 1;
}

int fgbgcall(char *line[50], int len)
{
    char *childProcName;
    // printf("len is %d\n", len);
    if (strcmp(line[len - 1], "&") == 0)
    {
        // Back Ground Process call
        line[len - 1] = NULL;
        len -= 1;
        return bgproc(line, len);
    }

    else
    {
        // ForeGround Process call
        childProcName = malloc(sizeof(char) * 250);
        childProcName = line[0];
        return fgproc(line, len);
    }
}

int bgproc(char *argumentList[250], int len)
{
    // for (int i = 0; i < len; i++)
    // {
    //     printf("~~~ %s\n", argumentList[i]);
    // }
    int forkChild;
    forkChild = fork();
    // printf("forkchild is %d\n", forkChild);
    argumentList[len] = NULL;
    double time_spent = 0.0;
    time_t begin = time(NULL);
    if (forkChild == 0)
    {
        setpgrp();
        execvp(argumentList[0], argumentList);
        perror("something went wrong with bg: ");
        exit(0);
    }
    else
    {
        int ppid = forkChild;
        for (int i = 0; i < 50; i++)
        {
            if (arrbg[i] == -1)
            {
                arrbg[i] = ppid;
                strbg[i] = malloc(sizeof(char) * 250);
                strcpy(strbg[i], argumentList[0]);
                printf("[%d] %d\n", i, ppid);
                break;
            }
        }
    }
    time_t end = time(NULL);
    time_spent += (double)(end - begin);
    return 1;
}