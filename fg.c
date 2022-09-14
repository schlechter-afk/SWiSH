#include "headers.h"

int fgproc(char *argumentList[250], int len)
{
    timetaken = -1;
    int forkChild;
    forkChild = fork();
    argumentList[len] = NULL;
    double time_spent = 0.0;
    time_t begin = time(NULL);
    if (forkChild == 0)
    {
        int ret = execvp(argumentList[0], argumentList);
        perror("file nahi hai aisi koi");
        if (ret == -1)
        {
            printf("INVALID COMMAND ;)\n");
            return 1;
        }
        perror("something went wrong with fg: ");
        exit(0);
    }
    else
    {
        int status;
        waitpid(forkChild, &status, WUNTRACED | WCONTINUED);
    }
    time_t end = time(NULL);
    time_spent += (double)(end - begin);
    timetaken = time_spent;
    return 1;
}

int fgbgcall(char *argumentList[250], int len)
{
    int lent = 0;
    char *arglist[250];
    int flag = 0;
    for (int i = 0; i < len; i++)
    {
        if (strcmp(argumentList[i], "&") != 0)
        {
            if (strcmp(argumentList[i], "<") == 0 || strcmp(argumentList[i], ">") == 0)
            {
            }
            else
            {
                arglist[lent] = malloc(sizeof(char) * 250);
                strcpy(arglist[lent], argumentList[i]);
                lent++;
            }
        }
        else
        {
            arglist[lent] = NULL;
            flag = 1;
            bgproc(arglist, lent);
            for (int k = 0; k < lent; k++)
            {
                free(arglist[k]);
            }
            lent = 0;
        }
    }
    if (lent != 0)
    {
        fgproc(arglist, lent);
    }
}

int bgproc(char *argumentList[250], int len)
{
    pid_t pid = fork();
    pid_t forkChild = pid;
    argumentList[len] = NULL;
    if (forkChild == 0)
    {
        setpgrp();
        int return_value = execvp(argumentList[0], argumentList);
        perror("something went wrong with bg: ");
        exit(0);
    }
    else
    {
        int ppid = forkChild;
        for (int j = 0; j < 50; j++)
        {
            if (arrbg[j] == -1)
            {
                arrbg[j] = ppid;
                strbg[j] = malloc(sizeof(char) * 250);
                strcpy(strbg[j], argumentList[0]);
                printf("[%d] %d\n", j, ppid);
                break;
            }
        }
    }
}
