#include "headers.h"
#include "echo.h"
#include "globals.h"

void execute(char command[1000])
{
    int checkempty = 1;
    int count = 0;
    char *saveptr_arg1 = (char *)malloc(sizeof(char) * 200);
    char *saveptr_arg2 = (char *)malloc(sizeof(char) * 200);
    argptr1 = (char *)malloc(sizeof(char) * 200);
    argptr2 = (char *)malloc(sizeof(char) * 200);
    char delim[2] = ";";
    argptr2 = strtok_r(command, delim, &saveptr_arg2);

    while (argptr2 != NULL)
    {
        argptr1 = strtok_r(argptr2, " \t\n", &saveptr_arg1);
        char *argumentList[300];
        char *templist[300];

        int len = 0;
        while (argptr1 != NULL)
        {
            argumentList[len++] = argptr1;
            argptr1 = strtok_r(NULL, " \t\n", &saveptr_arg1);
        }

        bool check = false;
        for (int i = 0; i < strlen(argumentList[len - 1]); i++)
        {
            if (argumentList[len - 1][i] != ' ' && argumentList[len - 1][i] != '\n')
                check = true;
        }
        if (!check)
        {
            len--;
        }

        if (len == 0)
        {
            return;
        }

        argptr2 = strtok_r(NULL, delim, &saveptr_arg2);

        char *storeargptr2 = (char *)malloc(sizeof(char) * 100);

        // // assert(storeargptr2!=NULL);
        int chkempty = 0;
        if (argptr2 != NULL)
        {
            chkempty = 1;
            strcpy(storeargptr2, argptr2);
        }

        if (strcmp("cd", argumentList[0]) == 0)
        {
            if (len == 1)
            {
                char *tempcurrentdirectory = malloc(sizeof(char) * 200);
                getcwd(tempcurrentdirectory, 1000);
                strcpy(prevdir, tempcurrentdirectory);
                chdir(homedir);
            }
            else if (len > 2)
            {
                printf("Too many Arguments passed\n");
            }
            else
            {
                cdcmd(argumentList, len);
            }
            for (int i = 0; i < len; i++)
            {
                argumentList[i][0] = '\0';
            }
        }

        else if (strcmp("echo", argumentList[0]) == 0)
        {
            echocmd(argumentList, len);
            for (int i = 0; i < len; i++)
            {
                argumentList[i][0] = '\0';
            }
        }

        else if (strcmp("pwd", argumentList[0]) == 0)
        {
            pwdcmd();
            for (int i = 0; i < len; i++)
            {
                argumentList[i][0] = '\0';
            }
        }

        else if (strcmp("clear", argumentList[0]) == 0)
        {
            printf("\e[1;1H\e[2J");
            for (int i = 0; i < len; i++)
            {
                argumentList[i][0] = '\0';
            }
        }
        else if (strcmp("ls", argumentList[0]) == 0)
        {
            inpls(argumentList, len);
            for (int i = 0; i < len; i++)
            {
                argumentList[i][0] = '\0';
            }
        }
        else if (strcmp("history", argumentList[0]) == 0)
        {
            display_history();
            for (int i = 0; i < len; i++)
            {
                argumentList[i][0] = '\0';
            }
        }
        else if (strcmp("pinfo", argumentList[0]) == 0)
        {
            pinfocmd(argumentList, len);
            for (int i = 0; i < len; i++)
            {
                argumentList[i][0] = '\0';
            }
        }
        else if (strcmp("discover", argumentList[0]) == 0)
        {
            char *currirect = malloc(sizeof(char) * 200);
            getcwd(currirect, 2000);
            executediscover(currirect, currirect, argumentList, len);
            for (int i = 0; i < len; i++)
            {
                argumentList[i][0] = '\0';
            }
        }
        else
        {
            fgbgcall(argumentList, len);
        }
        if (chkempty)
        {
            argptr2 = storeargptr2;
        }
        // for (int i = 0; i < len; i++)
        // {
        //     argumentList[i][0] = '\0';
        // }
    }
    return;
}
