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
            if (arrbg[i] != 0 && arrbg[j] != 0 && arrbg[i] != -1 && arrbg[j] != -1 && strcmp(strbg[i], strbg[j]) > 0)
            {
                char *tempstr = malloc(sizeof(char) * 250);
                strcpy(tempstr, strbg[j]);
                strcpy(strbg[j], strbg[i]);
                strcpy(strbg[i], tempstr);
                int tempvar = arrbg[j];
                arrbg[j] = arrbg[i];
                arrbg[i] = tempvar;
                int temp = assoc[i];
                assoc[i] = assoc[j];
                assoc[j] = temp;
            }
        }
    }

    int flag = 0;
    int counter = 0;

    for (int j = 1; j < 50; j++)
    {
        if (arrbg[j] != -1)
        {
            countproc++;

            // int val = countproc + counter;
            // printf("dd %d\n", arrbg[val]);

            sprintf(ProcFilePath, "/proc/%d/stat", arrbg[j]);

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
                printf("[%d] %s %s [%d]\n", assoc[j], state, strbg[j], arrbg[j]);
            }
            else if ((len == 2) && (strcmp(argumentList[1], "-r") == 0))
            {
                if (state[0] == 'R')
                {
                    printf("[%d] %s %s [%d]\n", assoc[j], state, strbg[j], arrbg[j]);
                }
            }
            else if ((len == 2) && (strcmp(argumentList[1], "-s") == 0))
            {
                if (state[0] == 'S')
                {
                    printf("[%d] %s %s [%d]\n", assoc[j], state, strbg[j], arrbg[j]);
                }
            }
            else
            {
                printf("Invalid Jobs Command\n");
                break;
            }
            free(state);
        }
        else
        {
            flag = 1;
            counter++;
        }
    }
    free(ProcFilePath);
}

// sleep 50 & sleep 40 & gedit & sleep 60 &