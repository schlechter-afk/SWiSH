#include "headers.h"
#include "echo.h"
#include "globals.h"

void bgjobsfunc(char *argumentList[250], int len)
{
    int JobNo = atoi(argumentList[1]);
    if (len >= 3)
    {
        printf("Invalid command\n");
    }

    // Invalid for job_no > no of bg proc.

    if (JobNo <= 0)
    {
        fprintf(stderr, "Invalid Job Number\n");
        return;
    }

    kill(arrbg[assoc[JobNo]], SIGTTIN);
    kill(arrbg[assoc[JobNo]], SIGCONT);
}