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

int fgbgcall(char *argumentList[250], int len)
{
    char *childProcName;
    setpgrp();
    if (strcmp(argumentList[len - 1], "&") == 0)
    {
        return bgproc(argumentList, len);
    }

    else
    {
        // ForeGround Process call
        childProcName = malloc(sizeof(char) * 250);
        childProcName = argumentList[0];
        return fgproc(argumentList, len);
    }
}

int bgproc(char *argumentList[250], int len)
{
    // setpgrp();
    int lent = 0;
    char *arglist[250];
    for (int i = 0; i < len; i++)
    {
        if (strcmp(argumentList[i], "&") != 0)
        {
            arglist[lent] = malloc(sizeof(char) * 250);
            strcpy(arglist[lent], argumentList[i]);
            lent++;
        }
        else
        {
            pid_t pid = fork();
            pid_t forkChild = pid;
            arglist[lent] = NULL;
            double time_spent = 0.0;
            time_t begin = time(NULL);
            if (forkChild == 0)
            {
                setpgrp();
                int return_value = execvp(arglist[0], arglist);
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
                        strcpy(strbg[j], arglist[0]);
                        printf("[%d] %d\n", j, ppid);
                        break;
                    }
                }
            }
            time_t end = time(NULL);
            time_spent += (double)(end - begin);
            for (int k = 0; k < lent; k++)
            {
                free(arglist[k]);
            }
            lent = 0;
        }
    }
}
