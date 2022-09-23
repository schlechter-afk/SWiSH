#include "headers.h"
#include "echo.h"
#include "globals.h"

void jobs(char *argumentList[250], int len)
{
    if (len >= 3)
    {
        fprintf(stderr, "Invalid Number of Arguments\n");
        return;
    }
    int countproc = 0;
    char *ProcFilePath = (char *)malloc(250 * sizeof(char));

    for (int i = 0; i < 50; i++)
    {
        for (int j = i + 1; j < 50; j++)
        {
            // printf("%d %d\n", cpyarrbg[i], cpyarrbg[j]);
            if (arrbg[i] != 0 && arrbg[j] != 0 && arrbg[i] != -1 && arrbg[j] != -1 && strcmp(strbg[i], strbg[j]) > 0)
            {
                char *tempstr = malloc(sizeof(char) * 250);
                strcpy(tempstr, cpystrbg[j]);
                strcpy(cpystrbg[j], cpystrbg[i]);
                strcpy(cpystrbg[i], tempstr);
                int tempvar = cpyarrbg[j];
                cpyarrbg[j] = cpyarrbg[i];
                cpyarrbg[i] = tempvar;
                // printf("no seg here\n");
            }
        }
    }

    for (int j = 1; j < 50; j++)
    {
        if (cpyarrbg[j] != -1)
        {
            countproc++;
            sprintf(ProcFilePath, "/proc/%d/stat", cpyarrbg[countproc]);
            FILE *openfile = fopen(ProcFilePath, "r");
            char *content = (char *)malloc(250 * sizeof(char));
            fgets(content, 250, openfile);
            char *state = (char *)malloc(250 * sizeof(char));
            char *token = strtok(content, " \t\r");
            for (int i = 2; i <= 3; i++)
            {
                token = strtok(NULL, " \r\t");
            }
            strcpy(state, token);

            free(content);

            if (strcmp(state, "I") == 0)
            {
                strcpy(state, "Interrupted");
            }
            else if (strcmp(state, "T") == 0)
            {
                strcpy(state, "Stopped");
            }
            else
            {
                strcpy(state, "Running");
            }
            if (len == 1)
            {
                printf("[%d] %s %s [%d]\n", countproc, state, cpystrbg[countproc], cpyarrbg[countproc]);
            }
            else if ((len == 2) && (strcmp(argumentList[1], "-r") == 0))
            {
                if (state[0] == 'R')
                {
                    printf("[%d] %s %s [%d]\n", countproc, state, cpystrbg[countproc], cpyarrbg[countproc]);
                }
            }
            else if ((len == 2) && (strcmp(argumentList[1], "-s") == 0))
            {
                if (state[0] == 'S')
                {
                    printf("[%d] %s %s [%d]\n", countproc, state, cpystrbg[countproc], cpyarrbg[countproc]);
                }
            }
            else
            {
                printf("Invalid Jobs Command\n");
                break;
            }
            free(state);
        }
    }
    // printf("survived sort\n");
    free(ProcFilePath);
}

// sleep 50 & sleep 40 & gedit & sleep 60 &