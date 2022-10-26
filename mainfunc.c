#include "headers.h"

extern int firstcd;
// void blue(char *str)
// {
//     printf("\e[34m");
//     printf("%s", str);
//     printf("\e[97m");
// }

// void black(char *str)
// {
//     printf("\e[30m");
//     printf("%s", str);
//     printf("\e[97m");
// }

// void blueint(int str)
// {
//     printf("\e[34m");
//     printf("%d", str);
//     printf("\e[97m");
// }

// void red(char *str)
// {
//     printf("\e[31m");
//     printf("%s", str);
//     printf("\e[97m");
// }

// void orange(char *str)
// {
//     printf("\e[33m");
//     printf("%s", str);
//     printf("\e[97m");
// }

void termcheck()
{
    int status;
    int pid = waitpid(-1, &status, WNOHANG);

    if (pid > 0)
    {
        int pos = 0;
        while (arrbg[pos] != pid)
        {
            pos++;
        }
        if (WIFSTOPPED(status))
        {
            return;
        }
        else
        {
            if (WIFEXITED(status))
            {
                fprintf(stderr, "%s with PID %d exited normally\n", strbg[pos], arrbg[pos]);
            }
            else
            {
                fprintf(stderr, "%s with PID %d exited abnormally\n", strbg[pos], arrbg[pos]);
            }
            arrbg[pos] = -1;
            free(strbg[pos]);
            return;
        }
    }
    else
    {
        return;
    }
}

// int fgRunning = 1;

// void controlhandle()
// {
// }

void mainfunc(char *command)
{
    char *historycmmd = (char *)malloc((sizeof(char) * 200));
    strcpy(historycmmd, command);

    int flagtab = 0;
    if (historycmmd[0] == '\t' || historycmmd[0] == ' ' || historycmmd[0] == '\n')
    {
        flagtab = 1;
    }

    if (!flagtab)
    {
        add_command_to_history(command);
    }

    printf("\033[1;30m");

    if (strlen(command) == 1)
    {
        return;
    }

    char *copycmd = (char *)malloc((sizeof(char *) * 200));

    strcpy(copycmd, command);

    int flagchk = 1;

    for (int i = 0; i < strlen(copycmd) - 1; i++)
    {
        if (copycmd[i] != ' ' && copycmd[i] != '\t')
        {
            flagchk = 0;
        }
    }

    if (flagchk)
    {
        return;
    }
    else
    {
        int flag = 0;
        for (int i = 0; i < strlen(command); i++)
        {
            if (command[i] == '|')
            {
                flag = 1;
            }
        }
        if (flag)
        {
            piping(command);
        }
        else
        {
            execute(command);
        }
    }
}