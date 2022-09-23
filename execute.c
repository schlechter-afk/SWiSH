#include "headers.h"
#include "echo.h"
#include "globals.h"

char *strcomm;
int fgRunning = 0;

// void controlhandle()
// {
//     if (fgRunning)
//     {
//         fgRunning = 0;
//     }
// }

void execute(char command[1000])
{
    // signal(SIGINT, controlhandle);
    // signal(SIGTSTP, controlhandle);

    // signal(SIGTSTP, SIG_IGN);
    // signal(SIGINT, SIG_IGN);

    int checkempty = 1;
    int count = 0;
    char *saveptr_arg1 = (char *)malloc(sizeof(char) * 200);
    char *saveptr_arg2 = (char *)malloc(sizeof(char) * 200);
    argptr1 = (char *)malloc(sizeof(char) * 200);
    argptr2 = (char *)malloc(sizeof(char) * 200);
    char delim[2] = ";";
    argptr2 = strtok_r(command, delim, &saveptr_arg2);

    strcomm = (char *)malloc(1000);
    strcpy(strcomm, command);

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

        if (len == 0)
        {
            return;
        }

        argptr2 = strtok_r(NULL, delim, &saveptr_arg2);

        char *storeargptr2 = (char *)malloc(sizeof(char) * 100);

        int chkempty = 0;
        if (argptr2 != NULL)
        {
            chkempty = 1;
            strcpy(storeargptr2, argptr2);
        }

        int input_file_flag = 0, output_file_flag = 0, append_flag = 0;

        char *inputfile = malloc(1000);
        char *outputfile = malloc(1000);
        char *appendf = malloc(1000);

        int fd;
        int fd2;
        int fd3;

        for (int i = 0; i < len; i++)
        {
            if (!(strcmp(argumentList[i], "<")))
            {
                strcpy(inputfile, argumentList[i + 1]);
                input_file_flag = 1;
            }
            else if (!(strcmp(argumentList[i], ">")))
            {
                strcpy(outputfile, argumentList[i + 1]);
                output_file_flag = 1;
            }
            else if (!(strcmp(argumentList[i], ">>")))
            {
                strcpy(appendf, argumentList[i + 1]);
                append_flag = 1;
            }
        }

        int flagg = 0;
        int x = len;
        for (int i = 0; i < len; i++)
        {
            if (strcmp(argumentList[i], "<") == 0 || strcmp(argumentList[i], ">") == 0 || strcmp(argumentList[i], ">>") == 0)
            {
                argumentList[i][0] = '\0';
                x--;
                flagg = 1;
            }
            if (flagg && argumentList[i][0] != '\0')
            {
                argumentList[i][0] = '\0';
                x--;
            }
        }
        len = x;

        if (input_file_flag)
        {
            fd = open(inputfile, O_RDONLY, 0);
            if (fd < 0)
            {
                perror("Error opening input file");
                return;
            }
            if (dup2(fd, 0) < 0)
            {
                perror("Error - duping the input");
                return;
            }
        }

        if (output_file_flag)
        {
            fd2 = open(outputfile, O_TRUNC | O_CREAT | O_WRONLY, 0644);
            if (fd2 < 0)
            {
                perror("Error opening output file");
                return;
            }
            if (dup2(fd2, 1) < 0)
            {
                perror("Error - duping the output");
                return;
            }
        }

        if (append_flag)
        {
            fd3 = open(appendf, O_APPEND | O_CREAT | O_WRONLY, 0644);
            if (fd3 < 0)
            {
                perror("Error opening the to be appended file");
                return;
            }
            if (dup2(fd3, 1) < 0)
            {
                perror("Error - duping while appending");
                return;
            }
        }

        // *************************************

        // printf("%s\n", argumentList[0]);

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
        else if (strcmp("jobs", argumentList[0]) == 0)
        {
            jobs(argumentList, len);
            for (int i = 0; i < len; i++)
            {
                argumentList[i][0] = '\0';
            }
        }
        else if (strcmp("sig", argumentList[0]) == 0)
        {
            sigfunc(argumentList, len);
            for (int i = 0; i < len; i++)
            {
                argumentList[i][0] = '\0';
            }
        }
        else
        {
            fgRunning = 1;
            fgbgcall(argumentList, len);
        }
        if (chkempty)
        {
            argptr2 = storeargptr2;
        }
        close(fd);
        close(fd2);
        close(fd3);

        // TRY uncommenting if getting seg fault;
        // for (int i = 0; i < len; i++)
        // {
        //     argumentList[i][0] = '\0';
        // }
    }
    return;
}
