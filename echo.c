#include "headers.h"
#include "echo.h"
#include "globals.h"

void echocmd(char *argumentList[300], int len)
{
    // argumentList[i] = strtok(argumentList[i], " \t");
    // argumentList[i] = strtok(NULL, " \t");
    for (int i = 1; i < len; i++)
    {
        // argumentList[i] = strtok(argumentList[i], " \t");
        // argumentList[i] = strtok(NULL, " \t");
        printf("%s ", argumentList[i]);
    }
    printf("\n");
}